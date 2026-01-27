/*
 * ============================================
 * VOLT AI WATCH - FIRMWARE V6.00 (PHASE 1)
 * ============================================
 * 
 * Target: ESP32-S3
 * New Features (Phase 1):
 * - GPS Tracking (NEO-6M)
 * - Emergency SOS Button
 * - Improved Audio (MAX98357A + INMP441)
 * - Activity Tracking (MPU6050)
 * - Battery Optimization (3+ days)
 * - Parental Dashboard API
 * 
 * ============================================
 */

#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#include <MPU6050.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Include Core Modules
#include "config.h"
#include "pins.h"
#include "memory.h"
#include "content.h"
#include "power_management.h"
#include "watchdog.h"
#include "ota_update.h"
#include "wifi_manager.h"
#include "web_api.h"
#include "VoltAI.h"

// NEW: Phase 1 Modules
#include "gps_tracker.h"
#include "activity_tracker.h"
#include "sos_system.h"

// Hardware Pin Definitions
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define BATTERY_PIN 34
#define BUZZER_PIN 25

// Global Objects
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
PowerManagement power;
Watchdog wdt;
OTAUpdate ota;
VoltAI bot;
VoltWiFiManager wifiManager;
VoltWebServer webApi;

// NEW: Phase 1 Objects
GPSTracker gpsTracker;
ActivityTracker activityTracker;
SOSSystem sosSystem;

// State Management
unsigned long lastButtonPress = 0;
int presses = 0;
const int DEBOUNCE_TIME = 250;
const int MULTI_PRESS_TIMEOUT = 600;

// NEW: Power optimization
unsigned long lastActivity = 0;
unsigned long lastGPSUpdate = 0;
unsigned long lastActivityUpdate = 0;
unsigned long lastAPISync = 0;

#define LIGHT_SLEEP_TIMEOUT 60000      // 1 minute
#define GPS_UPDATE_INTERVAL 30000      // 30 seconds
#define ACTIVITY_UPDATE_INTERVAL 5000  // 5 seconds
#define API_SYNC_INTERVAL 60000        // 1 minute

// Function Prototypes
void handleButtonAction(int count);
void showIdleScreen();
void optimizePower();
void syncWithAPI();
void checkSOSButton();

void setup() {
    Serial.begin(115200);
    Serial.println("\n\n=== VOLT V6.00 STARTUP (PHASE 1) ===");

    // 1. Hardware Init
    pinMode(0, INPUT_PULLUP);
    pinMode(2, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(2, LOW);

    // 2. Display Init
    Wire.begin();
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("Display allocation failed"));
        for(;;);
    }
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("VOLT v6.00");
    display.println("Phase 1 Features");
    display.println("Initializing...");
    display.display();
    delay(1000);

    // 3. System Modules Init
    wdt.begin(30);
    power.begin(GPIO_NUM_0, SLEEP_TIMEOUT);
    ota.begin("VOLT-Watch", AP_PASSWORD);

    // 4. NEW: GPS Init
    display.println("GPS...");
    display.display();
    if (gpsTracker.begin(GPS_RX_PIN, GPS_TX_PIN)) {
        Serial.println("GPS: Online");
        display.println("GPS: OK");
    } else {
        Serial.println("GPS: Failed");
        display.println("GPS: FAIL");
    }
    display.display();
    delay(500);

    // 5. NEW: Activity Tracking Init
    display.println("Activity...");
    display.display();
    if (activityTracker.begin()) {
        Serial.println("Activity: Online");
        display.println("Activity: OK");
    } else {
        Serial.println("Activity: Failed");
        display.println("Activity: FAIL");
    }
    display.display();
    delay(500);

    // 6. NEW: SOS System Init
    sosSystem.begin(BUZZER_PIN, &display);
    Serial.println("SOS: Online");

    // 7. WiFi & Web Server Init
    display.println("WiFi...");
    display.display();
    wifiManager.begin();
    if (wifiManager.isConnected()) {
        webApi.begin();
        Serial.println("Web API: Online");
        display.println("WiFi: OK");
    } else {
        display.println("WiFi: FAIL");
    }
    display.display();
    delay(500);

    // 8. AI Init
    display.println("AI...");
    display.display();
    if (bot.begin(OPENAI_API_KEY, VOLT_PERSONALITY)) {
        Serial.println("AI System: Online");
        display.println("AI: OK");
    } else {
        Serial.println("AI System: Failed");
        display.println("AI: FAIL");
    }
    display.display();
    delay(1000);

    // 9. Welcome
    display.clearDisplay();
    display.setCursor(0,0);
    String greeting = String(MORNING_GREETING);
    greeting.replace("CHILD_NAME_PLACEHOLDER", CHILD_NAME);
    display.println(greeting);
    display.display();
    
    if (WiFi.status() == WL_CONNECTED) {
        bot.speakText("System ready with GPS tracking!");
    }
    
    delay(2000);
    showIdleScreen();
    
    lastActivity = millis();
}

