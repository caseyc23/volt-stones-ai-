#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"
#include "power_management.h"
#include "watchdog.h"
#include "ota_update.h"
#include "VoltAI.h"

// Hardware Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_PIN 0
#define LED_PIN 2

// Modules
PowerManagement power;
Watchdog wdt;
OTAUpdate ota;
VoltAI volt;

void setup() {
    Serial.begin(115200);
    Serial.println("\n=== VOLT STARTUP ===");

    // 1. Initialize Display
    Wire.begin();
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("Connecting...");
    display.display();

    // 2. Initialize Hardware
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Off

    // 3. Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
        display.println("WiFi OK!");
    } else {
        Serial.println("\nWiFi Failed!");
        display.println("WiFi Fail!");
    }
    display.display();

    // 4. Initialize Modules
    power.begin(GPIO_NUM_0, SLEEP_TIMEOUT);
    wdt.begin(30); // 30s timeout
    ota.begin("VOLT-Pro", WEB_PASSWORD);
    
    if (volt.begin(OPENAI_API_KEY, VOLT_PERSONALITY)) {
        Serial.println("AI Initialized");
    }

    delay(1000);
    showIdleScreen();
}

void loop() {
    // 1. Core Services
    ota.handle();
    wdt.reset();
    power.checkIdleTimeout();

    // 2. Button Logic (Pull to talk)
    if (digitalRead(BUTTON_PIN) == LOW) {
        power.resetActivityTimer(); // Keep awake
        
        // Wait for debounce/hold
        delay(200);
        
        if (digitalRead(BUTTON_PIN) == LOW) {
            handleVoiceInteraction();
        }
    }

    delay(10);
}

void handleVoiceInteraction() {
    // 1. Record
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Listening...");
    display.display();
    digitalWrite(LED_PIN, HIGH);
    
    volt.recordAudio();
    
    digitalWrite(LED_PIN, LOW);
    display.println("Thinking...");
    display.display();

    // 2. Transcribe (Mock logic in skeleton, normally uploads audio)
    // String text = volt.transcribeAudio();
    
    // For skeleton testing without Microphone upload logic fully implemented:
    String text = "Testing VOLT"; 
    Serial.printf("Transcribed: %s\n", text.c_str());

    // 3. AI Chat
    if (text.length() > 0) {
        String reply = volt.chatWithGPT(text);
        
        if (reply.length() > 0) {
             display.clearDisplay();
             display.setCursor(0,0);
             display.println("Speaking...");
             display.display();
             
             // 4. TTS Playback
             volt.speakText(reply);
        }
    }

    showIdleScreen();
    // Allow watchdog reset after long operation
    wdt.reset();
}

void showIdleScreen() {
    display.clearDisplay();
    display.setCursor(0, 5);
    display.setTextSize(2);
    display.println("VOLT");
    display.setTextSize(1);
    display.setCursor(0, 30);
    display.println("Press to talk");
    
    // Battery
    display.setCursor(0, 50);
    display.printf("Bat: %d%%", power.getBatteryPercent());
    
    display.display();
}
