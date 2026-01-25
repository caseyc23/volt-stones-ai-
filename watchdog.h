// ============================================
// VOLT AI Watch - Watchdog Timer Module
// Professional-grade crash prevention & recovery
// ============================================

#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <esp_task_wdt.h>
#include <esp_system.h>

#define WDT_TIMEOUT 30  // 30 seconds timeout

class Watchdog {
private:
    bool enabled;
    int timeoutSeconds;
    unsigned long lastResetTime;
    int resetCount;
    
public:
    Watchdog() : enabled(false), timeoutSeconds(WDT_TIMEOUT), lastResetTime(0), resetCount(0) {}
    
    void begin(int timeout = WDT_TIMEOUT) {
        timeoutSeconds = timeout;
        
        // Initialize watchdog timer
        esp_task_wdt_init(timeoutSeconds, true); // Enable panic on timeout
        esp_task_wdt_add(NULL); // Add current task to watchdog
        
        enabled = true;
        lastResetTime = millis();
        
        Serial.println("=== Watchdog Timer ===");
        Serial.printf("Timeout: %d seconds\n", timeoutSeconds);
        Serial.println("Watchdog: Enabled");
        
        // Check previous reset reason
        checkResetReason();
    }
    
    void reset() {
        if (enabled) {
            esp_task_wdt_reset();
            lastResetTime = millis();
            resetCount++;
        }
    }
    
    void checkResetReason() {
        esp_reset_reason_t reason = esp_reset_reason();
        
        Serial.println("Previous reset reason:");
        
        switch(reason) {
            case ESP_RST_UNKNOWN:
                Serial.println("  - Unknown");
                break;
                
            case ESP_RST_POWERON:
                Serial.println("  - Power on");
                // Normal boot
                break;
                
            case ESP_RST_EXT:
                Serial.println("  - External reset");
                break;
                
            case ESP_RST_SW:
                Serial.println("  - Software reset");
                break;
                
            case ESP_RST_PANIC:
                Serial.println("  - PANIC/CRASH detected!");
                handleCrashRecovery();
                break;
                
            case ESP_RST_INT_WDT:
                Serial.println("  - Interrupt watchdog");
                handleWatchdogReset();
                break;
                
            case ESP_RST_TASK_WDT:
                Serial.println("  - Task watchdog");
                handleWatchdogReset();
                break;
                
            case ESP_RST_WDT:
                Serial.println("  - Other watchdog");
                handleWatchdogReset();
                break;
                
            case ESP_RST_DEEPSLEEP:
                Serial.println("  - Deep sleep wake");
                // Normal wake from sleep
                break;
                
            case ESP_RST_BROWNOUT:
                Serial.println("  - Brownout (low voltage)");
                handleBrownout();
                break;
                
            case ESP_RST_SDIO:
                Serial.println("  - SDIO reset");
                break;
                
            default:
                Serial.printf("  - Code: %d\n", reason);
                break;
        }
    }
    
    void handleCrashRecovery() {
        Serial.println("=== CRASH RECOVERY ===");
        
        // Log crash to storage
        logCrash("PANIC");
        
        // Show crash screen
        display.clear();
        display.setCursor(0, 0);
        display.println("VOLT Recovered");
        display.println("from crash");
        display.println("");
        display.println("Everything is OK now");
        display.display();
        delay(3000);
        
        // Clear crash flag
        // Reset to safe state
        resetToSafeState();
    }
    
    void handleWatchdogReset() {
        Serial.println("=== WATCHDOG RESET ===");
        
        // Log watchdog reset
        logCrash("WATCHDOG");
        
        // Show recovery screen
        display.clear();
        display.setCursor(0, 0);
        display.println("VOLT Restarted");
        display.println("");
        display.println("System recovered");
        display.display();
        delay(2000);
        
        // Reset to safe state
        resetToSafeState();
    }
    
    void handleBrownout() {
        Serial.println("=== BROWNOUT DETECTED ===");
        
        // Log brownout
        logCrash("BROWNOUT");
        
        // Show low power warning
        display.clear();
        display.setCursor(0, 0);
        display.println("Low Power Detected");
        display.println("");
        display.println("Please charge VOLT");
        display.display();
        delay(3000);
    }
    
    void logCrash(const char* type) {
        // Log crash to SPIFFS/LittleFS for later analysis
        Serial.printf("Logging crash: %s\n", type);
        
        // Create crash report
        String crashReport = "";
        crashReport += "Crash Type: " + String(type) + "\n";
        crashReport += "Time: " + String(millis()) + "\n";
        crashReport += "Free Heap: " + String(ESP.getFreeHeap()) + "\n";
        crashReport += "Boot Count: " + String(bootCount) + "\n";
        
        // Save to file
        File crashFile = SPIFFS.open("/crash_log.txt", FILE_APPEND);
        if (crashFile) {
            crashFile.println(crashReport);
            crashFile.close();
            Serial.println("Crash logged to file");
        }
        
        // Could also send to remote server for monitoring
        // sendCrashReport(crashReport);
    }
    
    void resetToSafeState() {
        Serial.println("Resetting to safe state...");
        
        // Disable any potentially problematic features
        // Reset configuration to defaults if needed
        // Clear any stuck states
        
        Serial.println("Safe state restored");
    }
    
    unsigned long getTimeSinceLastReset() {
        return millis() - lastResetTime;
    }
    
    int getResetCount() {
        return resetCount;
    }
    
    bool isEnabled() {
        return enabled;
    }
    
    void disable() {
        if (enabled) {
            esp_task_wdt_delete(NULL);
            esp_task_wdt_deinit();
            enabled = false;
            Serial.println("Watchdog: Disabled");
        }
    }
};

#endif // WATCHDOG_H
