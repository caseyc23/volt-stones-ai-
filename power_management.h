// ============================================
// VOLT AI Watch - Power Management Module
// Professional-grade deep sleep & battery optimization
// ============================================

#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H

#include <esp_sleep.h>
#include <esp_wifi.h>
#include <driver/rtc_io.h>

// RTC memory to persist across deep sleep
RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR int wakeupReason = 0;
RTC_DATA_ATTR unsigned long lastActiveTime = 0;

class PowerManagement {
private:
    int sleepTimeoutMinutes;
    gpio_num_t wakeupButtonPin;
    bool deepSleepEnabled;
    unsigned long lastActivityTime;
    
public:
    PowerManagement() : 
        sleepTimeoutMinutes(5),
        wakeupButtonPin(GPIO_NUM_0),
        deepSleepEnabled(true),
        lastActivityTime(0) {}
    
    void begin(gpio_num_t buttonPin = GPIO_NUM_0, int timeoutMinutes = 5) {
        wakeupButtonPin = buttonPin;
        sleepTimeoutMinutes = timeoutMinutes;
        lastActivityTime = millis();
        
        // Increment boot count
        bootCount++;
        
        Serial.println("=== Power Management ===");
        Serial.printf("Boot count: %d\n", bootCount);
        
        // Check wakeup reason
        checkWakeupReason();
        
        // Configure wakeup sources
        configureWakeupSources();
        
        Serial.println("Power Management: Initialized");
    }
    
    void checkWakeupReason() {
        esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
        
        switch(wakeup_reason) {
            case ESP_SLEEP_WAKEUP_EXT0:
                Serial.println("Wakeup: Button press");
                wakeupReason = 1;
                // Show wake animation
                showWakeAnimation();
                break;
                
            case ESP_SLEEP_WAKEUP_TIMER:
                Serial.println("Wakeup: Timer");
                wakeupReason = 2;
                // Check for scheduled tasks
                checkScheduledTasks();
                break;
                
            case ESP_SLEEP_WAKEUP_TOUCHPAD:
                Serial.println("Wakeup: Touch");
                wakeupReason = 3;
                break;
                
            case ESP_SLEEP_WAKEUP_ULP:
                Serial.println("Wakeup: ULP program");
                wakeupReason = 4;
                break;
                
            default:
                Serial.println("Wakeup: Power on or reset");
                wakeupReason = 0;
                // First boot - show welcome screen
                showWelcomeScreen();
                break;
        }
    }
    
    void configureWakeupSources() {
        // Configure button wakeup (EXT0)
        esp_sleep_enable_ext0_wakeup(wakeupButtonPin, 0); // Wake on LOW (button press)
        
        // Configure timer wakeup (for periodic checks)
        // Wake up every hour to check for updates, sync time, etc.
        esp_sleep_enable_timer_wakeup(60 * 60 * 1000000ULL); // 1 hour in microseconds
        
        Serial.println("Wakeup sources configured:");
        Serial.printf("  - Button (GPIO %d)\n", wakeupButtonPin);
        Serial.println("  - Timer (1 hour)");
    }
    
    void enterDeepSleep(const char* reason = "Timeout") {
        if (!deepSleepEnabled) {
            Serial.println("Deep sleep disabled");
            return;
        }
        
        Serial.printf("Entering deep sleep: %s\n", reason);
        
        // Save current state
        saveState();
        
        // Show sleep screen
        display.clear();
        display.setCursor(0, 0);
        display.println("Going to sleep...");
        display.println("Press button to wake");
        display.display();
        delay(2000);
        
        // Turn off display
        display.powerOff();
        
        // Disable WiFi to save power
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        esp_wifi_stop();
        
        // Disable Bluetooth
        btStop();
        
        // Configure GPIO for minimal power consumption
        configureGPIOForSleep();
        
        // Enter deep sleep
        Serial.println("Entering deep sleep now...");
        Serial.flush();
        
        esp_deep_sleep_start();
    }
    
    void enterLightSleep(int seconds) {
        Serial.printf("Entering light sleep for %d seconds\n", seconds);
        
        // Configure timer wakeup
        esp_sleep_enable_timer_wakeup(seconds * 1000000ULL);
        
        // Enter light sleep (WiFi stays connected)
        esp_light_sleep_start();
        
        Serial.println("Woke from light sleep");
    }
    
