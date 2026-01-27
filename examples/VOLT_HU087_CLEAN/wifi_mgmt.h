/*
 * ============================================
 * WiFi Management - Simplified
 * ============================================
 * 
 * Handles:
 * - WiFi connection
 * - AP mode for setup
 * - Connection status
 * 
 * Optimized for Stone's HU-087 watch
 * 
 * ============================================
 */

#ifndef WIFI_MGMT_H
#define WIFI_MGMT_H

#include <Arduino.h>
#include <WiFi.h>
#include "config_stone.h"

class WiFiManager {
private:
    String ssid;
    String password;
    
public:
    WiFiManager() {}
    
    bool connect(const char* wifiSSID, const char* wifiPassword, int timeout) {
        ssid = String(wifiSSID);
        password = String(wifiPassword);
        
        Serial.println("WiFi: Connecting to " + ssid);
        
        WiFi.mode(WIFI_STA);
        WiFi.begin(wifiSSID, wifiPassword);
        
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED && (millis() - startTime < timeout * 1000)) {
            delay(500);
            Serial.print(".");
        }
        Serial.println();
        
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("WiFi: Connected!");
            Serial.println("WiFi: IP address: " + WiFi.localIP().toString());
            return true;
        } else {
            Serial.println("WiFi: Connection failed");
            return false;
        }
    }
    
    bool isConnected() {
        return (WiFi.status() == WL_CONNECTED);
    }
    
    bool startAP(const char* apSSID, const char* apPassword) {
        Serial.println("WiFi: Starting AP mode");
        
        WiFi.mode(WIFI_AP);
        bool success = WiFi.softAP(apSSID, apPassword);
        
        if (success) {
            Serial.println("WiFi: AP started");
            Serial.println("WiFi: AP IP: " + WiFi.softAPIP().toString());
            return true;
        } else {
            Serial.println("WiFi: AP failed to start");
            return false;
        }
    }
    
    void disconnect() {
        WiFi.disconnect();
        Serial.println("WiFi: Disconnected");
    }
    
    String getSSID() {
        return ssid;
    }
    
    String getIP() {
        if (WiFi.status() == WL_CONNECTED) {
            return WiFi.localIP().toString();
        }
        return "Not connected";
    }
    
    int getSignalStrength() {
        if (WiFi.status() == WL_CONNECTED) {
            return WiFi.RSSI();
        }
        return 0;
    }
};

#endif // WIFI_MGMT_H
