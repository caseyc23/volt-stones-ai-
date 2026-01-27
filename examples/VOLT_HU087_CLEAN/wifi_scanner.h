/*
 * ============================================
 * WiFi Network Scanner & Selector
 * ============================================
 * 
 * Features:
 * - Scan for available WiFi networks
 * - Display networks on screen
 * - Let Stone select network
 * - Save credentials securely
 * - Auto-connect to saved networks
 * 
 * ============================================
 */

#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <Arduino.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include "secure_storage.h"

#define MAX_SCAN_NETWORKS 20

struct WiFiNetwork {
    String ssid;
    int rssi;
    bool encrypted;
    bool saved;
};

class WiFiScanner {
private:
    TFT_eSPI* display;
    SecureStorage* storage;
    WiFiNetwork networks[MAX_SCAN_NETWORKS];
    int networkCount;
    int selectedIndex;
    
public:
    WiFiScanner(TFT_eSPI* disp, SecureStorage* store) : 
        display(disp), storage(store), networkCount(0), selectedIndex(0) {}
    
    // ============================================
    // NETWORK SCANNING
    // ============================================
    
    int scanNetworks() {
        display->fillScreen(TFT_BLACK);
        display->setTextSize(2);
        display->setCursor(10, 60);
        display->setTextColor(TFT_CYAN);
        display->println("Scanning");
        display->setCursor(10, 90);
        display->println("WiFi...");
        
        Serial.println("WiFiScanner: Scanning for networks...");
        
        // Scan for networks
        int n = WiFi.scanNetworks();
        networkCount = min(n, MAX_SCAN_NETWORKS);
        
        Serial.printf("WiFiScanner: Found %d networks\n", n);
        
        // Store network info
        for (int i = 0; i < networkCount; i++) {
            networks[i].ssid = WiFi.SSID(i);
            networks[i].rssi = WiFi.RSSI(i);
            networks[i].encrypted = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
            
            // Check if saved
            String savedPass = storage->getWiFiPassword(networks[i].ssid.c_str());
            networks[i].saved = (savedPass.length() > 0);
            
            Serial.printf("  %d. %s (%d dBm) %s %s\n", 
                i + 1, 
                networks[i].ssid.c_str(), 
                networks[i].rssi,
                networks[i].encrypted ? "[🔒]" : "[Open]",
                networks[i].saved ? "[Saved]" : "");
        }
        
        // Sort by signal strength
        sortNetworksBySignal();
        
        return networkCount;
    }
    
    // ============================================
    // NETWORK DISPLAY
    // ============================================
    
    void displayNetworks(int startIndex = 0) {
        display->fillScreen(TFT_BLACK);
        display->setTextSize(1);
        
        // Title
        display->setCursor(10, 5);
        display->setTextColor(TFT_CYAN);
        display->println("WiFi Networks:");
        
        // Show up to 10 networks
        int maxDisplay = min(10, networkCount - startIndex);
        
        for (int i = 0; i < maxDisplay; i++) {
            int index = startIndex + i;
            int y = 25 + (i * 28);
            
            // Highlight selected
            if (index == selectedIndex) {
                display->fillRect(0, y - 2, 172, 26, TFT_DARKGREY);
            }
            
            // SSID
            display->setCursor(5, y);
            display->setTextColor(networks[index].saved ? TFT_GREEN : TFT_WHITE);
            
            String displayName = networks[index].ssid;
            if (displayName.length() > 18) {
                displayName = displayName.substring(0, 15) + "...";
            }
            display->println(displayName);
            
            // Signal strength bars
            display->setCursor(5, y + 12);
            display->setTextColor(TFT_YELLOW);
            int bars = getSignalBars(networks[index].rssi);
            for (int b = 0; b < bars; b++) {
                display->print("▮");
            }
            
            // Lock icon if encrypted
            if (networks[index].encrypted) {
                display->setCursor(150, y);
                display->setTextColor(TFT_RED);
                display->print("🔒");
            }
            
            // Saved indicator
            if (networks[index].saved) {
                display->setCursor(135, y + 12);
                display->setTextColor(TFT_GREEN);
                display->print("✓");
            }
        }
        
        // Instructions
        display->setCursor(5, 300);
        display->setTextColor(TFT_CYAN);
        display->println("Press to select");
    }
    
    // ============================================
    // NETWORK SELECTION
    // ============================================
    
