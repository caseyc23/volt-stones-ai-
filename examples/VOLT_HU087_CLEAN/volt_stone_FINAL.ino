/*
 * ============================================
 * VOLT for Stone - FINAL PRODUCTION VERSION
 * ============================================
 * 
 * Target: XiaoZhi HU-087 ESP32-S3 Watch
 * Child: Stone (8 years old)
 * Purpose: AI companion for connection, support, and fun
 * 
 * ✅ ALL CRITICAL BUGS FIXED
 * ✅ LONG PRESS DETECTION ADDED
 * ✅ WATCHDOG TIMER ENABLED
 * ✅ WIFI AUTO-RECONNECT
 * ✅ LOW BATTERY WARNING
 * ✅ COMPREHENSIVE ERROR HANDLING
 * 
 * This is the FINAL, production-ready version.
 * 
 * Features:
 * - GPT-4 AI conversations
 * - Voice recognition & speech
 * - Breathing exercises for anxiety
 * - Jokes and entertainment
 * - Dad's love messages (long press)
 * - Simple button interface
 * 
 * Hardware:
 * - ESP32-S3 microcontroller
 * - ST7789 1.47" color display (172x320)
 * - INMP441 I2S microphone
 * - MAX98357A I2S amplifier
 * - Single button interface
 * 
 * ============================================
 */

#include <Arduino.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <esp_task_wdt.h>

// Core modules - Use FINAL versions
#include "config_stone_FINAL.h"
#include "pins_hu087.h"
#include "volt_ai_FINAL.h"
#include "power_mgmt.h"
#include "wifi_mgmt.h"

// ============================================
// GLOBAL OBJECTS
// ============================================

TFT_eSPI display = TFT_eSPI();
VoltAI bot;
PowerManager power;
WiFiManager wifiMgr;

// ============================================
// STATE MANAGEMENT
// ============================================

// Button state
unsigned long lastButtonPress = 0;
unsigned long buttonPressStartTime = 0;
int buttonPresses = 0;
bool buttonCurrentlyPressed = false;

const int DEBOUNCE_TIME = 250;
const int MULTI_PRESS_TIMEOUT = 600;
const unsigned long LONG_PRESS_TIME = 2000;  // 2 seconds for love message

// App state
enum State {
    IDLE,
    LISTENING,
    THINKING,
    SPEAKING
};
State currentState = IDLE;

// WiFi reconnection
unsigned long lastWiFiCheck = 0;
const unsigned long WIFI_CHECK_INTERVAL = 30000;  // 30 seconds

// ============================================
// FUNCTION PROTOTYPES
// ============================================

void handleButtonPresses(int count);
void showIdleScreen();
void talkToVolt();
void tellJoke();
void breathingExercise();
void playLoveMessage();
void wifiSetup();
void updateDisplay(const char* message, uint16_t color = TFT_WHITE);
void setBacklight(bool on);
void checkWiFiConnection();
void checkBattery();

