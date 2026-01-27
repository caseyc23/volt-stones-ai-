# VOLT AI Watch - Phase 1 Execution Plan

## Immediate Action Items to Complete Phase 1 (Next 30 Days)

---

## 🎯 Phase 1 Quick Summary

**Goal**: Add critical safety features to compete with mainstream kids' wearables
**Timeline**: 12 weeks (3 months)
**Budget**: $130 for hardware (5 prototype units)
**Expected Impact**: Safety Score 7/10 → 9/10, Overall Score 38/50 → 41/50

---

## ✅ WEEK 1-2: ORDER & SETUP (START NOW!)

### Day 1: Order Hardware Components

#### Shopping List (Priority Order):

**1. GPS Module - NEO-6M ($40 for 5 units)**

```
Amazon Search: "NEO-6M GPS Module ESP32"
Recommended: HiLetgo NEO-6M GPS Module
Price: ~$8 each
Quantity: 5
Link: amazon.com/s?k=neo-6m+gps+module
Shipping: 2-3 days (Prime)
```

**2. Audio Upgrade ($35 for 5 units)**

```
MAX98357A I2S Amplifier:
- Search: "MAX98357A I2S Class D Amplifier"
- Adafruit part #3006 or compatible
- Price: ~$4 each
- Quantity: 5

INMP441 I2S Microphone:
- Search: "INMP441 I2S MEMS Microphone"
- Price: ~$3 each
- Quantity: 5
```

**3. Accelerometer - MPU6050 ($10 for 5 units)**

```
Amazon Search: "MPU6050 GY-521 Module"
Price: ~$2 each
Quantity: 5
Shipping: 2-3 days
```

**4. Larger Battery ($40 for 5 units)**

```
Amazon Search: "1200mAh 3.7V LiPo Battery JST"
Recommended: 603450 size
Price: ~$8 each
Quantity: 5
IMPORTANT: Check connector type (JST-PH 2.0)
```

**5. Buzzer for SOS ($5 for 5 units)**

```
Amazon Search: "5V Active Buzzer Arduino"
Price: ~$1 each
Quantity: 5
```

**6. Jumper Wires & Breadboard ($10)**

```
If you don't have:
- Dupont jumper wires (M-M, M-F, F-F)
- Small breadboard
- Total: ~$10
```

**TOTAL COST: ~$140**

#### Order Now:

```bash
# Create shopping cart with these items:
1. NEO-6M GPS (5x) - $40
2. MAX98357A Amp (5x) - $20
3. INMP441 Mic (5x) - $15
4. MPU6050 (5x) - $10
5. 1200mAh Battery (5x) - $40
6. Buzzer (5x) - $5
7. Jumper wires - $10

Total: ~$140
Expected Delivery: 2-5 days
```

### Day 2-3: Software Setup

#### Install Required Libraries

**Arduino IDE Setup:**

```cpp
// Open Arduino IDE
// Go to: Tools → Manage Libraries

// Install these libraries:
1. TinyGPS++ (by Mikal Hart)
   - Search: "TinyGPS++"
   - Click Install

2. MPU6050 (by Electronic Cats)
   - Search: "MPU6050"
   - Install "MPU6050 by Electronic Cats"

3. Adafruit GFX Library
   - Search: "Adafruit GFX"
   - Click Install

4. Adafruit SSD1306
   - Search: "Adafruit SSD1306"
   - Click Install

5. ArduinoJson (v6.x)
   - Search: "ArduinoJson"
   - Install version 6.x (NOT 7.x)

6. HTTPClient (built-in with ESP32)
   - No installation needed
```

**PlatformIO Setup (Alternative):**

```ini
# platformio.ini
[env:esp32s3]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino

lib_deps =
    mikalhart/TinyGPSPlus@^1.0.3
    electroniccats/MPU6050@^1.0.0
    adafruit/Adafruit GFX Library@^1.11.9
    adafruit/Adafruit SSD1306@^2.5.9
    bblanchon/ArduinoJson@^6.21.4
```

