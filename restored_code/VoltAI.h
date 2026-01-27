#ifndef VOLT_AI_H
#define VOLT_AI_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <driver/i2s.h>

// Audio Configuration
#define I2S_WS 15
#define I2S_SD 13
#define I2S_SCK 2
#define I2S_PORT I2S_NUM_0
#define SAMPLE_RATE 16000
#define RECORD_TIME_SEC 5
// 16kHz * 2 bytes * 5 seconds = 160KB.
// ESP32-S3 usually has PSRAM. If not, reduce record time.
#define BUFFER_SIZE (SAMPLE_RATE * RECORD_TIME_SEC) 

// AI Configuration
// These are expected to be defined in config.h
// If not, we provide fallbacks
#ifndef GPT_MODEL
#define GPT_MODEL "gpt-4o-mini"
#endif
#ifndef TTS_MODEL
#define TTS_MODEL "tts-1"
#endif

class VoltAI {
private:
    String apiKey;
    String systemPrompt;
    int16_t* audioBuffer;
    bool hasPSRAM;

    void setupI2S(int mode) {
        i2s_driver_uninstall(I2S_PORT); // Clean up previous
        
        i2s_config_t i2s_config = {
            .mode = (mode == 0) ? (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX) : (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
            .sample_rate = SAMPLE_RATE,
            .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
            .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
            .communication_format = I2S_COMM_FORMAT_I2S,
            .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
            .dma_buf_count = 8,
            .dma_buf_len = 64,
            .use_apll = false,
            .tx_desc_auto_clear = (mode == 1), // Auto clear for TX
            .fixed_mclk = 0
        };

        i2s_pin_config_t pin_config = {
            .bck_io_num = I2S_SCK,
            .ws_io_num = I2S_WS,
            .data_out_num = I2S_SD,
            .data_in_num = I2S_SD // Same pin for simplified wiring usually, or separate
        };

        if (i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL) != ESP_OK) {
            Serial.println("Failed to install I2S driver");
        }
        if (i2s_set_pin(I2S_PORT, &pin_config) != ESP_OK) {
            Serial.println("Failed to set I2S pins");
        }
    }

public:
    VoltAI() : audioBuffer(nullptr), hasPSRAM(false) {}

    bool begin(const char* key, const char* prompt) {
        apiKey = String(key);
        systemPrompt = String(prompt);
        
        if (psramInit()) {
            Serial.println("PSRAM found! Allocating large buffer...");
            audioBuffer = (int16_t*)ps_malloc(BUFFER_SIZE * sizeof(int16_t));
            hasPSRAM = true;
        } else {
            Serial.println("No PSRAM. Attempting standard malloc (might fail)...");
            audioBuffer = (int16_t*)malloc(BUFFER_SIZE * sizeof(int16_t));
        }

        if (!audioBuffer) {
            Serial.println("Failed to allocate audio buffer!");
            return false;
        }

        return true;
    }

    // 1. Record Audio
    void recordAudio() {
        Serial.println("Starting recording...");
        setupI2S(0); // RX Mode
        
        size_t bytesRead = 0;
        // Discard first few ms of noise
        int16_t dummy[100];
        i2s_read(I2S_PORT, dummy, sizeof(dummy), &bytesRead, 100);

        // Record loop
        size_t totalBytesRead = 0;
        uint8_t* byteBuffer = (uint8_t*)audioBuffer;
        
        while (totalBytesRead < BUFFER_SIZE * sizeof(int16_t)) {
            size_t bytesToRead = 1024;
            if (totalBytesRead + bytesToRead > BUFFER_SIZE * sizeof(int16_t)) {
                bytesToRead = (BUFFER_SIZE * sizeof(int16_t)) - totalBytesRead;
            }
            
            i2s_read(I2S_PORT, 
                     byteBuffer + totalBytesRead, 
                     bytesToRead, 
                     &bytesRead, 
                     portMAX_DELAY);
            totalBytesRead += bytesRead;
        }
        Serial.println("Recording finished.");
    }