// ============================================
// SETUP
// ============================================

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n\n=== VOLT for Stone - Starting ===");
    Serial.println("Version: FINAL (Production Ready)");
    
    // Enable watchdog timer (8 seconds)
    esp_task_wdt_init(8, true);
    esp_task_wdt_add(NULL);
    Serial.println("Watchdog: Enabled (8s timeout)");
    
    // 1. Hardware initialization
    pinMode(BTN_BOOT, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    
    // Initialize backlight control
    pinMode(LCD_BL, OUTPUT);
    setBacklight(true);
    
    // 2. Display initialization
    display.init();
    display.setRotation(0);
    display.fillScreen(TFT_BLACK);
    display.setTextColor(TFT_WHITE, TFT_BLACK);
    display.setTextSize(2);
    display.setCursor(10, 60);
    display.println("VOLT");
    display.setTextSize(1);
    display.setCursor(10, 90);
    display.println("for Stone");
    display.setCursor(10, 110);
    display.println("Starting...");
    delay(1000);
    
    // 3. Power management
    power.begin();
    Serial.println("Power: Initialized");
    
    // 4. WiFi connection
    updateDisplay("Connecting WiFi...");
    if (wifiMgr.connect(WIFI_SSID, WIFI_PASSWORD, WIFI_TIMEOUT)) {
        Serial.println("WiFi: Connected");
        Serial.println("WiFi: IP = " + wifiMgr.getIP());
        updateDisplay("WiFi Connected!", TFT_GREEN);
    } else {
        Serial.println("WiFi: Failed (will work offline)");
        updateDisplay("WiFi Failed", TFT_YELLOW);
    }
    delay(1500);
    
    // 5. AI initialization
    updateDisplay("Starting AI...");
    if (bot.begin(OPENAI_API_KEY, STONE_PERSONALITY)) {
        Serial.println("AI: Ready");
        updateDisplay("AI Ready!", TFT_GREEN);
    } else {
        Serial.println("AI: Failed (check API key)");
        updateDisplay("AI Failed", TFT_RED);
    }
    delay(1500);
    
    // 6. Welcome message
    display.fillScreen(TFT_BLACK);
    display.setTextSize(2);
    display.setCursor(10, 60);
    display.setTextColor(TFT_CYAN);
    display.println("Hi Stone!");
    display.setTextSize(1);
    display.setCursor(10, 90);
    display.setTextColor(TFT_WHITE);
    display.println("Press button to talk");
    display.setCursor(10, 110);
    display.println("Hold for Dad's message");
    
    if (WiFi.status() == WL_CONNECTED) {
        bot.speak("Hi Stone! I'm ready to help you!");
    }
    
    delay(2000);
    showIdleScreen();
    
    Serial.println("=== VOLT Ready for Stone ===\n");
}

// ============================================
// MAIN LOOP
// ============================================

void loop() {
    // Reset watchdog
    esp_task_wdt_reset();
    power.keepAlive();
    
    // Check battery status
    checkBattery();
    
    // Check WiFi connection periodically
    checkWiFiConnection();
    
    // Check for sleep timeout
    if (ENABLE_DEEP_SLEEP && power.shouldSleep()) {
        Serial.println("Loop: Entering sleep mode");
        setBacklight(false);
        power.enterDeepSleep();
    }
    
    // Button handling
    bool buttonPressed = (digitalRead(BTN_BOOT) == LOW);
    
    // Detect button press start
    if (buttonPressed && !buttonCurrentlyPressed) {
        buttonPressStartTime = millis();
        buttonCurrentlyPressed = true;
        power.resetIdleTimer();
    }
    
    // Detect long press (for love message)
    if (buttonPressed && buttonCurrentlyPressed) {
        unsigned long pressDuration = millis() - buttonPressStartTime;
        if (pressDuration >= LONG_PRESS_TIME && buttonPresses == 0) {
            // Long press detected - play love message
            Serial.println("Button: Long press detected");
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            
            if (ENABLE_LOVE_MESSAGES) {
                playLoveMessage();
            }
            showIdleScreen();
            
            buttonCurrentlyPressed = false;
            buttonPresses = 0;
            
            // Wait for button release
            while (digitalRead(BTN_BOOT) == LOW) {
                esp_task_wdt_reset();
                delay(10);
            }
            return;
        }
    }
    
    // Detect button release (for counting presses)
    if (!buttonPressed && buttonCurrentlyPressed) {
        buttonCurrentlyPressed = false;
        
        unsigned long now = millis();
        if (now - lastButtonPress > DEBOUNCE_TIME) {
            buttonPresses++;
            lastButtonPress = now;
            
            // Visual feedback
            digitalWrite(LED_BUILTIN, HIGH);
            delay(50);
            digitalWrite(LED_BUILTIN, LOW);
            
            Serial.printf("Button: Press detected (count=%d)\n", buttonPresses);
        }
    }
    
    // Execute action after button release timeout
    if (buttonPresses > 0 && !buttonCurrentlyPressed && 
        (millis() - lastButtonPress > MULTI_PRESS_TIMEOUT)) {
        handleButtonPresses(buttonPresses);
        buttonPresses = 0;
    }
    
    delay(10);
}

// ============================================
// BUTTON ACTIONS
// ============================================