#### Download Phase 1 Firmware

```bash
# Files already created in phase1_firmware/:
- volt_firmware_v6.ino (main firmware)
- gps_tracker.h (GPS module)
- activity_tracker.h (step counting)
- sos_system.h (emergency alerts)
- README.md (setup guide)

# Copy these to your Arduino sketch folder
```

### Day 4-5: Test Current Setup

**Before adding new hardware, verify existing system:**

```cpp
// Test 1: Basic Boot
// Upload current firmware and verify:
☐ Display shows boot screen
☐ WiFi connects
☐ AI voice works
☐ Button responds
☐ No errors in serial monitor

// Test 2: Power Consumption
// Measure current draw:
☐ Idle: Should be ~50mA
☐ Active: Should be ~200-300mA
☐ Deep sleep: Should be ~10-15mA

// Test 3: Battery Life Baseline
// Full charge test:
☐ Charge battery to 100%
☐ Run normal operations
☐ Record time to depletion
☐ Current baseline: 1-2 days
```

---

## ✅ WEEK 3-4: GPS INTEGRATION

### Hardware Wiring

**NEO-6M GPS → ESP32-S3:**

```
GPS Module    ESP32-S3 Pin
VCC       →   3.3V
GND       →   GND
TX        →   GPIO 16 (RX2)
RX        →   GPIO 17 (TX2)

Notes:
- Use 3.3V, NOT 5V (will damage GPS)
- TX on GPS goes to RX on ESP32
- RX on GPS goes to TX on ESP32
- Keep wires short (<10cm)
```

**Wiring Diagram:**

```
         ESP32-S3
         ┌─────────┐
    3.3V │●        │
     GND │●        │
GPIO 16  │●        │ ← GPS TX
GPIO 17  │●        │ → GPS RX
         └─────────┘
              ↕
         NEO-6M GPS
         ┌─────────┐
     VCC │●        │
     GND │●        │
      TX │●        │
      RX │●        │
         └─────────┘
```

### Software Integration

**Step 1: Add GPS Library**

```cpp
// At top of volt_firmware_v6.ino
#include "gps_tracker.h"

// Create GPS object
GPSTracker gpsTracker;
```

**Step 2: Initialize in setup()**

```cpp
void setup() {
    // ... existing code ...

    // Add GPS initialization
    Serial.println("Initializing GPS...");
    if (gpsTracker.begin(16, 17)) {  // RX, TX pins
        Serial.println("GPS: Online");
    } else {
        Serial.println("GPS: Failed to initialize");
    }

    // ... rest of setup ...
}
```

**Step 3: Update in loop()**

```cpp
void loop() {
    // ... existing code ...

    // Update GPS every 30 seconds
    static unsigned long lastGPSUpdate = 0;
    if (millis() - lastGPSUpdate > 30000) {
        gpsTracker.update();
        lastGPSUpdate = millis();

        // Log location if valid
        if (gpsTracker.isValid()) {
            Serial.printf("Location: %.6f, %.6f (%d sats)\n",
                gpsTracker.getLatitude(),
                gpsTracker.getLongitude(),
                gpsTracker.getSatellites());
        }
    }

    // ... rest of loop ...
}
```

### Testing GPS

**Test Protocol:**

```
1. Upload firmware with GPS code
2. Open Serial Monitor (115200 baud)
3. Take device outside (clear view of sky)
4. Wait 2-5 minutes for GPS lock
5. Verify output:
   ☐ "GPS: Online" message
   ☐ Satellite count increasing (need 4+)
   ☐ Location coordinates displayed
   ☐ Coordinates are accurate (check on Google Maps)

Expected Output:
GPS: Initializing...
GPS: Online
GPS: Searching for satellites...
GPS: 3 satellites
GPS: 5 satellites
GPS: 8 satellites
Location: 37.774929, -122.419418 (8 sats)
```