    // 2. STT (Whisper)
    String transcribeAudio() {
        Serial.println("Transcribing with Whisper...");
        WiFiClientSecure client;
        client.setInsecure(); // For development
        HTTPClient https;

        // Note: Constructing a proper Multipart/Form-data request manually is complex C++.
        // Simplified pseudo-implementation for the HTTP header structure:
        String boundary = "------------------------ESP32Boundary";
        String contentType = "multipart/form-data; boundary=" + boundary;
        
        if (https.begin(client, "https://api.openai.com/v1/audio/transcriptions")) {
            https.addHeader("Authorization", "Bearer " + apiKey);
            https.addHeader("Content-Type", contentType);
            
            // This part requires streaming the buffer. 
            // Writing generic logic here for brevity; usually requires custom stream classes.
            // Returning dummy string for skeleton if buffer send fails.
            
            // In a real implementation we would construct the body:
            // --boundary
            // Content-Disposition: form-data; name="model"
            //
            // whisper-1
            // --boundary
            // Content-Disposition: form-data; name="file"; filename="audio.wav"
            // Content-Type: audio/wav
            // 
            // [BINARY WAV HEADER + DATA]
            // --boundary--

            Serial.println("[Mock] Whisper Request Sent (Not implemented fully in skeleton)");
            return "Hello Volt"; // Mock response for testing flow
        }
        return "";
    }

    // 2b. Simplified Transcribe (Text Input fallback for testing)
    String chatWithGPT(String text) {
        if (text.length() == 0) return "";
        
        Serial.printf("User said: %s\n", text.c_str());
        Serial.println("Asking GPT...");

        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient https;
        
        if (https.begin(client, "https://api.openai.com/v1/chat/completions")) {
            https.addHeader("Authorization", "Bearer " + apiKey);
            https.addHeader("Content-Type", "application/json");
            
            StaticJsonDocument<1024> doc;
            doc["model"] = GPT_MODEL;
            JsonArray messages = doc.createNestedArray("messages");
            
            JsonObject sysMsg = messages.createNestedObject();
            sysMsg["role"] = "system";
            sysMsg["content"] = systemPrompt;
            
            JsonObject userMsg = messages.createNestedObject();
            userMsg["role"] = "user";
            userMsg["content"] = text;
            
            String jsonPayload;
            serializeJson(doc, jsonPayload);
            
            int httpCode = https.POST(jsonPayload);
            
            if (httpCode == HTTP_CODE_OK) {
                String payload = https.getString();
                StaticJsonDocument<2048> responseDoc;
                deserializeJson(responseDoc, payload);
                String reply = responseDoc["choices"][0]["message"]["content"].as<String>();
                Serial.printf("VOLT says: %s\n", reply.c_str());
                return reply;
            } else {
                Serial.printf("GPT Error: %d\n", httpCode);
            }
            https.end();
        }
        return "I had a connection error.";
    }

    // 4. TTS (OpenAI Audio)
    void speakText(String text) {
        Serial.println("Synthesizing speech...");
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient https;
        
        if (https.begin(client, "https://api.openai.com/v1/audio/speech")) {
            https.addHeader("Authorization", "Bearer " + apiKey);
            https.addHeader("Content-Type", "application/json");
            
            StaticJsonDocument<512> doc;
            doc["model"] = TTS_MODEL;
            doc["input"] = text;
            doc["voice"] = TTS_VOICE; // Uses global from config.h
            doc["response_format"] = "pcm"; // RAW PCM!
            doc["speed"] = TTS_SPEED; // Uses global from config.h
            
            String jsonPayload;
            serializeJson(doc, jsonPayload);
            
            int httpCode = https.POST(jsonPayload);
            
            if (httpCode == HTTP_CODE_OK) {
                // Buffer the stream and play
                int len = https.getSize();
                Serial.printf("TTS Audio received: %d bytes\n", len);
                
                // Switch to TX mode
                setupI2S(1);
                
                // Read stream in chunks and play directly
                WiFiClient *stream = https.getStreamPtr();
                uint8_t buff[1024];
                while(https.connected() && (len > 0 || len == -1)) {
                    size_t size = stream->available();
                    if(size) {
                        int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
                        
                        size_t bytesWritten;
                        i2s_write(I2S_PORT, buff, c, &bytesWritten, portMAX_DELAY);
                        
                        if(len > 0) len -= c;
                    }
                    delay(1);
                }
                
                // Zero out to prevent pop
                memset(buff, 0, sizeof(buff));
                size_t w;
                i2s_write(I2S_PORT, buff, sizeof(buff), &w, portMAX_DELAY);
                
                Serial.println("Playback finished.");
            } else {
                Serial.printf("TTS Error: %d\n", httpCode);
            }
            https.end();
        }
    }
};

#endif
