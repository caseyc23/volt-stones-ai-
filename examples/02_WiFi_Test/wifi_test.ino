/*
 * ============================================
 * VOLT AI Watch - WiFi Test Example
 * ============================================
 * 
 * Test WiFi connectivity without AI features.
 * Perfect for debugging network issues.
 * 
 * Features:
 * - WiFi connection
 * - Network scanning
 * - Signal strength monitoring
 * - Connection status display
 * - Web server for testing
 * 
 * No AI or voice - just WiFi testing
 * 
 * ============================================
 */

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// WiFi credentials - CHANGE THESE!
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// Web server
WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n=== VOLT WiFi Test ===");
  
  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display failed!");
    while(1);
  }
  
  showMessage("VOLT WiFi Test", "Scanning networks...");
  
  // Scan for networks
  scanNetworks();
  
  // Connect to WiFi
  connectToWiFi();
  
  // Start web server
  setupWebServer();
  
  Serial.println("Setup complete!");
}

void loop() {
  server.handleClient();
  
  // Update display every 5 seconds
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 5000) {
    lastUpdate = millis();
    updateDisplay();
  }
  
  delay(10);
}

void scanNetworks() {
  Serial.println("Scanning WiFi networks...");
  
  int n = WiFi.scanNetworks();
  
  Serial.printf("Found %d networks:\n", n);
  
  for (int i = 0; i < n; i++) {
    Serial.printf("%d: %s (%d dBm) %s\n", 
      i + 1,
      WiFi.SSID(i).c_str(),
      WiFi.RSSI(i),
      WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "Open" : "Encrypted"
    );
  }
  
  delay(2000);
}

void connectToWiFi() {
  Serial.printf("Connecting to: %s\n", WIFI_SSID);
  
  showMessage("Connecting to:", WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("Signal strength: %d dBm\n", WiFi.RSSI());
    
    showMessage("WiFi Connected!", WiFi.localIP().toString().c_str());
    delay(3000);
  } else {
    Serial.println("\nWiFi connection failed!");
    showMessage("WiFi Failed!", "Check credentials");
    delay(5000);
  }
}

void setupWebServer() {
  // Root page
  server.on("/", []() {
    String html = "<html><body>";
    html += "<h1>VOLT WiFi Test</h1>";
    html += "<p>WiFi is working!</p>";
    html += "<p>IP: " + WiFi.localIP().toString() + "</p>";
    html += "<p>RSSI: " + String(WiFi.RSSI()) + " dBm</p>";
    html += "<p>SSID: " + String(WIFI_SSID) + "</p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });
  
  // Status endpoint
  server.on("/status", []() {
    String json = "{";
    json += "\"connected\": true,";
    json += "\"ssid\": \"" + String(WIFI_SSID) + "\",";
    json += "\"ip\": \"" + WiFi.localIP().toString() + "\",";
    json += "\"rssi\": " + String(WiFi.RSSI());
    json += "}";
    server.send(200, "application/json", json);
  });
  
  server.begin();
  Serial.println("Web server started");
  Serial.printf("Visit: http://%s\n", WiFi.localIP().toString().c_str());
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  if (WiFi.status() == WL_CONNECTED) {
    display.println("WiFi: Connected");
    display.printf("SSID: %s\n", WIFI_SSID);
    display.printf("IP: %s\n", WiFi.localIP().toString().c_str());
    display.printf("RSSI: %d dBm\n", WiFi.RSSI());
    
    // Signal strength bar
    int bars = map(WiFi.RSSI(), -90, -30, 0, 5);
    display.setCursor(0, 50);
    display.print("Signal: ");
    for (int i = 0; i < bars; i++) {
      display.print("|");
    }
  } else {
    display.println("WiFi: Disconnected");
    display.println("");
    display.println("Reconnecting...");
    
    // Try to reconnect
    WiFi.reconnect();
  }
  
  display.display();
}

void showMessage(const char* line1, const char* line2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println(line1);
  display.setCursor(0, 35);
  display.println(line2);
  display.display();
}