**Troubleshooting:**

```
Problem: No satellites
Solution:
- Go outside (GPS doesn't work indoors)
- Wait 5-10 minutes (cold start)
- Check antenna connection
- Verify 3.3V power

Problem: Wrong coordinates
Solution:
- Wait for more satellites (need 4+)
- Check TX/RX wiring (might be swapped)
- Verify baud rate (9600)

Problem: GPS not responding
Solution:
- Check wiring (especially power)
- Swap TX/RX pins
- Try different baud rate
- Test with GPS test sketch
```

---

## ✅ WEEK 5-6: ACTIVITY TRACKING

### Hardware Wiring

**MPU6050 → ESP32-S3:**

```
MPU6050      ESP32-S3 Pin
VCC      →   3.3V
GND      →   GND
SCL      →   GPIO 22 (I2C Clock)
SDA      →   GPIO 21 (I2C Data)

Notes:
- I2C address is usually 0x68
- Can share I2C bus with display
- Keep wires short for reliability
```

### Software Integration

**Step 1: Add Activity Tracker**

```cpp
// At top of volt_firmware_v6.ino
#include "activity_tracker.h"

// Create activity tracker object
ActivityTracker activityTracker;
```

**Step 2: Initialize in setup()**

```cpp
void setup() {
    // ... existing code ...

    // Add activity tracker initialization
    Serial.println("Initializing Activity Tracker...");
    if (activityTracker.begin(21, 22)) {  // SDA, SCL pins
        Serial.println("Activity: Online");
    } else {
        Serial.println("Activity: Failed to initialize");
    }

    // ... rest of setup ...
}
```

**Step 3: Update in loop()**

```cpp
void loop() {
    // ... existing code ...

    // Update activity every 5 seconds
    static unsigned long lastActivityUpdate = 0;
    if (millis() - lastActivityUpdate > 5000) {
        activityTracker.update();
        lastActivityUpdate = millis();
    }

    // ... rest of loop ...
}
```

**Step 4: Add Stats Display (Button 2)**

```cpp
void handleButtonAction(int count) {
    switch(count) {
        case 1:
            // Existing voice chat code
            break;

        case 2:  // NEW: Show stats
            display.clearDisplay();
            display.setTextSize(1);
            display.setCursor(0,0);
            display.println("=== TODAY'S STATS ===");
            display.printf("Steps: %d\n", activityTracker.getSteps());
            display.printf("Calories: %d\n", activityTracker.getCalories());
            display.printf("Distance: %.2f km\n", activityTracker.getDistanceKm());
            display.printf("Battery: %d%%\n", power.getBatteryPercent());
            display.display();
            delay(5000);
            break;

        // ... rest of cases ...
    }
}
```

### Testing Activity Tracking

**Test Protocol:**

```
1. Upload firmware with activity tracking
2. Open Serial Monitor
3. Keep device still for calibration (10 seconds)
4. Walk around (take 20-30 steps)
5. Verify output:
   ☐ "Activity: Online" message
   ☐ Calibration complete
   ☐ Steps counted (should be close to actual)
   ☐ Calories calculated
   ☐ Distance calculated

Expected Output:
Activity: Initializing...
Activity: Calibrating (keep still)...
Activity: Calibration complete (X=123, Y=456, Z=789)
Activity: Online
Activity: Step detected! Total=1, Cal=0
Activity: Step detected! Total=2, Cal=0
Activity: Step detected! Total=20, Cal=1
```

---

## ✅ WEEK 7-8: SOS SYSTEM

### Hardware Wiring

**Buzzer → ESP32-S3:**

```
Buzzer       ESP32-S3 Pin
VCC      →   5V (or 3.3V for quieter)
GND      →   GND
Signal   →   GPIO 25

Notes:
- Use active buzzer (has built-in oscillator)
- 5V is louder, 3.3V works but quieter
- Add 100Ω resistor in series (optional, for volume control)
```

