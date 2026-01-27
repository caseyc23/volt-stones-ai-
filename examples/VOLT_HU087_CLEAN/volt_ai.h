/*
 * ============================================
 * VOLT AI Engine - Simplified & Optimized
 * ============================================
 * 
 * Handles all AI interactions:
 * - Voice recording
 * - Speech-to-text (Whisper)
 * - GPT-4 conversations
 * - Text-to-speech
 * 
 * Optimized for Stone's HU-087 watch
 * 
 * ============================================
 */

#ifndef VOLT_AI_H
#define VOLT_AI_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <driver/i2s.h>
#include "config_stone.h"
#include "pins_hu087.h"

class VoltAI {
private:
    String apiKey;
    String systemPrompt;
    int16_t* audioBuffer;
    bool initialized;
    
    // Setup I2S for recording (mode=0) or playback (mode=1)
    void setupI2S(int mode) {
        i2s_driver_uninstall((i2s_port_t)((mode == 0) ? MIC_I2S_NUM : SPK_I2S_NUM));
        
        i2s_config_t i2s_config = {
            .mode = (mode == 0) ? 
                (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX) : 
                (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
            .sample_rate = SAMPLE_RATE,
            .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
            .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
            .communication_format = I2S_COMM_FORMAT_STAND_I2S,
            .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
            .dma_buf_count = 8,
            .dma_buf_len = 1024,
            .use_apll = true,
            .tx_desc_auto_clear = true,
            .fixed_mclk = 0
        };
        
        i2s_pin_config_t pin_config;
        
        if (mode == 0) {
            // Microphone pins
            pin_config.bck_io_num = MIC_SCK;
            pin_config.ws_io_num = MIC_WS;
            pin_config.data_out_num = I2S_PIN_NO_CHANGE;
            pin_config.data_in_num = MIC_SD;
        } else {
            // Speaker pins
            pin_config.bck_io_num = SPK_BCLK;
            pin_config.ws_io_num = SPK_LRCK;
            pin_config.data_out_num = SPK_DOUT;
            pin_config.data_in_num = I2S_PIN_NO_CHANGE;
            
            // Enable speaker amplifier
            pinMode(SPK_SD_MODE, OUTPUT);
            digitalWrite(SPK_SD_MODE, HIGH);
        }
        
        i2s_driver_install((i2s_port_t)((mode == 0) ? MIC_I2S_NUM : SPK_I2S_NUM), &i2s_config, 0, NULL);
        i2s_set_pin((i2s_port_t)((mode == 0) ? MIC_I2S_NUM : SPK_I2S_NUM), &pin_config);
    }

public:
    VoltAI() : audioBuffer(nullptr), initialized(false) {}
    
    ~VoltAI() {
        if (audioBuffer) {
            free(audioBuffer);
        }
    }
    
    bool begin(const char* key, const char* prompt) {
        apiKey = String(key);
        systemPrompt = String(prompt);
        
        // Replace placeholders
        systemPrompt.replace("CHILD_NAME_PLACEHOLDER", CHILD_NAME);
        systemPrompt.replace("CHILD_AGE_PLACEHOLDER", String(CHILD_AGE));
        
        // Allocate audio buffer
        if (psramInit()) {
            Serial.println("AI: Using PSRAM for audio buffer");
            audioBuffer = (int16_t*)ps_malloc(BUFFER_SIZE * sizeof(int16_t));
        } else {
            Serial.println("AI: Using heap for audio buffer");
            audioBuffer = (int16_t*)malloc(BUFFER_SIZE * sizeof(int16_t));
        }
        
        if (!audioBuffer) {
            Serial.println("AI: Failed to allocate audio buffer");
            return false;
        }
        
        initialized = true;
        Serial.println("AI: Initialized successfully");
        return true;
    }
    
    void recordAudio() {
        if (!initialized) return;
        
        Serial.println("AI: Recording audio...");
        setupI2S(0);  // Microphone mode
        
        size_t bytesRead = 0;
        i2s_read((i2s_port_t)MIC_I2S_NUM, audioBuffer, BUFFER_SIZE * sizeof(int16_t), &bytesRead, portMAX_DELAY);
        
        Serial.printf("AI: Recorded %d bytes\n", bytesRead);
    }
    
    String transcribe() {
        if (!initialized || WiFi.status() != WL_CONNECTED) {
            Serial.println("AI: Cannot transcribe (not initialized or no WiFi)");
            return "";
        }
        
        Serial.println("AI: Transcribing audio...");
        
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient https;
        
        if (!https.begin(client, "https://api.openai.com/v1/audio/transcriptions")) {
            Serial.println("AI: Failed to connect to API");
            return "";
        }
        
        https.addHeader("Authorization", "Bearer " + apiKey);
        https.setTimeout(15000);
        
        // Create multipart form data
        String boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW";
        https.addHeader("Content-Type", "multipart/form-data; boundary=" + boundary);
        
        String body = "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"model\"\r\n\r\n";
        body += String(STT_MODEL) + "\r\n";
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"file\"; filename=\"audio.wav\"\r\n";
        body += "Content-Type: audio/wav\r\n\r\n";
        
        // Send request
        https.POST((uint8_t*)body.c_str(), body.length());
        https.writeToStream((uint8_t*)audioBuffer, BUFFER_SIZE * sizeof(int16_t));
        
        String endBoundary = "\r\n--" + boundary + "--\r\n";
        https.POST((uint8_t*)endBoundary.c_str(), endBoundary.length());
        
        int httpCode = https.GET();
        String result = "";
        
        if (httpCode == HTTP_CODE_OK) {
            String response = https.getString();
            DynamicJsonDocument doc(1024);
            
            if (deserializeJson(doc, response) == DeserializationError::Ok) {
                result = doc["text"].as<String>();
                Serial.println("AI: Transcription: " + result);
            }
        } else {
            Serial.printf("AI: Transcription failed (HTTP %d)\n", httpCode);
        }
        
        https.end();
        return result;
    }
    
    String chat(String userMessage) {
        if (!initialized || WiFi.status() != WL_CONNECTED) {
            Serial.println("AI: Cannot chat (not initialized or no WiFi)");
            return "";
        }
        
        Serial.println("AI: Getting GPT response...");
        
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient https;
        
        if (!https.begin(client, "https://api.openai.com/v1/chat/completions")) {
            Serial.println("AI: Failed to connect to API");
            return "";
        }
        
        https.addHeader("Authorization", "Bearer " + apiKey);
        https.addHeader("Content-Type", "application/json");
        https.setTimeout(30000);
        
        // Build JSON request
        DynamicJsonDocument doc(2048);
        doc["model"] = AI_MODEL;
        doc["max_tokens"] = MAX_TOKENS;
        doc["temperature"] = AI_TEMPERATURE;
        
        JsonArray messages = doc.createNestedArray("messages");
        
        JsonObject systemMsg = messages.createNestedObject();
        systemMsg["role"] = "system";
        systemMsg["content"] = systemPrompt;
        
        JsonObject userMsg = messages.createNestedObject();
        userMsg["role"] = "user";
        userMsg["content"] = userMessage;
        
        String jsonPayload;
        serializeJson(doc, jsonPayload);
        
        int httpCode = https.POST(jsonPayload);
        String result = "";
        
        if (httpCode == HTTP_CODE_OK) {
            String response = https.getString();
            DynamicJsonDocument responseDoc(4096);
            
            if (deserializeJson(responseDoc, response) == DeserializationError::Ok) {
                result = responseDoc["choices"][0]["message"]["content"].as<String>();
                Serial.println("AI: GPT response: " + result);
            }
        } else {
            Serial.printf("AI: Chat failed (HTTP %d)\n", httpCode);
        }
        
        https.end();
        return result;
    }
    
    void speak(String text) {
        if (!initialized) return;
        
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("AI: Cannot speak (no WiFi)");
            return;
        }
        
        Serial.println("AI: Speaking: " + text);
        
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient https;
        
        if (!https.begin(client, "https://api.openai.com/v1/audio/speech")) {
            Serial.println("AI: Failed to connect to TTS API");
            return;
        }
        
        https.addHeader("Authorization", "Bearer " + apiKey);
        https.addHeader("Content-Type", "application/json");
        https.setTimeout(30000);
        
        // Build JSON request
        DynamicJsonDocument doc(1024);
        doc["model"] = TTS_MODEL;
        doc["input"] = text;
        doc["voice"] = TTS_VOICE;
        doc["response_format"] = "pcm";
        doc["speed"] = TTS_SPEED;
        
        String jsonPayload;
        serializeJson(doc, jsonPayload);
        
        int httpCode = https.POST(jsonPayload);
        
        if (httpCode == HTTP_CODE_OK) {
            setupI2S(1);  // Speaker mode
            
            WiFiClient* stream = https.getStreamPtr();
            uint8_t buffer[512];
            size_t bytesWritten;
            
            while (https.connected() && (https.getSize() > 0 || https.getSize() == -1)) {
                size_t available = stream->available();
                if (available) {
                    int bytesRead = stream->readBytes(buffer, min(available, sizeof(buffer)));
                    i2s_write((i2s_port_t)SPK_I2S_NUM, buffer, bytesRead, &bytesWritten, portMAX_DELAY);
                }
                delay(1);
            }
            
            // Add silence padding
            memset(buffer, 0, sizeof(buffer));
            i2s_write((i2s_port_t)SPK_I2S_NUM, buffer, sizeof(buffer), &bytesWritten, portMAX_DELAY);
            
            Serial.println("AI: Speech complete");
        } else {
            Serial.printf("AI: TTS failed (HTTP %d)\n", httpCode);
        }
        
        https.end();
        
        // Disable speaker amplifier
        digitalWrite(SPK_SD_MODE, LOW);
    }
};

#endif // VOLT_AI_H