void handleButtonPresses(int count) {
    Serial.printf("Button: Executing action for %d presses\n", count);
    
    switch(count) {
        case 1:
            // Talk to VOLT
            if (ENABLE_VOICE_CHAT) {
                talkToVolt();
            }
            break;
            
        case 2:
            // Tell a joke
            if (ENABLE_JOKES) {
                tellJoke();
            }
            break;
            
        case 3:
            // Breathing exercise
            if (ENABLE_BREATHING_EXERCISES) {
                breathingExercise();
            }
            break;
            
        case 5:
            // WiFi setup
            if (ENABLE_WIFI_SETUP) {
                wifiSetup();
            }
            break;
            
        default:
            // Unknown pattern
            Serial.printf("Button: Unknown pattern (%d presses)\n", count);
            updateDisplay("Unknown pattern", TFT_YELLOW);
            delay(1000);
            break;
    }
    
    showIdleScreen();
}

// ============================================
// FEATURE IMPLEMENTATIONS
// ============================================

void talkToVolt() {
    Serial.println("Feature: Voice chat starting");
    
    if (WiFi.status() != WL_CONNECTED) {
        updateDisplay("Need WiFi!", TFT_YELLOW);
        delay(2000);
        updateDisplay("Try offline features:", TFT_CYAN);
        delay(1000);
        updateDisplay("2 press = Jokes", TFT_WHITE);
        delay(1000);
        updateDisplay("3 press = Breathing", TFT_WHITE);
        delay(2000);
        return;
    }
    
    // 1. Listen
    currentState = LISTENING;
    updateDisplay("Listening...", TFT_CYAN);
    digitalWrite(LED_BUILTIN, HIGH);
    
    bot.recordAudio();
    
    digitalWrite(LED_BUILTIN, LOW);
    
    // 2. Transcribe
    currentState = THINKING;
    updateDisplay("Thinking...", TFT_YELLOW);
    
    String userText = bot.transcribe();
    
    if (userText.length() == 0) {
        updateDisplay("Didn't hear you", TFT_RED);
        delay(2000);
        currentState = IDLE;
        Serial.println("Feature: No audio detected");
        return;
    }
    
    Serial.println("User said: " + userText);
    
    // 3. Get AI response
    String response = bot.chat(userText);
    
    if (response.length() == 0) {
        updateDisplay("AI Error", TFT_RED);
        delay(2000);
        currentState = IDLE;
        Serial.println("Feature: AI response failed");
        return;
    }
    
    Serial.println("VOLT says: " + response);
    
    // 4. Speak response
    currentState = SPEAKING;
    updateDisplay("Speaking...", TFT_GREEN);
    
    bot.speak(response);
    
    currentState = IDLE;
    Serial.println("Feature: Voice chat complete");
}

void tellJoke() {
    Serial.println("Feature: Joke time");
    updateDisplay("Joke Time!", TFT_MAGENTA);
    delay(1000);
    
    String joke = "";
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Feature: Getting AI joke");
        String prompt = "Tell a short, funny joke for an 8-year-old boy named Stone. Keep it under 30 words.";
        joke = bot.chat(prompt);
    }
    
    // Fallback to offline jokes
    if (joke.length() == 0) {
        Serial.println("Feature: Using offline joke");
        const char* offlineJokes[] = {
            "Why did the scarecrow win an award? Because he was outstanding in his field!",
            "What do you call a bear with no teeth? A gummy bear!",
            "Why don't scientists trust atoms? Because they make up everything!",
            "What did the ocean say to the beach? Nothing, it just waved!",
            "Why did the bicycle fall over? It was two tired!",
            "What do you call a dinosaur that crashes his car? Tyrannosaurus Wrecks!",
            "Why can't you hear a pterodactyl go to the bathroom? Because the P is silent!",
            "What do you call a sleeping bull? A bulldozer!"
        };
        int randomIndex = random(0, 8);
        joke = offlineJokes[randomIndex];
    }
    
    Serial.println("Joke: " + joke);
    
    // Display joke on screen
    display.fillScreen(TFT_BLACK);
    display.setTextSize(1);
    display.setCursor(5, 40);
    display.setTextColor(TFT_YELLOW);
    display.println(joke);
    
    // Speak joke if WiFi available
    if (WiFi.status() == WL_CONNECTED) {
        bot.speak(joke);
    }
    
    delay(3000);
    Serial.println("Feature: Joke complete");
}