### Software Integration

**Step 1: Add SOS System**

```cpp
// At top of volt_firmware_v6.ino
#include "sos_system.h"

// Create SOS system object
SOSSystem sosSystem;
```

**Step 2: Initialize in setup()**

```cpp
void setup() {
    // ... existing code ...

    // Add SOS system initialization
    pinMode(25, OUTPUT);  // Buzzer pin
    sosSystem.begin(25, &display);
    sosSystem.setAPIConfig(
        "https://your-api.com",  // API endpoint
        "your-api-key",          // API key
        "volt-001",              // Device ID
        CHILD_NAME               // Child name
    );
    Serial.println("SOS: Online");

    // ... rest of setup ...
}
```

**Step 3: Add Long-Press Detection in loop()**

```cpp
void loop() {
    // ... existing code ...

    // Check for SOS (5-second hold)
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

        // Show countdown
        if (pressDuration > 3000 && pressDuration < 5000) {
            display.clearDisplay();
            display.setTextSize(2);
            display.setCursor(0, 20);
            display.println("Hold for");
            display.println("SOS...");
            display.display();
        }

        // Trigger SOS at 5 seconds
        if (pressDuration >= 5000) {
            sosSystem.trigger(
                gpsTracker.getLatitude(),
                gpsTracker.getLongitude(),
                gpsTracker.isValid(),
                power.getBatteryPercent()
            );
            sosTriggered = true;
        }
    }

    if (!buttonPressed && buttonWasPressed) {
        buttonWasPressed = false;
    }

    // ... rest of loop ...
}
```

### Testing SOS System

**Test Protocol:**

```
1. Upload firmware with SOS code
2. Hold button for 5 seconds
3. Verify:
   ☐ Display shows "Hold for SOS..." at 3 seconds
   ☐ Display shows "SOS!" at 5 seconds
   ☐ Buzzer plays Morse code (... --- ...)
   ☐ Serial shows "SOS ACTIVATED!"
   ☐ API call attempted (check serial for HTTP response)

Expected Output:
[Button held for 3 seconds]
Display: "Hold for SOS..."

[Button held for 5 seconds]
🚨🚨🚨 SOS ACTIVATED! 🚨🚨🚨
Display: "SOS! Help is coming!"
Buzzer: [Morse code pattern]
SOS: Sending alert...
SOS: Alert sent successfully!
```

---

## ✅ WEEK 9-10: PARENTAL DASHBOARD

### Backend Setup (Firebase)

**Step 1: Create Firebase Project**

```
1. Go to console.firebase.google.com
2. Click "Add project"
3. Name: "VOLT-AI-Watch"
4. Enable Google Analytics (optional)
5. Create project

6. In project settings:
   - Go to "Service accounts"
   - Generate new private key
   - Save JSON file securely
```

**Step 2: Set Up Realtime Database**

```
1. In Firebase console, go to "Realtime Database"
2. Click "Create Database"
3. Start in test mode (for development)
4. Database URL: https://volt-ai-watch.firebaseio.com

5. Set up data structure:
{
  "devices": {
    "volt-001": {
      "location": {
        "latitude": 0,
        "longitude": 0,
        "valid": false,
        "timestamp": 0
      },
      "status": {
        "battery": 0,
        "steps": 0,
        "wifi": false,
        "gps_valid": false
      },
      "alerts": {
        "sos_001": {
          "type": "SOS",
          "timestamp": 0,
          "location": {...}
        }
      }
    }
  }
}
```

**Step 3: Set Up Authentication**

```
1. In Firebase console, go to "Authentication"
2. Click "Get started"
3. Enable "Email/Password"
4. Add your email as first user
5. Save credentials
```

### Frontend Setup (Web Dashboard)

**Step 1: Update Dashboard HTML**

