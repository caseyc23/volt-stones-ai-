/*
 * ============================================
 * VOLT AI Watch - Basic Example
 * ============================================
 * 
 * This is the simplest VOLT example.
 * Perfect for beginners and testing hardware.
 * 
 * Features:
 * - Button press detection
 * - Display messages
 * - LED control
 * - Serial output
 * 
 * No WiFi, no AI - just basic functionality
 * 
 * Hardware Required:
 * - ESP32-S3 board
 * - Display (SSD1306 or similar)
 * - Button
 * - LED
 * 
 * ============================================
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
#define BUTTON_PIN 0
#define LED_PIN 2

// Button state
int buttonPressCount = 0;
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 200;

void setup() {
  // Initialize serial
  Serial.begin(115200);
  Serial.println("\n\n=== VOLT Basic Example ===");
  
  // Initialize button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display initialization failed!");
    while(1);
  }
  
  // Show welcome screen
  showWelcome();
  
  Serial.println("Setup complete!");
  Serial.println("Press the button to interact with VOLT");
}

void loop() {
  // Check button
  if (digitalRead(BUTTON_PIN) == LOW) {
    unsigned long currentTime = millis();
    
    // Debounce
    if (currentTime - lastButtonPress > debounceDelay) {
      lastButtonPress = currentTime;
      handleButtonPress();
    }
  }
  
  delay(10);
}

void handleButtonPress() {
  buttonPressCount++;
  
  Serial.printf("Button pressed! Count: %d\n", buttonPressCount);
  
  // Blink LED
  digitalWrite(LED_PIN, HIGH);
  
  // Show message on display
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("VOLT");
  
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Button pressed!");
  
  display.setCursor(0, 35);
  display.printf("Count: %d\n", buttonPressCount);
  
  display.setCursor(0, 50);
  display.println("Made with love by Dad");
  
  display.display();
  
  // Turn off LED after 500ms
  delay(500);
  digitalWrite(LED_PIN, LOW);
}

void showWelcome() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("VOLT");
  
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Basic Example");
  
  display.setCursor(0, 35);
  display.println("Press button");
  display.setCursor(0, 45);
  display.println("to start!");
  
  display.display();
  delay(2000);
}
