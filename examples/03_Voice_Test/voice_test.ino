/*
 * ============================================
 * VOLT AI Watch - Voice Test Example
 * ============================================
 * 
 * Test voice recording and playback.
 * Perfect for testing microphone and speaker.
 * 
 * Features:
 * - Microphone recording
 * - Audio playback
 * - Volume control
 * - Audio quality testing
 * 
 * No WiFi or AI - just audio hardware testing
 * 
 * ============================================
 */

#include <driver/i2s.h>
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

// I2S configuration for microphone
#define I2S_WS 15
#define I2S_SD 13
#define I2S_SCK 2
#define I2S_PORT I2S_NUM_0

// Audio buffer
#define SAMPLE_RATE 16000
#define SAMPLE_BITS 16
#define RECORD_TIME 5  // seconds
#define BUFFER_SIZE (SAMPLE_RATE * RECORD_TIME)

int16_t audioBuffer[BUFFER_SIZE];
bool isRecording = false;
bool hasRecording = false;

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n=== VOLT Voice Test ===");
  
  // Initialize pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display failed!");
    while(1);
  }
  
  // Initialize I2S for microphone
  setupI2S();
  
  showWelcome();
  
  Serial.println("Setup complete!");
  Serial.println("Press button to record");
}

void loop() {
  // Check button
  static unsigned long lastPress = 0;
  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastPress > 500) {
    lastPress = millis();
    
    if (!isRecording && !hasRecording) {
      // Start recording
      startRecording();
    } else if (hasRecording) {
      // Play back recording
      playRecording();
    }
  }
  
  delay(10);
}

void setupI2S() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };
  
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };
  
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  
  Serial.println("I2S initialized");
}

void startRecording() {
  Serial.println("Recording started...");
  isRecording = true;
  hasRecording = false;
  
  // Turn on LED
  digitalWrite(LED_PIN, HIGH);
  
  // Show recording screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Recording");
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.println("Speak now...");
  display.display();
  
  // Record audio
  size_t bytesRead = 0;
  for (int i = 0; i < RECORD_TIME; i++) {
    // Show progress
    display.fillRect(0, 55, (i + 1) * 25, 8, SSD1306_WHITE);
    display.display();
    
    // Read 1 second of audio
    i2s_read(I2S_PORT, 
             &audioBuffer[i * SAMPLE_RATE], 
             SAMPLE_RATE * sizeof(int16_t), 
             &bytesRead, 
             portMAX_DELAY);
    
    Serial.printf("Recorded %d bytes (second %d)\n", bytesRead, i + 1);
  }
  
  // Turn off LED
  digitalWrite(LED_PIN, LOW);
  
  isRecording = false;
  hasRecording = true;
  
  Serial.println("Recording complete!");
  
  // Show completion
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println("Complete!");
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.println("Press to play back");
  display.display();
  
  // Analyze audio
  analyzeAudio();
}

void playRecording() {
  Serial.println("Playing back...");
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println("Playing");
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.println("Listen...");
  display.display();
  
  // Reconfigure I2S for playback
  i2s_driver_uninstall(I2S_PORT);
  
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };
  
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_SD,
    .data_in_num = I2S_PIN_NO_CHANGE
  };
  
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  
  // Play audio
  size_t bytesWritten = 0;
  i2s_write(I2S_PORT, audioBuffer, BUFFER_SIZE * sizeof(int16_t), &bytesWritten, portMAX_DELAY);
  
  Serial.println("Playback complete!");
  
  // Reconfigure back to recording
  setupI2S();
  
  hasRecording = false;
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Press to record again");
  display.display();
}

void analyzeAudio() {
  // Calculate audio statistics
  int32_t sum = 0;
  int16_t maxVal = -32768;
  int16_t minVal = 32767;
  
  for (int i = 0; i < BUFFER_SIZE; i++) {
    sum += abs(audioBuffer[i]);
    if (audioBuffer[i] > maxVal) maxVal = audioBuffer[i];
    if (audioBuffer[i] < minVal) minVal = audioBuffer[i];
  }
  
  int16_t average = sum / BUFFER_SIZE;
  int16_t range = maxVal - minVal;
  
  Serial.println("=== Audio Analysis ===");
  Serial.printf("Average amplitude: %d\n", average);
  Serial.printf("Max value: %d\n", maxVal);
  Serial.printf("Min value: %d\n", minVal);
  Serial.printf("Range: %d\n", range);
  
  // Check if audio was captured
  if (average < 10) {
    Serial.println("WARNING: Very low audio level!");
    Serial.println("Check microphone connection");
  } else if (average > 1000) {
    Serial.println("Good audio level detected");
  }
}

void showWelcome() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("VOLT");
  
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Voice Test");
  display.setCursor(0, 35);
  display.println("Press button");
  display.setCursor(0, 45);
  display.println("to record");
  
  display.display();
  delay(2000);
}