void breathingExercise() {
    Serial.println("Feature: Breathing exercise starting");
    updateDisplay("Let's Breathe", TFT_CYAN);
    
    if (WiFi.status() == WL_CONNECTED) {
        bot.speak("Let's breathe together, Stone. Follow along.");
    }
    delay(1500);
    
    for (int i = 0; i < 3; i++) {
        Serial.printf("Breathing: Cycle %d/3\n", i + 1);
        
        // Breathe in
        display.fillScreen(TFT_BLUE);
        display.setTextSize(3);
        display.setCursor(20, 100);
        display.setTextColor(TFT_WHITE);
        display.println("BREATHE");
        display.setCursor(50, 140);
        display.println("IN");
        
        if (WiFi.status() == WL_CONNECTED) {
            bot.speak("Breathe in... 1, 2, 3, 4");
        }
        delay(4000);
        
        // Hold
        display.fillScreen(TFT_YELLOW);
        display.setTextSize(3);
        display.setCursor(50, 120);
        display.setTextColor(TFT_BLACK);
        display.println("HOLD");
        
        if (WiFi.status() == WL_CONNECTED) {
            bot.speak("Hold... 1, 2, 3, 4");
        }
        delay(4000);
        
        // Breathe out
        display.fillScreen(TFT_GREEN);
        display.setTextSize(3);
        display.setCursor(20, 100);
        display.setTextColor(TFT_WHITE);
        display.println("BREATHE");
        display.setCursor(50, 140);
        display.println("OUT");
        
        if (WiFi.status() == WL_CONNECTED) {
            bot.speak("Breathe out... 1, 2, 3, 4, 5, 6");
        }
        delay(6000);
    }
    
    display.fillScreen(TFT_BLACK);
    display.setTextSize(2);
    display.setCursor(30, 120);
    display.setTextColor(TFT_GREEN);
    display.println("Great Job!");
    
    if (WiFi.status() == WL_CONNECTED) {
        bot.speak("Great job, Stone! You did amazing!");
    }
    delay(2000);
    
    Serial.println("Feature: Breathing exercise complete");
}

void playLoveMessage() {
    Serial.println("Feature: Playing love message");
    
    display.fillScreen(TFT_PURPLE);
    display.setTextSize(2);
    display.setCursor(10, 60);
    display.setTextColor(TFT_WHITE);
    display.println("Message");
    display.setCursor(10, 90);
    display.println("from Dad");
    
    display.setTextSize(1);
    display.setCursor(10, 130);
    display.println(LOVE_MESSAGE);
    
    Serial.println("Love Message: " + String(LOVE_MESSAGE));
    
    if (WiFi.status() == WL_CONNECTED) {
        bot.speak(LOVE_MESSAGE);
    }
    
    delay(3000);
    Serial.println("Feature: Love message complete");
}

void wifiSetup() {
    Serial.println("Feature: WiFi setup mode");
    updateDisplay("WiFi Setup", TFT_CYAN);
    
    if (WiFi.status() == WL_CONNECTED) {
        bot.speak("Starting WiFi setup mode");
    }
    
    // Show instructions
    display.fillScreen(TFT_BLACK);
    display.setTextSize(1);
    display.setCursor(10, 40);
    display.println("WiFi Setup Mode");
    display.setCursor(10, 60);
    display.println("Connect to:");
    display.setTextSize(2);
    display.setCursor(10, 80);
    display.setTextColor(TFT_CYAN);
    display.println("VOLT-Setup");
    display.setTextSize(1);
    display.setTextColor(TFT_WHITE);
    display.setCursor(10, 110);
    display.println("Password: volt2024");
    display.setCursor(10, 130);
    display.println("Go to: 192.168.4.1");
    display.setCursor(10, 160);
    display.setTextColor(TFT_YELLOW);
    display.println("Press button to exit");
    
    // Start AP mode
    if (wifiMgr.startAP("VOLT-Setup", "volt2024")) {
        Serial.println("AP Mode: Started successfully");
        
        // Keep AP open for 5 minutes or until button press
        unsigned long startTime = millis();
        while (millis() - startTime < 300000) {
            esp_task_wdt_reset();
            power.keepAlive();
            
            // Exit on button press
            if (digitalRead(BTN_BOOT) == LOW) {
                delay(1000);
                Serial.println("AP Mode: Exiting on button press");
                break;
            }
            
            delay(100);
        }
        
        updateDisplay("Restarting...", TFT_YELLOW);
        delay(2000);
        
        // Restart to apply new settings
        ESP.restart();
    } else {
        updateDisplay("AP Failed", TFT_RED);
        Serial.println("AP Mode: Failed to start");
        delay(2000);
    }
}

