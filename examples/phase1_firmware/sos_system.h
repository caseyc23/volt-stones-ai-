#ifndef SOS_SYSTEM_H
#define SOS_SYSTEM_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_SSD1306.h>

class SOSSystem {
private:
    int buzzerPin;
    Adafruit_SSD1306* display;
    
    bool sosActive;
    unsigned long sosLastTriggered;
    const unsigned long SOS_COOLDOWN = 60000;  // 1 minute cooldown
    
    String apiEndpoint;
    String apiKey;
    String deviceId;
    String childName;
    
public:
    SOSSystem() : buzzerPin(-1), display(nullptr), sosActive(false), 
                  sosLastTriggered(0) {}
    
    void begin(int buzzer, Adafruit_SSD1306* disp) {
        buzzerPin = buzzer;
        display = disp;
        pinMode(buzzerPin, OUTPUT);
        digitalWrite(buzzerPin, LOW);
        Serial.println("SOS: System initialized");
    }
    
    void setAPIConfig(String endpoint, String key, String devId, String name) {
        apiEndpoint = endpoint;
        apiKey = key;
        deviceId = devId;
        childName = name;
    }
    
    bool trigger(double latitude, double longitude, bool gpsValid, int battery) {
        // Check cooldown
        if (millis() - sosLastTriggered < SOS_COOLDOWN) {
            Serial.println("SOS: Cooldown active, ignoring trigger");
            return false;
        }
        
        sosActive = true;
        sosLastTriggered = millis();
        
        Serial.println("🚨🚨🚨 SOS ACTIVATED! 🚨🚨🚨");
        
        // Visual feedback
        showSOSScreen();
        
        // Audio feedback
        playSOSAlarm();
        
        // Send alert
        bool sent = sendSOSAlert(latitude, longitude, gpsValid, battery);
        
        sosActive = false;
        
        return sent;
    }
    
    void showSOSScreen() {
        if (!display) return;
        
        display->clearDisplay();
        display->setTextSize(3);
        display->setCursor(10, 15);
        display->println("SOS!");
        display->setTextSize(1);
        display->setCursor(0, 45);
        display->println("Help is coming!");
        display->display();
    }
    
    void playSOSAlarm() {
        // SOS pattern in Morse code: ... --- ...
        // Short beep = dot, Long beep = dash
        
        // S (...)
        for (int i = 0; i < 3; i++) {
            tone(buzzerPin, 1000, 200);
            delay(200);
            noTone(buzzerPin);
            delay(200);
        }
        
        delay(400);
        
        // O (---)
        for (int i = 0; i < 3; i++) {
            tone(buzzerPin, 1000, 600);
            delay(600);
            noTone(buzzerPin);
            delay(200);
        }
        
        delay(400);
        
        // S (...)
        for (int i = 0; i < 3; i++) {
            tone(buzzerPin, 1000, 200);
            delay(200);
            noTone(buzzerPin);
            delay(200);
        }
    }
    
    bool sendSOSAlert(double latitude, double longitude, bool gpsValid, int battery) {
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("SOS: No WiFi connection, cannot send alert");
            return false;
        }
        
        HTTPClient http;
        String url = apiEndpoint + "/api/device/" + deviceId + "/sos";
        
        http.begin(url);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("X-API-Key", apiKey);
        
        StaticJsonDocument<512> doc;
        doc["device_id"] = deviceId;
        doc["child_name"] = childName;
        doc["timestamp"] = millis();
        doc["type"] = "SOS";
        doc["priority"] = "CRITICAL";
        
        JsonObject location = doc.createNestedObject("location");
        location["latitude"] = latitude;
        location["longitude"] = longitude;
        location["valid"] = gpsValid;
        
        doc["battery"] = battery;
        doc["wifi_rssi"] = WiFi.RSSI();
        
        String payload;
        serializeJson(doc, payload);
        
        Serial.println("SOS: Sending alert...");
        Serial.println(payload);
        
        int httpCode = http.POST(payload);
        
        bool success = false;
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
            Serial.println("SOS: Alert sent successfully!");
            success = true;
            
            // Show success message
            if (display) {
                display->clearDisplay();
                display->setTextSize(1);
                display->setCursor(0, 20);
                display->println("SOS Alert Sent!");
                display->println("Help is on the way");
                display->display();
                delay(3000);
            }
        } else {
            Serial.printf("SOS: Alert failed (HTTP %d)\n", httpCode);
            String response = http.getString();
            Serial.println("Response: " + response);
            
            // Show error message
            if (display) {
                display->clearDisplay();
                display->setTextSize(1);
                display->setCursor(0, 20);
                display->println("SOS Alert Failed");
                display->println("Retrying...");
                display->display();
            }
            
            // Retry once
            delay(2000);
            httpCode = http.POST(payload);
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
                Serial.println("SOS: Alert sent on retry!");
                success = true;
            }
        }
        
        http.end();
        return success;
    }
    
    bool isActive() {
        return sosActive;
    }
    
    unsigned long getLastTriggerTime() {
        return sosLastTriggered;
    }
    
    bool canTrigger() {
        return (millis() - sosLastTriggered >= SOS_COOLDOWN);
    }
    
    // Test SOS system (without sending alert)
    void test() {
        Serial.println("SOS: Testing system...");
        showSOSScreen();
        delay(2000);
        playSOSAlarm();
        Serial.println("SOS: Test complete");
    }
};

#endif
