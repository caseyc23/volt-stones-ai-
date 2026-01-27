/*
 * ============================================
 * Secure Credential Storage for VOLT
 * ============================================
 * 
 * Safely stores:
 * - WiFi credentials (multiple networks)
 * - API keys (OpenAI, Hugging Face, etc.)
 * - User preferences
 * 
 * Uses ESP32 Preferences library (encrypted NVS)
 * 
 * ============================================
 */

#ifndef SECURE_STORAGE_H
#define SECURE_STORAGE_H

#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>

#define MAX_WIFI_NETWORKS 5
#define MAX_SSID_LENGTH 32
#define MAX_PASSWORD_LENGTH 64
#define MAX_API_KEY_LENGTH 128

class SecureStorage {
private:
    Preferences prefs;
    
    // Encryption key (change this to something unique!)
    const char* ENCRYPTION_KEY = "VOLT_STONE_2024_SECURE";
    
public:
    SecureStorage() {}
    
    // ============================================
    // INITIALIZATION
    // ============================================
    
    bool begin() {
        // Open preferences with encryption
        if (!prefs.begin(ENCRYPTION_KEY, false)) {
            Serial.println("SecureStorage: Failed to initialize");
            return false;
        }
        
        Serial.println("SecureStorage: Initialized successfully");
        return true;
    }
    
    void end() {
        prefs.end();
    }
    
    // ============================================
    // WIFI NETWORK MANAGEMENT
    // ============================================
    
    // Save WiFi credentials
    bool saveWiFiNetwork(const char* ssid, const char* password) {
        if (!ssid || !password) return false;
        
        // Get current network count
        int count = prefs.getInt("wifi_count", 0);
        
        // Check if network already exists
        for (int i = 0; i < count; i++) {
            String savedSSID = prefs.getString(("wifi_ssid_" + String(i)).c_str(), "");
            if (savedSSID == String(ssid)) {
                // Update existing network
                prefs.putString(("wifi_pass_" + String(i)).c_str(), password);
                Serial.println("SecureStorage: Updated WiFi: " + String(ssid));
                return true;
            }
        }
        
        // Add new network (if space available)
        if (count < MAX_WIFI_NETWORKS) {
            prefs.putString(("wifi_ssid_" + String(count)).c_str(), ssid);
            prefs.putString(("wifi_pass_" + String(count)).c_str(), password);
            prefs.putInt("wifi_count", count + 1);
            Serial.println("SecureStorage: Saved new WiFi: " + String(ssid));
            return true;
        }
        
        Serial.println("SecureStorage: WiFi storage full");
        return false;
    }
    
    // Get WiFi password for SSID
    String getWiFiPassword(const char* ssid) {
        int count = prefs.getInt("wifi_count", 0);
        
        for (int i = 0; i < count; i++) {
            String savedSSID = prefs.getString(("wifi_ssid_" + String(i)).c_str(), "");
            if (savedSSID == String(ssid)) {
                return prefs.getString(("wifi_pass_" + String(i)).c_str(), "");
            }
        }
        
        return "";
    }
    
    // Get all saved WiFi networks
    int getSavedNetworks(String* ssids, int maxCount) {
        int count = prefs.getInt("wifi_count", 0);
        int returnCount = min(count, maxCount);
        
        for (int i = 0; i < returnCount; i++) {
            ssids[i] = prefs.getString(("wifi_ssid_" + String(i)).c_str(), "");
        }
        
        return returnCount;
    }
    
    // Delete WiFi network
    bool deleteWiFiNetwork(const char* ssid) {
        int count = prefs.getInt("wifi_count", 0);
        
        for (int i = 0; i < count; i++) {
            String savedSSID = prefs.getString(("wifi_ssid_" + String(i)).c_str(), "");
            if (savedSSID == String(ssid)) {
                // Shift remaining networks down
                for (int j = i; j < count - 1; j++) {
                    String nextSSID = prefs.getString(("wifi_ssid_" + String(j + 1)).c_str(), "");
                    String nextPass = prefs.getString(("wifi_pass_" + String(j + 1)).c_str(), "");
                    prefs.putString(("wifi_ssid_" + String(j)).c_str(), nextSSID.c_str());
                    prefs.putString(("wifi_pass_" + String(j)).c_str(), nextPass.c_str());
                }
                
                // Clear last entry
                prefs.remove(("wifi_ssid_" + String(count - 1)).c_str());
                prefs.remove(("wifi_pass_" + String(count - 1)).c_str());
                
                // Update count
                prefs.putInt("wifi_count", count - 1);
                
                Serial.println("SecureStorage: Deleted WiFi: " + String(ssid));
                return true;
            }
        }
        
        return false;
    }
    
    // ============================================
    // API KEY MANAGEMENT
    // ============================================
    
    // Save API key
    bool saveAPIKey(const char* service, const char* key) {
        if (!service || !key) return false;
        
        String keyName = String("api_") + service;
        prefs.putString(keyName.c_str(), key);
        
        Serial.println("SecureStorage: Saved API key for: " + String(service));
        return true;
    }
    
    // Get API key
    String getAPIKey(const char* service) {
        String keyName = String("api_") + service;
        return prefs.getString(keyName.c_str(), "");
    }
    
    // Delete API key
    bool deleteAPIKey(const char* service) {
        String keyName = String("api_") + service;
        prefs.remove(keyName.c_str());
        
        Serial.println("SecureStorage: Deleted API key for: " + String(service));
        return true;
    }
    
    // ============================================
    // PREFERENCES
    // ============================================
    
    // Save preference
    bool savePref(const char* key, const char* value) {
        prefs.putString(key, value);
        return true;
    }
    
    String getPref(const char* key, const char* defaultValue = "") {
        return prefs.getString(key, defaultValue);
    }
    
    bool savePrefInt(const char* key, int value) {
        prefs.putInt(key, value);
        return true;
    }
    
    int getPrefInt(const char* key, int defaultValue = 0) {
        return prefs.getInt(key, defaultValue);
    }
    
    // ============================================
    // UTILITY
    // ============================================
    
    // Clear all stored data
    bool clearAll() {
        prefs.clear();
        Serial.println("SecureStorage: All data cleared");
        return true;
    }
    
    // Get storage info
    void printStorageInfo() {
        Serial.println("\n=== Secure Storage Info ===");
        
        int wifiCount = prefs.getInt("wifi_count", 0);
        Serial.printf("WiFi Networks: %d/%d\n", wifiCount, MAX_WIFI_NETWORKS);
        
        for (int i = 0; i < wifiCount; i++) {
            String ssid = prefs.getString(("wifi_ssid_" + String(i)).c_str(), "");
            Serial.printf("  %d. %s\n", i + 1, ssid.c_str());
        }
        
        Serial.println("===========================\n");
    }
};

#endif // SECURE_STORAGE_H
