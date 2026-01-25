// ============================================
// VOLT AI Watch - OTA Update Module
// Professional-grade Over-The-Air updates
// ============================================

#ifndef OTA_UPDATE_H
#define OTA_UPDATE_H

#include <ArduinoOTA.h>
#include <WiFi.h>

class OTAUpdate {
private:
    bool enabled;
    String hostname;
    String password;
    
    static void onStart() {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
        Serial.println("OTA: Start updating " + type);
        
        // Show on display
        display.clear();
        display.setCursor(0, 0);
        display.println("UPDATING VOLT...");
        display.println("Do not power off!");
        display.display();
    }
    
    static void onEnd() {
        Serial.println("\nOTA: Update complete!");
        display.clear();
        display.setCursor(0, 0);
        display.println("Update Complete!");
        display.println("Restarting...");
        display.display();
    }
    
    static void onProgress(unsigned int progress, unsigned int total) {
        static unsigned int lastPercent = 0;
        unsigned int percent = (progress / (total / 100));
        
        if (percent != lastPercent && percent % 10 == 0) {
            Serial.printf("OTA Progress: %u%%\n", percent);
            
            // Update display every 10%
            display.clear();
            display.setCursor(0, 0);
            display.println("UPDATING VOLT");
            display.printf("Progress: %u%%\n", percent);
            display.println("Please wait...");
            display.display();
            
            lastPercent = percent;
        }
    }
    
    static void onError(ota_error_t error) {
        Serial.printf("OTA Error[%u]: ", error);
        String errorMsg = "";
        
        switch(error) {
            case OTA_AUTH_ERROR:
                errorMsg = "Auth Failed";
                Serial.println("Auth Failed");
                break;
            case OTA_BEGIN_ERROR:
                errorMsg = "Begin Failed";
                Serial.println("Begin Failed");
                break;
            case OTA_CONNECT_ERROR:
                errorMsg = "Connect Failed";
                Serial.println("Connect Failed");
                break;
            case OTA_RECEIVE_ERROR:
                errorMsg = "Receive Failed";
                Serial.println("Receive Failed");
                break;
            case OTA_END_ERROR:
                errorMsg = "End Failed";
                Serial.println("End Failed");
                break;
        }
        
        display.clear();
        display.setCursor(0, 0);
        display.println("Update Failed!");
        display.println(errorMsg);
        display.println("Please try again");
        display.display();
    }

public:
    OTAUpdate() : enabled(false), hostname("VOLT-Watch"), password("volt2024") {}
    
    void begin(const char* deviceHostname = nullptr, const char* otaPassword = nullptr) {
        if (deviceHostname) hostname = deviceHostname;
        if (otaPassword) password = otaPassword;
        
        // Set hostname
        ArduinoOTA.setHostname(hostname.c_str());
        
        // Set password for security
        ArduinoOTA.setPassword(password.c_str());
        
        // Set port (default 3232)
        ArduinoOTA.setPort(3232);
        
        // Configure callbacks
        ArduinoOTA.onStart(onStart);
        ArduinoOTA.onEnd(onEnd);
        ArduinoOTA.onProgress(onProgress);
        ArduinoOTA.onError(onError);
        
        // Start OTA service
        ArduinoOTA.begin();
        
        enabled = true;
        
        Serial.println("OTA Update: Enabled");
        Serial.printf("OTA Hostname: %s\n", hostname.c_str());
        Serial.println("OTA Port: 3232");
        Serial.println("OTA Password: Protected");
    }
    
    void handle() {
        if (enabled) {
            ArduinoOTA.handle();
        }
    }
    
    bool isEnabled() {
        return enabled;
    }
    
    String getHostname() {
        return hostname;
    }
};

#endif // OTA_UPDATE_H