    void selectNext() {
        selectedIndex = (selectedIndex + 1) % networkCount;
        displayNetworks(max(0, selectedIndex - 5));
    }
    
    void selectPrevious() {
        selectedIndex = (selectedIndex - 1 + networkCount) % networkCount;
        displayNetworks(max(0, selectedIndex - 5));
    }
    
    WiFiNetwork getSelectedNetwork() {
        if (selectedIndex >= 0 && selectedIndex < networkCount) {
            return networks[selectedIndex];
        }
        return WiFiNetwork();
    }
    
    // ============================================
    // AUTO-CONNECT
    // ============================================
    
    bool autoConnect(int timeout = 20) {
        Serial.println("WiFiScanner: Attempting auto-connect...");
        
        // Get saved networks
        String savedSSIDs[MAX_WIFI_NETWORKS];
        int savedCount = storage->getSavedNetworks(savedSSIDs, MAX_WIFI_NETWORKS);
        
        if (savedCount == 0) {
            Serial.println("WiFiScanner: No saved networks");
            return false;
        }
        
        // Scan for networks
        int n = WiFi.scanNetworks();
        
        // Try to connect to saved networks in order of signal strength
        for (int i = 0; i < n; i++) {
            String scannedSSID = WiFi.SSID(i);
            
            // Check if this network is saved
            for (int j = 0; j < savedCount; j++) {
                if (scannedSSID == savedSSIDs[j]) {
                    String password = storage->getWiFiPassword(scannedSSID.c_str());
                    
                    if (password.length() > 0) {
                        Serial.println("WiFiScanner: Trying " + scannedSSID);
                        
                        display->fillScreen(TFT_BLACK);
                        display->setTextSize(1);
                        display->setCursor(10, 60);
                        display->setTextColor(TFT_CYAN);
                        display->println("Connecting to:");
                        display->setCursor(10, 80);
                        display->setTextColor(TFT_WHITE);
                        display->println(scannedSSID);
                        
                        WiFi.begin(scannedSSID.c_str(), password.c_str());
                        
                        unsigned long startTime = millis();
                        while (WiFi.status() != WL_CONNECTED && 
                               (millis() - startTime < timeout * 1000)) {
                            delay(500);
                            Serial.print(".");
                        }
                        Serial.println();
                        
                        if (WiFi.status() == WL_CONNECTED) {
                            Serial.println("WiFiScanner: Connected to " + scannedSSID);
                            
                            display->setCursor(10, 100);
                            display->setTextColor(TFT_GREEN);
                            display->println("Connected!");
                            delay(1000);
                            
                            return true;
                        } else {
                            Serial.println("WiFiScanner: Failed to connect to " + scannedSSID);
                        }
                    }
                }
            }
        }
        
        Serial.println("WiFiScanner: Auto-connect failed");
        return false;
    }
    
    // ============================================
    // PASSWORD INPUT
    // ============================================
    
    String inputPassword(const char* ssid) {
        // For now, return empty string
        // In full implementation, this would show an on-screen keyboard
        // or use a web interface for password entry
        
        display->fillScreen(TFT_BLACK);
        display->setTextSize(1);
        display->setCursor(10, 60);
        display->setTextColor(TFT_YELLOW);
        display->println("Password needed for:");
        display->setCursor(10, 80);
        display->setTextColor(TFT_WHITE);
        display->println(ssid);
        display->setCursor(10, 110);
        display->setTextColor(TFT_CYAN);
        display->println("Use WiFi Setup mode");
        display->setCursor(10, 130);
        display->println("(5 button presses)");
        
        delay(3000);
        return "";
    }
    
    // ============================================
    // UTILITIES
    // ============================================
    
private:
    void sortNetworksBySignal() {
        // Simple bubble sort by RSSI
        for (int i = 0; i < networkCount - 1; i++) {
            for (int j = 0; j < networkCount - i - 1; j++) {
                if (networks[j].rssi < networks[j + 1].rssi) {
                    WiFiNetwork temp = networks[j];
                    networks[j] = networks[j + 1];
                    networks[j + 1] = temp;
                }
            }
        }
    }
    
    int getSignalBars(int rssi) {
        if (rssi >= -50) return 4;
        if (rssi >= -60) return 3;
        if (rssi >= -70) return 2;
        if (rssi >= -80) return 1;
        return 0;
    }
};

#endif // WIFI_SCANNER_H