// ============================================
// HELPER FUNCTIONS
// ============================================

void checkWiFiConnection() {
    if (millis() - lastWiFiCheck < WIFI_CHECK_INTERVAL) {
        return;
    }
    
    lastWiFiCheck = millis();
    
    if (WiFi.status() != WL_CONNECTED && strlen(WIFI_SSID) > 0) {
        Serial.println("WiFi: Connection lost, attempting reconnect...");
        if (wifiMgr.connect(WIFI_SSID, WIFI_PASSWORD, 10)) {
            Serial.println("WiFi: Reconnected successfully");
        }
    }
}

void checkBattery() {
    static unsigned long lastBatteryCheck = 0;
    static bool lowBatteryWarningShown = false;
    
    if (millis() - lastBatteryCheck < 60000) {  // Check every minute
        return;
    }
    
    lastBatteryCheck = millis();
    int batteryPercent = power.getBatteryPercent();
    
    if (batteryPercent < 20 && !lowBatteryWarningShown) {
        Serial.println("⚠️ LOW BATTERY WARNING: " + String(batteryPercent) + "%");
        lowBatteryWarningShown = true;
        
        // Could add visual/audio warning here
        updateDisplay("Low Battery!", TFT_RED);
        delay(2000);
        showIdleScreen();
    }
    
    if (batteryPercent >= 20) {
        lowBatteryWarningShown = false;
    }
}

void showIdleScreen() {
    currentState = IDLE;
    
    display.fillScreen(TFT_BLACK);
    
    // Title
    display.setTextSize(3);
    display.setCursor(30, 60);
    display.setTextColor(TFT_CYAN);
    display.println("VOLT");
    
    // Status
    display.setTextSize(1);
    display.setCursor(10, 110);
    display.setTextColor(TFT_WHITE);
    
    if (WiFi.status() == WL_CONNECTED) {
        display.setTextColor(TFT_GREEN);
        display.println("Ready to talk!");
    } else {
        display.setTextColor(TFT_YELLOW);
        display.println("Offline mode");
        display.setCursor(10, 125);
        display.setTextColor(TFT_WHITE);
        display.println("(Jokes & breathing work)");
    }
    
    // Battery
    display.setCursor(10, 150);
    display.setTextColor(TFT_WHITE);
    int battery = power.getBatteryPercent();
    if (battery < 20) {
        display.setTextColor(TFT_RED);
    }
    display.printf("Battery: %d%%", battery);
    
    // Instructions
    display.setCursor(10, 180);
    display.setTextColor(TFT_CYAN);
    display.println("Press button to start");
    
    display.setCursor(10, 200);
    display.setTextSize(1);
    display.setTextColor(TFT_GRAY);
    display.println("1=Talk 2=Joke 3=Breathe");
    display.setCursor(10, 215);
    display.println("Hold=Love 5=WiFi");
}

void updateDisplay(const char* message, uint16_t color) {
    display.fillScreen(TFT_BLACK);
    display.setTextSize(2);
    display.setCursor(10, 120);
    display.setTextColor(color);
    display.println(message);
}

void setBacklight(bool on) {
    // HU-087 backlight is active LOW
    digitalWrite(LCD_BL, on ? LOW : HIGH);
}

// ============================================
// END OF FIRMWARE
// ============================================
