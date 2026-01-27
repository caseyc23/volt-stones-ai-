/*
 * ============================================
 * VOLT for Stone - HU-087 Clean Version
 * ============================================
 * 
 * Target: XiaoZhi HU-087 ESP32-S3 Watch
 * Child: Stone (8 years old)
 * Purpose: AI companion for connection, support, and fun
 * 
 * Features:
 * - GPT-4 AI conversations
 * - Voice recognition & speech
 * - Breathing exercises for anxiety
 * - Jokes and entertainment
 * - Dad's love messages
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
#include <TFT_eSPI.h>  // For ST7789 display

// Core modules
#include "config_stone.h"
#include "pins_hu087.h"
#include "volt_ai.h"
#include "power_mgmt.h"
#include "wifi_mgmt.h"

// ============================================
// GLOBAL OBJECTS
// ============================================

TFT_eSPI display = TFT_eSPI();  // ST7789 display
VoltAI bot;                      // AI engine
PowerManager power;              // Power management
WiFiManager wifiMgr;             // WiFi management

// ============================================
// STATE MANAGEMENT
// ============================================

// Button state
unsigned long lastButtonPress = 0;
int buttonPresses = 0;
const int DEBOUNCE_TIME = 250;
const int MULTI_PRESS_TIMEOUT = 600;

// App state
enum State {
    IDLE,
    LISTENING,
    THINKING,
    SPEAKING
};
State currentState = IDLE;

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

// ============================================
// SETUP
// ============================================

void setup() {
    Serial.begin(115200);
    Serial.println("\n\n=== VOLT for Stone - Starting ===");
    
    // 1. Hardware initialization
    pinMode(BTN_BOOT, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    
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
        updateDisplay("WiFi Connected!", TFT_GREEN);
    } else {
        Serial.println("WiFi: Failed (will work offline)");
        updateDisplay("WiFi Failed", TFT_YELLOW);
    }
    delay(1000);
    
    // 5. AI initialization
    updateDisplay("Starting AI...");
    if (bot.begin(OPENAI_API_KEY, STONE_PERSONALITY)) {
        Serial.println("AI: Ready");
        updateDisplay("AI Ready!", TFT_GREEN);
    } else {
        Serial.println("AI: Failed");
        updateDisplay("AI Failed", TFT_RED);
    }
    delay(1000);
    
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
    power.keepAlive();
    
    // Check for sleep timeout
    if (power.shouldSleep()) {
        power.enterDeepSleep();
    }
    
    // Button handling
    if (digitalRead(BTN_BOOT) == LOW) {
        power.resetIdleTimer();
        
        unsigned long now = millis();
        if (now - lastButtonPress > DEBOUNCE_TIME) {
            buttonPresses++;
            lastButtonPress = now;
            
            // Visual feedback
            digitalWrite(LED_BUILTIN, HIGH);
            delay(50);
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
    
    // Execute action after button release
    if (buttonPresses > 0 && (millis() - lastButtonPress > MULTI_PRESS_TIMEOUT)) {
        handleButtonPresses(buttonPresses);
        buttonPresses = 0;
    }
    
    delay(10);
}

// ============================================
// BUTTON ACTIONS
// ============================================

void handleButtonPresses(int count) {
    Serial.printf("Button: %d presses\n", count);
    
    switch(count) {
        case 1:
            // Talk to VOLT
            talkToVolt();
            break;
            
        case 2:
            // Tell a joke
            tellJoke();
            break;
            
        case 3:
            // Breathing exercise
            breathingExercise();
            break;
            
        case 4:
            // Dad's love message
            playLoveMessage();
            break;
            
        case 5:
            // WiFi setup
            wifiSetup();
            break;
            
        default:
            // Unknown pattern
            Serial.println("Unknown button pattern");
            break;
    }
    
    showIdleScreen();
}

// ============================================
// FEATURE IMPLEMENTATIONS
// ============================================

void talkToVolt() {
    if (WiFi.status() != WL_CONNECTED) {
        updateDisplay("Need WiFi!", TFT_YELLOW);
        bot.speak("I need WiFi to talk. Try the breathing exercise or jokes!");
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
        bot.speak("Sorry Stone, I didn't hear you. Try again?");
        delay(2000);
        currentState = IDLE;
        return;
    }
    
    Serial.println("User: " + userText);
    
    // 3. Get AI response
    String response = bot.chat(userText);
    
    if (response.length() == 0) {
        updateDisplay("AI Error", TFT_RED);
        bot.speak("Sorry Stone, I'm having trouble thinking right now.");
        delay(2000);
        currentState = IDLE;
        return;
    }
    
    Serial.println("VOLT: " + response);
    
    // 4. Speak response
    currentState = SPEAKING;
    updateDisplay("Speaking...", TFT_GREEN);
    
    bot.speak(response);
    
    currentState = IDLE;
}

void tellJoke() {
    updateDisplay("Joke Time!", TFT_MAGENTA);
    
    String joke;
    
    if (WiFi.status() == WL_CONNECTED) {
        // Get AI joke
        String prompt = "Tell a short, funny joke for an 8-year-old boy named Stone. Keep it under 30 words.";
        joke = bot.chat(prompt);
    }
    
    // Fallback to offline jokes
    if (joke.length() == 0) {
        const char* offlineJokes[] = {
            "Why did the scarecrow win an award? Because he was outstanding in his field!",
            "What do you call a bear with no teeth? A gummy bear!",
            "Why don't scientists trust atoms? Because they make up everything!",
            "What did the ocean say to the beach? Nothing, it just waved!",
            "Why did the bicycle fall over? It was two tired!"
        };
        int randomIndex = random(0, 5);
        joke = offlineJokes[randomIndex];
    }
    
    Serial.println("Joke: " + joke);
    bot.speak(joke);
    
    delay(1000);
}

void breathingExercise() {
    updateDisplay("Let's Breathe", TFT_CYAN);
    bot.speak("Let's breathe together, Stone. Follow along.");
    delay(1500);
    
    for (int i = 0; i < 3; i++) {
        // Breathe in
        display.fillScreen(TFT_BLUE);
        display.setTextSize(3);
        display.setCursor(20, 100);
        display.setTextColor(TFT_WHITE);
        display.println("BREATHE");
        display.setCursor(50, 140);
        display.println("IN");
        bot.speak("Breathe in... 1, 2, 3, 4");
        delay(4000);
        
        // Hold
        display.fillScreen(TFT_YELLOW);
        display.setTextSize(3);
        display.setCursor(50, 120);
        display.setTextColor(TFT_BLACK);
        display.println("HOLD");
        bot.speak("Hold... 1, 2, 3, 4");
        delay(4000);
        
        // Breathe out
        display.fillScreen(TFT_GREEN);
        display.setTextSize(3);
        display.setCursor(20, 100);
        display.setTextColor(TFT_WHITE);
        display.println("BREATHE");
        display.setCursor(50, 140);
        display.println("OUT");
        bot.speak("Breathe out... 1, 2, 3, 4, 5, 6");
        delay(6000);
    }
    
    display.fillScreen(TFT_BLACK);
    display.setTextSize(2);
    display.setCursor(30, 120);
    display.setTextColor(TFT_GREEN);
    display.println("Great Job!");
    bot.speak("Great job, Stone! You did amazing!");
    delay(2000);
}

void playLoveMessage() {
    display.fillScreen(TFT_PURPLE);
    display.setTextSize(2);
    display.setCursor(10, 60);
    display.setTextColor(TFT_WHITE);
    display.println("Message");
    display.setCursor(10, 90);
    display.println("from Dad");
    
    String message = String(LOVE_MESSAGE);
    message.replace("CHILD_NAME", CHILD_NAME);
    
    Serial.println("Love Message: " + message);
    bot.speak(message);
    
    delay(2000);
}

void wifiSetup() {
    updateDisplay("WiFi Setup", TFT_CYAN);
    bot.speak("Starting WiFi setup mode");
    
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
    
    // Start AP mode
    if (wifiMgr.startAP("VOLT-Setup", "volt2024")) {
        Serial.println("AP Mode: Started");
        
        // Keep AP open for 5 minutes
        unsigned long startTime = millis();
        while (millis() - startTime < 300000) {
            power.keepAlive();
            
            // Exit on button press
            if (digitalRead(BTN_BOOT) == LOW) {
                delay(1000);
                break;
            }
            
            delay(100);
        }
        
        // Restart to apply new settings
        ESP.restart();
    } else {
        updateDisplay("AP Failed", TFT_RED);
        delay(2000);
    }
}

// ============================================
// DISPLAY HELPERS
// ============================================

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
    display.printf("Battery: %d%%", battery);
    
    // Instructions
    display.setCursor(10, 180);
    display.setTextColor(TFT_CYAN);
    display.println("Press button to start");
}

void updateDisplay(const char* message, uint16_t color) {
    display.fillScreen(TFT_BLACK);
    display.setTextSize(2);
    display.setCursor(10, 120);
    display.setTextColor(color);
    display.println(message);
}

// ============================================
// END OF FIRMWARE
// ============================================