void loop() {
    // Background Tasks
    wdt.reset();
    ota.handle();
    webApi.handle();
    
    // NEW: Check SOS button (long press detection)
    checkSOSButton();
    
    // NEW: Update GPS periodically
    if (millis() - lastGPSUpdate > GPS_UPDATE_INTERVAL) {
        gpsTracker.update();
        lastGPSUpdate = millis();
    }
    
    // NEW: Update activity tracking
    if (millis() - lastActivityUpdate > ACTIVITY_UPDATE_INTERVAL) {
        activityTracker.update();
        lastActivityUpdate = millis();
    }
    
    // NEW: Sync with API
    if (millis() - lastAPISync > API_SYNC_INTERVAL) {
        syncWithAPI();
        lastAPISync = millis();
    }
    
    // NEW: Power optimization
    optimizePower();

    // Button Handling (Multi-press logic)
    if (digitalRead(0) == LOW) {
        power.resetActivityTimer();
        lastActivity = millis();
        
        unsigned long now = millis();
        if (now - lastButtonPress > DEBOUNCE_TIME) {
            presses++;
            lastButtonPress = now;
            delay(10);
        }
    }

    // Execute logic after pause
    if (presses > 0 && (millis() - lastButtonPress > MULTI_PRESS_TIMEOUT)) {
        handleButtonAction(presses);
        presses = 0;
    }
    
    delay(10);
}

void checkSOSButton() {
    static unsigned long buttonPressStart = 0;
    static bool buttonWasPressed = false;
    static bool sosTriggered = false;
    
    bool buttonPressed = (digitalRead(0) == LOW);
    
    if (buttonPressed && !buttonWasPressed) {
        buttonPressStart = millis();
        buttonWasPressed = true;
        sosTriggered = false;
    }
    
    if (buttonPressed && buttonWasPressed && !sosTriggered) {
        unsigned long pressDuration = millis() - buttonPressStart;
        
        // Visual feedback during long press
        if (pressDuration > 3000 && pressDuration < 5000) {
            display.clearDisplay();
            display.setTextSize(2);
            display.setCursor(0, 20);
            display.println("Hold for");
            display.println("SOS...");
            display.display();
        }
        
        if (pressDuration >= 5000) {
            // Trigger SOS
            sosSystem.trigger(
                gpsTracker.getLatitude(),
                gpsTracker.getLongitude(),
                gpsTracker.isValid(),
                power.getBatteryPercent()
            );
            sosTriggered = true;
            lastActivity = millis();
        }
    }
    
    if (!buttonPressed && buttonWasPressed) {
        buttonWasPressed = false;
        if (!sosTriggered && (millis() - buttonPressStart < 5000)) {
            // Normal button press, show idle screen
            showIdleScreen();
        }
    }
}

void handleButtonAction(int count) {
    Serial.printf("Button Pressed: %d times\n", count);
    lastActivity = millis();
    
    switch(count) {
        case 1: // Talk to VOLT
            if (ENABLE_VOICE_CHAT) {
                display.clearDisplay();
                display.setCursor(0,0);
                display.print("Listening...");
                display.display();
                digitalWrite(LED_PIN, HIGH);
                
                bot.recordAudio();
                
                digitalWrite(LED_PIN, LOW);
                display.clearDisplay();
                display.setCursor(0,0);
                display.print("Thinking...");
                display.display();
                
                String text = bot.transcribeAudio();
                String reply = bot.chatWithGPT(text);
                
                display.clearDisplay();
                display.setCursor(0,0);
                display.print("Speaking...");
                display.display();
                bot.speakText(reply);
            }
            break;
            
        case 2: // Show Stats
            display.clearDisplay();
            display.setTextSize(1);
            display.setCursor(0,0);
            display.println("=== TODAY'S STATS ===");
            display.printf("Steps: %d\n", activityTracker.getSteps());
            display.printf("Calories: %d\n", activityTracker.getCalories());
            display.printf("Battery: %d%%\n", power.getBatteryPercent());
            display.println("");
            if (gpsTracker.isValid()) {
                display.printf("GPS: %d sats\n", gpsTracker.getSatellites());
                display.println("Location: OK");
            } else {
                display.println("GPS: Searching...");
            }
            display.display();
            delay(5000);
            break;
            
        case 3: // Breathing Exercise
            if (ENABLE_BREATHING) {
                display.clearDisplay();
                display.println("Breathe in...");
                display.display();
                bot.speakText("Breathe in... 1, 2, 3, 4.");
                delay(4000);
                display.clearDisplay();
                display.println("Hold...");
                display.display();
                bot.speakText("Hold it... 1, 2, 3, 4.");
                delay(4000);
                display.clearDisplay();
                display.println("Breathe out...");
                display.display();
                bot.speakText("Breathe out... 1, 2, 3, 4.");
            }
            break;
            
        case 4: // Love Message
            if (ENABLE_LOVE_MESSAGE) {
                String msg = String(LOVE_MESSAGE);
                msg.replace("CHILD_NAME_PLACEHOLDER", CHILD_NAME);
                display.clearDisplay();
                display.println("Message from Dad:");
                display.println(msg);
                display.display();
                bot.speakText(msg);
            }
            break;
            
        case 5: // WiFi Setup
            if (ENABLE_WIFI_SETUP) {
                display.clearDisplay();
                display.setCursor(0,0);
                display.println("WiFi Setup Mode");
                display.println("Starting AP...");
                display.display();
                
                if (wifiManager.startAP()) {
                    webApi.begin();
                    display.println("Connect to:");
                    display.println("VOLT-Setup");
                    display.println("192.168.4.1");
                    display.display();
                    
                    unsigned long apStart = millis();
                    while(millis() - apStart < 300000) {
                        webApi.handle();
                        wdt.reset();
                        delay(10);
                        if (digitalRead(0) == LOW) break;
                    }
                    ESP.restart();
                }
            }
            break;
    }
    
    showIdleScreen();
}

void showIdleScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 5);
    display.println("VOLT");
    
    display.setTextSize(1);
    display.setCursor(0, 25);
    
    if (WiFi.status() == WL_CONNECTED) {
        display.println("Ready to talk!");
    } else {
        display.println("Offline mode");
    }
    
    // NEW: Show activity stats
    display.setCursor(0, 40);
    display.printf("Steps: %d", activityTracker.getSteps());
    
    // NEW: Show GPS status
    display.setCursor(0, 50);
    if (gpsTracker.isValid()) {
        display.printf("GPS: %d sats", gpsTracker.getSatellites());
    } else {
        display.print("GPS: Searching");
    }
    
    // Battery
    display.setCursor(0, 58);
    display.printf("Bat: %d%%", power.getBatteryPercent());
    
    display.display();
}

void optimizePower() {
    unsigned long idleTime = millis() - lastActivity;
    
    // Reduce CPU frequency when idle
    if (idleTime > LIGHT_SLEEP_TIMEOUT) {
        setCpuFrequencyMhz(80);  // Low power mode
    } else {
        setCpuFrequencyMhz(240);  // Full speed
    }
    
    // WiFi power saving
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.setSleep(true);
        esp_wifi_set_ps(WIFI_PS_MAX_MODEM);
    }
    
    // Display dimming
    if (idleTime > 30000) {
        display.dim(true);
    } else {
        display.dim(false);
    }
    
    // Deep sleep check
    power.checkIdleTimeout();
}

void syncWithAPI() {
    if (WiFi.status() != WL_CONNECTED) {
        return;
    }
    
    HTTPClient http;
    http.begin("https://your-api.com/api/device/" + String(DEVICE_ID) + "/sync");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-API-Key", API_KEY);
    
    StaticJsonDocument<1024> doc;
    
    // Device info
    doc["device_id"] = DEVICE_ID;
    doc["child_name"] = CHILD_NAME;
    doc["timestamp"] = millis();
    
    // Location
    JsonObject location = doc.createNestedObject("location");
    location["latitude"] = gpsTracker.getLatitude();
    location["longitude"] = gpsTracker.getLongitude();
    location["altitude"] = gpsTracker.getAltitude();
    location["satellites"] = gpsTracker.getSatellites();
    location["valid"] = gpsTracker.isValid();
    
    // Activity
    JsonObject activity = doc.createNestedObject("activity");
    activity["steps"] = activityTracker.getSteps();
    activity["calories"] = activityTracker.getCalories();
    activity["is_moving"] = activityTracker.isMoving();
    
    // Status
    JsonObject status = doc.createNestedObject("status");
    status["battery"] = power.getBatteryPercent();
    status["wifi_rssi"] = WiFi.RSSI();
    status["uptime"] = millis() / 1000;
    
    String payload;
    serializeJson(doc, payload);
    
    int httpCode = http.POST(payload);
    
    if (httpCode == HTTP_CODE_OK) {
        Serial.println("API: Sync successful");
    } else {
        Serial.printf("API: Sync failed (HTTP %d)\n", httpCode);
    }
    
    http.end();
}
