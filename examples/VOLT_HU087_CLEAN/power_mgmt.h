/*
 * ============================================
 * Power Management - Simplified
 * ============================================
 * 
 * Handles:
 * - Deep sleep
 * - Idle timeout
 * - Battery monitoring
 * - Wake-up
 * 
 * Optimized for Stone's HU-087 watch
 * 
 * ============================================
 */

#ifndef POWER_MGMT_H
#define POWER_MGMT_H

#include <Arduino.h>
#include "config_stone.h"
#include "pins_hu087.h"

class PowerManager {
private:
    unsigned long lastActivityTime;
    int sleepTimeout;  // in seconds
    
public:
    PowerManager() : lastActivityTime(0), sleepTimeout(SLEEP_TIMEOUT) {}
    
    void begin() {
        lastActivityTime = millis();
        
        // Configure wake-up source (button)
        esp_sleep_enable_ext0_wakeup((gpio_num_t)BTN_BOOT, 0);  // Wake on LOW
        
        Serial.println("Power: Initialized");
    }
    
    void keepAlive() {
        // Called regularly to prevent watchdog timeout
        delay(1);
    }
    
    void resetIdleTimer() {
        lastActivityTime = millis();
    }
    
    bool shouldSleep() {
        unsigned long idleTime = (millis() - lastActivityTime) / 1000;  // Convert to seconds
        return (idleTime >= sleepTimeout);
    }
    
    void enterDeepSleep() {
        Serial.println("Power: Entering deep sleep...");
        
        // Disable speaker amplifier
        digitalWrite(SPK_SD_MODE, LOW);
        
        // Turn off LED
        digitalWrite(LED_BUILTIN, LOW);
        
        delay(100);
        
        // Enter deep sleep
        esp_deep_sleep_start();
    }
    
    int getBatteryPercent() {
        // Simple battery estimation
        // TODO: Implement actual ADC reading if battery pin available
        
        #ifdef BATTERY_ADC
        int raw = analogRead(BATTERY_ADC);
        float voltage = (raw / 4095.0) * 3.3 * 2.0;  // Assuming voltage divider
        
        // LiPo voltage to percentage (approximate)
        if (voltage >= 4.2) return 100;
        if (voltage >= 4.0) return 80;
        if (voltage >= 3.8) return 60;
        if (voltage >= 3.6) return 40;
        if (voltage >= 3.4) return 20;
        return 10;
        #else
        // Return estimated value if no ADC
        unsigned long uptime = millis() / 1000 / 60;  // minutes
        int estimated = 100 - (uptime / 10);  // Rough estimate: 1% per 10 min
        return max(10, min(100, estimated));
        #endif
    }
};

#endif // POWER_MGMT_H