```html
<!-- phase1_dashboard/index.html -->
<!-- Update configuration section: -->

<script>
  // Firebase Configuration
  const firebaseConfig = {
    apiKey: "YOUR_API_KEY",
    authDomain: "volt-ai-watch.firebaseapp.com",
    databaseURL: "https://volt-ai-watch.firebaseio.com",
    projectId: "volt-ai-watch",
    storageBucket: "volt-ai-watch.appspot.com",
    messagingSenderId: "YOUR_SENDER_ID",
    appId: "YOUR_APP_ID",
  };

  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);
  const database = firebase.database();

  // Listen for real-time updates
  const deviceRef = database.ref("devices/volt-001");
  deviceRef.on("value", (snapshot) => {
    const data = snapshot.val();
    updateDashboard(data);
  });
</script>
```

**Step 2: Deploy Dashboard**

```bash
# Option 1: Firebase Hosting (Recommended)
npm install -g firebase-tools
firebase login
firebase init hosting
firebase deploy

# Option 2: Local Testing
# Just open index.html in browser
# Use Live Server extension in VS Code

# Option 3: Vercel (Free)
# Push to GitHub
# Connect to Vercel
# Auto-deploy on push
```

### Testing Dashboard

**Test Protocol:**

```
1. Open dashboard in browser
2. Login with Firebase credentials
3. Verify:
   ☐ Map loads correctly
   ☐ Device status shows (even if offline)
   ☐ Can see location (if GPS active)
   ☐ Activity stats display
   ☐ SOS alerts appear when triggered

4. Test real-time updates:
   ☐ Trigger SOS on device
   ☐ Alert appears on dashboard within 5 seconds
   ☐ Location updates on map
   ☐ Status cards update
```

---

## ✅ WEEK 11-12: BATTERY OPTIMIZATION & TESTING

### Power Optimization Code

**Add to volt_firmware_v6.ino:**

```cpp
void optimizePower() {
    unsigned long idleTime = millis() - lastActivity;

    // 1. CPU Frequency Scaling
    if (idleTime > 60000) {  // 1 minute idle
        setCpuFrequencyMhz(80);   // Low power mode
    } else {
        setCpuFrequencyMhz(240);  // Full speed
    }

    // 2. WiFi Power Saving
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.setSleep(true);
        esp_wifi_set_ps(WIFI_PS_MAX_MODEM);
    }

    // 3. GPS Power Management
    static unsigned long lastGPSActive = 0;
    if (millis() - lastGPSActive > 30000) {
        gpsTracker.sleep();  // Sleep GPS
    }
    // Wake GPS every 30 seconds for update
    if (millis() - lastGPSActive > 30000) {
        gpsTracker.wake();
        lastGPSActive = millis();
    }

    // 4. Display Dimming
    if (idleTime > 30000) {
        display.dim(true);
    } else {
        display.dim(false);
    }

    // 5. Deep Sleep (after 5 minutes)
    if (idleTime > 300000) {
        enterDeepSleep();
    }
}

void enterDeepSleep() {
    Serial.println("Entering deep sleep...");

    // Save state
    // ... save important data ...

    // Configure wake sources
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0);  // Button wake
    esp_sleep_enable_timer_wakeup(300 * 1000000);  // 5 min timer

    // Display sleep message
    display.clearDisplay();
    display.setCursor(0, 20);
    display.println("Sleeping...");
    display.println("Press button to wake");
    display.display();
    delay(2000);

    // Enter deep sleep
    esp_deep_sleep_start();
}
```

### Comprehensive Testing

**Test Suite:**