    void checkIdleTimeout() {
        if (!deepSleepEnabled) return;
        
        unsigned long idleTime = (millis() - lastActivityTime) / 1000; // seconds
        
        if (idleTime > sleepTimeoutMinutes * 60) {
            Serial.printf("Idle timeout: %lu seconds\n", idleTime);
            enterDeepSleep("Idle timeout");
        }
    }
    
    void resetActivityTimer() {
        lastActivityTime = millis();
    }
    
    void setDeepSleepEnabled(bool enabled) {
        deepSleepEnabled = enabled;
        Serial.printf("Deep sleep: %s\n", enabled ? "Enabled" : "Disabled");
    }
    
    void setSleepTimeout(int minutes) {
        sleepTimeoutMinutes = minutes;
        Serial.printf("Sleep timeout: %d minutes\n", minutes);
    }
    
    int getBootCount() {
        return bootCount;
    }
    
    int getWakeupReason() {
        return wakeupReason;
    }
    
    float getBatteryVoltage() {
        // Read battery voltage from ADC
        // Adjust pin and calculation for your hardware
        const int batteryPin = 35; // Example pin
        int rawValue = analogRead(batteryPin);
        
        // Convert to voltage (adjust multiplier for your voltage divider)
        float voltage = (rawValue / 4095.0) * 3.3 * 2.0; // Example calculation
        
        return voltage;
    }
    
    int getBatteryPercent() {
        float voltage = getBatteryVoltage();
        
        // LiPo battery voltage range: 3.0V (empty) to 4.2V (full)
        const float minVoltage = 3.0;
        const float maxVoltage = 4.2;
        
        int percent = ((voltage - minVoltage) / (maxVoltage - minVoltage)) * 100;
        
        // Clamp to 0-100
        if (percent < 0) percent = 0;
        if (percent > 100) percent = 100;
        
        return percent;
    }
    
    bool isLowBattery() {
        return getBatteryPercent() < 20;
    }
    
    bool isCriticalBattery() {
        return getBatteryPercent() < 5;
    }
    
    void showBatteryWarning() {
        if (isCriticalBattery()) {
            display.clear();
            display.setCursor(0, 0);
            display.println("CRITICAL BATTERY!");
            display.printf("%d%% remaining\n", getBatteryPercent());
            display.println("Please charge now");
            display.display();
            
            // Force sleep to preserve battery
            delay(5000);
            enterDeepSleep("Critical battery");
        }
        else if (isLowBattery()) {
            display.clear();
            display.setCursor(0, 0);
            display.println("Low Battery");
            display.printf("%d%% remaining\n", getBatteryPercent());
            display.println("Please charge soon");
            display.display();
            delay(3000);
        }
    }

private:
    void saveState() {
        // Save important state to RTC memory or flash
        lastActiveTime = millis();
        // Add more state saving as needed
    }
    
    void configureGPIOForSleep() {
        // Isolate GPIO pins to minimize power consumption
        // Keep only wakeup button enabled
        
        // Example: Disable all GPIOs except wakeup button
        for (int i = 0; i < GPIO_NUM_MAX; i++) {
            if (i != wakeupButtonPin) {
                rtc_gpio_isolate((gpio_num_t)i);
            }
        }
    }
    
    void showWakeAnimation() {
        display.clear();
        display.setCursor(0, 0);
        display.println("⚡ VOLT");
        display.println("Waking up...");
        display.display();
        delay(1000);
    }
    
    void showWelcomeScreen() {
        display.clear();
        display.setCursor(0, 0);
        display.println("⚡ VOLT v5.00");
        display.println("AI Companion Watch");
        display.println("for Stone");
        display.println("");
        display.println("Made with 💙 by Dad");
        display.display();
        delay(3000);
    }
    
    void checkScheduledTasks() {
        // Check if there are any scheduled tasks to perform
        // Examples: sync time, check for updates, send heartbeat
        Serial.println("Checking scheduled tasks...");
        
        // If no tasks, go back to sleep
        // If tasks exist, perform them then sleep again
    }
};

#endif // POWER_MANAGEMENT_H