```
1. GPS Accuracy Test
☐ Get GPS lock outdoors
☐ Compare coordinates with phone GPS
☐ Accuracy should be within 10 meters
☐ Test in different locations

2. Activity Tracking Test
☐ Walk 100 steps (count manually)
☐ Check step count on device
☐ Accuracy should be ±10%
☐ Test running, walking, standing

3. SOS System Test
☐ Trigger SOS (5-second hold)
☐ Verify alarm sounds
☐ Check dashboard receives alert
☐ Verify location included
☐ Test cooldown (1 minute)

4. Battery Life Test
☐ Full charge battery
☐ Run normal operations
☐ Record time to depletion
☐ Target: 72+ hours (3 days)
☐ Measure: Idle, active, sleep modes

5. Integration Test
☐ All features work together
☐ No conflicts or crashes
☐ Memory usage acceptable
☐ No memory leaks

6. Stress Test
☐ Run for 24 hours continuous
☐ Trigger all features repeatedly
☐ Monitor for crashes
☐ Check memory stability

7. User Acceptance Test
☐ Give to beta tester (family member)
☐ Use for 1 week normally
☐ Collect feedback
☐ Fix any issues found
```

---

## 📊 Phase 1 Completion Checklist

### Hardware Complete

- [ ] GPS module installed and working
- [ ] Accelerometer installed and working
- [ ] Buzzer installed and working
- [ ] Larger battery installed
- [ ] Audio upgrade installed (optional)
- [ ] All wiring secure and tested

### Software Complete

- [ ] GPS tracking functional
- [ ] Location updates every 30 seconds
- [ ] Activity tracking counts steps
- [ ] SOS system triggers on long-press
- [ ] SOS alert sent to dashboard
- [ ] Battery optimization implemented
- [ ] Deep sleep working
- [ ] All features tested

### Dashboard Complete

- [ ] Firebase project created
- [ ] Database structure set up
- [ ] Authentication configured
- [ ] Web dashboard deployed
- [ ] Real-time updates working
- [ ] SOS alerts display
- [ ] Location map functional

### Testing Complete

- [ ] GPS accuracy ±10m
- [ ] Step counting ±10%
- [ ] SOS response <5 seconds
- [ ] Battery life 3+ days
- [ ] No crashes in 24h test
- [ ] Beta testing complete
- [ ] All issues resolved

### Documentation Complete

- [ ] Setup guide written
- [ ] Troubleshooting guide created
- [ ] API documentation complete
- [ ] User manual drafted
- [ ] Code commented
- [ ] README updated

### Metrics Achieved

- [ ] Safety score: 9/10
- [ ] Overall score: 41/50
- [ ] Battery life: 3+ days
- [ ] GPS accuracy: <10m
- [ ] Step accuracy: ±10%
- [ ] SOS reliability: 100%
- [ ] System uptime: >99%

---

## 🎯 Success Criteria

**Phase 1 is complete when:**

1. ✅ All 5 prototype units assembled
2. ✅ GPS tracking working reliably
3. ✅ SOS system tested and functional
4. ✅ Activity tracking accurate
5. ✅ Battery life 3+ days confirmed
6. ✅ Parental dashboard operational
7. ✅ Beta testing successful
8. ✅ Ready to proceed to Phase 2

---

## 🚀 Next Steps After Phase 1

**Immediate (Week 13):**

1. Review Phase 1 results
2. Document lessons learned
3. Order Phase 2 components
4. Begin PCB design

**Phase 2 Preview:**

- Professional PCB design
- IP67 waterproof enclosure
- Audio quality upgrade
- Manufacturing process
- 50 production units

---

## 📞 Support & Resources

**If you get stuck:**

1. Check README.md in phase1_firmware/
2. Review troubleshooting section
3. Check serial monitor output
4. Test components individually
5. Ask for help with specific error messages

**Useful Resources:**

- TinyGPS++ documentation
- MPU6050 datasheet
- ESP32 deep sleep guide
- Firebase documentation
- Arduino forum

---

**START NOW: Order components today and begin Phase 1!**

Total Time: 12 weeks
Total Cost: $130-150
Expected Result: Production-ready safety features

**You have everything you need to complete Phase 1. Let's build!**
