# VOLT AI Watch - Phase 1 Implementation Guide

## Safety Parity (3 Months) - CRITICAL FEATURES

---

## 🎯 Phase 1 Goals

**Objective**: Match basic safety standards to be taken seriously by parents

**Timeline**: 3 months (12 weeks)

**Expected Outcome**:

- Safety Score: 7/10 → 9/10
- Overall Score: 38/50 → 41/50
- Market Position: Niche Innovator → Competitive Alternative

---

## 📦 Hardware Components to Order

### Immediate Orders (Week 1):

| Component       | Model        | Quantity | Cost/Unit | Total    | Supplier          |
| --------------- | ------------ | -------- | --------- | -------- | ----------------- |
| GPS Module      | NEO-6M       | 5        | $8        | $40      | Amazon/AliExpress |
| Audio Amplifier | MAX98357A    | 5        | $3        | $15      | Adafruit/Amazon   |
| Microphone      | INMP441      | 5        | $4        | $20      | Amazon            |
| Accelerometer   | MPU6050      | 5        | $2        | $10      | Amazon/AliExpress |
| Larger Battery  | 1200mAh LiPo | 5        | $8        | $40      | Amazon            |
| Jumper Wires    | Dupont       | 1 set    | $5        | $5       | Amazon            |
| **TOTAL**       |              |          |           | **$130** |                   |

### Recommended Suppliers:

- **Amazon**: Fast shipping (2-3 days)
- **AliExpress**: Cheaper but slower (2-4 weeks)
- **Adafruit**: Quality components, good documentation

### Shopping Links:

```
GPS Module: Search "NEO-6M GPS Module ESP32"
Audio Amp: Search "MAX98357A I2S Amplifier"
Microphone: Search "INMP441 I2S Microphone"
Accelerometer: Search "MPU6050 GY-521"
Battery: Search "1200mAh 3.7V LiPo Battery JST"
```

---

## 🗓️ Week-by-Week Implementation Plan

### Week 1-2: Setup & GPS Integration

**Goals**:

- Order all components
- Set up development environment
- Integrate GPS tracking
- Test location accuracy

**Tasks**:

1. ✅ Order hardware components
2. ✅ Install required libraries
3. ✅ Wire GPS module to ESP32
4. ✅ Implement GPS tracking code
5. ✅ Test location accuracy
6. ✅ Add location API endpoint

**Deliverables**:

- GPS module connected and working
- Location data accessible via API
- Basic location logging

---

### Week 3-4: Emergency SOS & Audio Upgrade

**Goals**:

- Implement emergency SOS button
- Upgrade audio quality
- Test alert system

**Tasks**:

1. ✅ Implement long-press SOS detection
2. ✅ Create SOS alert API
3. ✅ Wire audio components
4. ✅ Upgrade audio drivers
5. ✅ Test voice quality
6. ✅ Implement SMS/email alerts

**Deliverables**:

- SOS button functional
- Alert system working
- Improved voice quality

---

### Week 5-6: Parental Dashboard (Backend)

**Goals**:

- Set up backend infrastructure
- Create API endpoints
- Implement authentication

**Tasks**:

1. ✅ Set up Firebase project
2. ✅ Create REST API server
3. ✅ Implement authentication
4. ✅ Create location tracking API
5. ✅ Create device status API
6. ✅ Set up database schema

**Deliverables**:

- Backend API operational
- Authentication working
- Database configured

---

### Week 7-8: Parental Dashboard (Frontend)

**Goals**:

- Build web dashboard
- Implement real-time tracking
- Create settings interface

**Tasks**:

1. ✅ Set up React project
2. ✅ Create login page
3. ✅ Build location map view
4. ✅ Create device status page
5. ✅ Implement settings panel
6. ✅ Add activity history

**Deliverables**:

- Web dashboard live
- Real-time location tracking
- Device management interface

---

### Week 9-10: Battery Optimization & Activity Tracking

**Goals**:

- Extend battery life to 3+ days
- Add activity tracking
- Optimize power consumption

**Tasks**:

1. ✅ Implement aggressive deep sleep
2. ✅ Optimize WiFi power usage
3. ✅ Wire accelerometer
4. ✅ Implement step counting
5. ✅ Add activity detection
6. ✅ Test battery life

**Deliverables**:

- Battery life 3+ days
- Activity tracking functional
- Power consumption optimized

---

### Week 11-12: Testing & Documentation

**Goals**:

- Comprehensive testing
- Beta user feedback
- Documentation complete

**Tasks**:

1. ✅ Integration testing
2. ✅ Beta testing (5-10 users)
3. ✅ Bug fixes
4. ✅ Documentation
5. ✅ Setup guides
6. ✅ Prepare for Phase 2

**Deliverables**:

- All features tested
- Documentation complete
- Ready for wider release

---

## 💻 Technical Implementation Details

### 1. GPS Integration

#### Hardware Wiring:

```
NEO-6M GPS Module → ESP32-S3
VCC → 3.3V
GND → GND
TX  → GPIO 16 (RX2)
RX  → GPIO 17 (TX2)
```

#### Firmware Code:

```cpp
// Add to includes
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// GPS Configuration
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD 9600

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

// GPS Data Structure
struct GPSData {
    double latitude;
    double longitude;
    double altitude;
    float speed;
    int satellites;
    bool valid;
    unsigned long timestamp;
};

GPSData currentLocation;

void setupGPS() {
    gpsSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
    Serial.println("GPS: Initializing...");
}

void updateGPS() {
    while (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
            if (gps.location.isValid()) {
                currentLocation.latitude = gps.location.lat();
                currentLocation.longitude = gps.location.lng();
                currentLocation.altitude = gps.altitude.meters();
                currentLocation.speed = gps.speed.kmph();
                currentLocation.satellites = gps.satellites.value();
                currentLocation.valid = true;
                currentLocation.timestamp = millis();

                Serial.printf("GPS: Lat=%.6f, Lng=%.6f, Sats=%d\n",
                    currentLocation.latitude,
                    currentLocation.longitude,
                    currentLocation.satellites);
            }
        }
    }
}

// API Endpoint for location
String getLocationJSON() {
    StaticJsonDocument<256> doc;
    doc["latitude"] = currentLocation.latitude;
    doc["longitude"] = currentLocation.longitude;
    doc["altitude"] = currentLocation.altitude;
    doc["speed"] = currentLocation.speed;
    doc["satellites"] = currentLocation.satellites;
    doc["valid"] = currentLocation.valid;
    doc["timestamp"] = currentLocation.timestamp;

    String output;
    serializeJson(doc, output);
    return output;
}
```

---

### 2. Emergency SOS System

#### Firmware Code:

```cpp
// SOS Configuration
#define SOS_LONG_PRESS_TIME 5000  // 5 seconds
#define SOS_COOLDOWN 60000        // 1 minute cooldown

bool sosActive = false;
unsigned long sosLastTriggered = 0;
unsigned long buttonPressStart = 0;

void checkSOSButton() {
    static bool buttonWasPressed = false;
    bool buttonPressed = (digitalRead(BUTTON_PIN) == LOW);

    if (buttonPressed && !buttonWasPressed) {
        // Button just pressed
        buttonPressStart = millis();
        buttonWasPressed = true;
    }

    if (buttonPressed && buttonWasPressed) {
        // Button held down
        unsigned long pressDuration = millis() - buttonPressStart;

        if (pressDuration >= SOS_LONG_PRESS_TIME && !sosActive) {
            // Trigger SOS
            triggerSOS();
        }
    }

    if (!buttonPressed && buttonWasPressed) {
        // Button released
        buttonWasPressed = false;
    }
}

void triggerSOS() {
    // Check cooldown
    if (millis() - sosLastTriggered < SOS_COOLDOWN) {
        Serial.println("SOS: Cooldown active");
        return;
    }

    sosActive = true;
    sosLastTriggered = millis();

    Serial.println("🚨 SOS ACTIVATED! 🚨");

    // Visual feedback
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.println("SOS!");
    display.setTextSize(1);
    display.setCursor(0, 45);
    display.println("Help is coming!");
    display.display();

    // Audio feedback
    for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        tone(BUZZER_PIN, 1000, 200);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
    }

    // Send SOS alert
    sendSOSAlert();

    sosActive = false;
}

void sendSOSAlert() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("SOS: No WiFi connection");
        return;
    }

    HTTPClient http;
    http.begin("https://your-api.com/api/sos");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(API_KEY));

    StaticJsonDocument<512> doc;
    doc["device_id"] = DEVICE_ID;
    doc["child_name"] = CHILD_NAME;
    doc["timestamp"] = millis();
    doc["location"]["latitude"] = currentLocation.latitude;
    doc["location"]["longitude"] = currentLocation.longitude;
    doc["location"]["valid"] = currentLocation.valid;
    doc["battery"] = power.getBatteryPercent();
    doc["type"] = "SOS";

    String payload;
    serializeJson(doc, payload);

    int httpCode = http.POST(payload);

    if (httpCode == HTTP_CODE_OK) {
        Serial.println("SOS: Alert sent successfully");
    } else {
        Serial.printf("SOS: Alert failed (HTTP %d)\n", httpCode);
    }

    http.end();
}
```

---

### 3. Audio Quality Upgrade

#### Hardware Wiring:

```
MAX98357A Amplifier → ESP32-S3
VIN  → 3.3V
GND  → GND
DIN  → GPIO 13 (I2S Data)
BCLK → GPIO 2  (I2S Clock)
LRC  → GPIO 15 (I2S WS)

INMP441 Microphone → ESP32-S3
VDD  → 3.3V
GND  → GND
SD   → GPIO 13 (I2S Data)
SCK  → GPIO 2  (I2S Clock)
WS   → GPIO 15 (I2S WS)
L/R  → GND (Left channel)
```

#### Firmware Code:

```cpp
// Improved I2S Configuration
void setupI2SImproved(int mode) {
    i2s_driver_uninstall(I2S_PORT);

    i2s_config_t i2s_config = {
        .mode = (mode == 0) ?
            (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX) :
            (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 1024,
        .use_apll = true,  // Better audio quality
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = 2,
        .ws_io_num = 15,
        .data_out_num = 13,
        .data_in_num = 13
    };

    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pin_config);

    // Set volume (0-100)
    i2s_set_clk(I2S_PORT, 16000, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
}

// Noise reduction
void applyNoiseReduction(int16_t* buffer, size_t length) {
    // Simple noise gate
    const int16_t NOISE_THRESHOLD = 100;

    for (size_t i = 0; i < length; i++) {
        if (abs(buffer[i]) < NOISE_THRESHOLD) {
            buffer[i] = 0;
        }
    }
}
```

---

### 4. Parental Dashboard Backend

#### Technology Stack:

- **Backend**: Node.js + Express
- **Database**: Firebase Realtime Database
- **Authentication**: Firebase Auth
- **Hosting**: Vercel (free tier)

#### API Endpoints:

```javascript
// server.js
const express = require("express");
const admin = require("firebase-admin");
const cors = require("cors");

const app = express();
app.use(cors());
app.use(express.json());

// Initialize Firebase Admin
admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://your-project.firebaseio.com",
});

const db = admin.database();

// Authentication middleware
const authenticate = async (req, res, next) => {
  const token = req.headers.authorization?.split("Bearer ")[1];
  if (!token) {
    return res.status(401).json({ error: "No token provided" });
  }

  try {
    const decodedToken = await admin.auth().verifyIdToken(token);
    req.user = decodedToken;
    next();
  } catch (error) {
    res.status(401).json({ error: "Invalid token" });
  }
};

// Get device location
app.get("/api/device/:deviceId/location", authenticate, async (req, res) => {
  try {
    const snapshot = await db
      .ref(`devices/${req.params.deviceId}/location`)
      .once("value");
    res.json(snapshot.val());
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// Get device status
app.get("/api/device/:deviceId/status", authenticate, async (req, res) => {
  try {
    const snapshot = await db
      .ref(`devices/${req.params.deviceId}/status`)
      .once("value");
    res.json(snapshot.val());
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// Update device location (from ESP32)
app.post("/api/device/:deviceId/location", async (req, res) => {
  const apiKey = req.headers["x-api-key"];

  // Verify device API key
  if (apiKey !== process.env.DEVICE_API_KEY) {
    return res.status(401).json({ error: "Invalid API key" });
  }

  try {
    await db.ref(`devices/${req.params.deviceId}/location`).set({
      ...req.body,
      timestamp: admin.database.ServerValue.TIMESTAMP,
    });
    res.json({ success: true });
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// SOS Alert endpoint
app.post("/api/device/:deviceId/sos", async (req, res) => {
  const apiKey = req.headers["x-api-key"];

  if (apiKey !== process.env.DEVICE_API_KEY) {
    return res.status(401).json({ error: "Invalid API key" });
  }

  try {
    // Save SOS alert
    await db.ref(`devices/${req.params.deviceId}/alerts`).push({
      type: "SOS",
      ...req.body,
      timestamp: admin.database.ServerValue.TIMESTAMP,
    });

    // Send notification to parent (implement with FCM or email)
    await sendSOSNotification(req.params.deviceId, req.body);

    res.json({ success: true });
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// Get activity history
app.get("/api/device/:deviceId/activity", authenticate, async (req, res) => {
  try {
    const snapshot = await db
      .ref(`devices/${req.params.deviceId}/activity`)
      .orderByChild("timestamp")
      .limitToLast(100)
      .once("value");
    res.json(snapshot.val());
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
```

---

### 5. Battery Optimization

#### Firmware Code:

```cpp
// Power Management Configuration
#define DEEP_SLEEP_TIMEOUT 300000  // 5 minutes
#define LIGHT_SLEEP_TIMEOUT 60000  // 1 minute
#define GPS_UPDATE_INTERVAL 30000  // 30 seconds
#define WIFI_RECONNECT_INTERVAL 60000  // 1 minute

unsigned long lastActivity = 0;
unsigned long lastGPSUpdate = 0;
unsigned long lastWiFiCheck = 0;

void optimizePowerConsumption() {
    // 1. Reduce CPU frequency when idle
    if (millis() - lastActivity > LIGHT_SLEEP_TIMEOUT) {
        setCpuFrequencyMhz(80);  // Down from 240MHz
    } else {
        setCpuFrequencyMhz(240);  // Full speed when active
    }

    // 2. WiFi power saving
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.setSleep(true);
        esp_wifi_set_ps(WIFI_PS_MAX_MODEM);
    }

    // 3. GPS power management
    if (millis() - lastGPSUpdate > GPS_UPDATE_INTERVAL) {
        // Wake GPS, get location, sleep GPS
        wakeGPS();
        updateGPS();
        sleepGPS();
        lastGPSUpdate = millis();
    }

    // 4. Display dimming
    if (millis() - lastActivity > 30000) {
        display.dim(true);
    }

    // 5. Deep sleep when very idle
    if (millis() - lastActivity > DEEP_SLEEP_TIMEOUT) {
        enterDeepSleep();
    }
}

void enterDeepSleep() {
    Serial.println("Entering deep sleep...");

    // Save state
    saveState();

    // Configure wake sources
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0);  // Button wake
    esp_sleep_enable_timer_wakeup(300 * 1000000);  // 5 min timer

    // Display sleep message
    display.clearDisplay();
    display.setCursor(0, 20);
    display.println("Sleeping...");
    display.println("Press button");
    display.println("to wake");
    display.display();
    delay(2000);

    // Enter deep sleep
    esp_deep_sleep_start();
}

void wakeGPS() {
    // Send wake command to GPS
    gpsSerial.println("$PMTK225,0*2B");  // Full power mode
    delay(100);
}

void sleepGPS() {
    // Send sleep command to GPS
    gpsSerial.println("$PMTK161,0*28");  // Standby mode
}

// Battery monitoring
int getBatteryVoltage() {
    int raw = analogRead(BATTERY_PIN);
    // Convert to voltage (adjust for your voltage divider)
    float voltage = (raw / 4095.0) * 3.3 * 2.0;  // Assuming 1:1 divider
    return (int)(voltage * 1000);  // Return in mV
}

int getBatteryPercent() {
    int voltage = getBatteryVoltage();

    // LiPo voltage curve (approximate)
    if (voltage >= 4200) return 100;
    if (voltage >= 4100) return 90;
    if (voltage >= 4000) return 80;
    if (voltage >= 3900) return 70;
    if (voltage >= 3800) return 60;
    if (voltage >= 3700) return 50;
    if (voltage >= 3600) return 40;
    if (voltage >= 3500) return 30;
    if (voltage >= 3400) return 20;
    if (voltage >= 3300) return 10;
    return 5;
}
```

---

### 6. Activity Tracking

#### Hardware Wiring:

```
MPU6050 Accelerometer → ESP32-S3
VCC → 3.3V
GND → GND
SCL → GPIO 22 (I2C Clock)
SDA → GPIO 21 (I2C Data)
```

#### Firmware Code:

```cpp
#include <Wire.h>
#include <MPU6050.h>

MPU6050 accel;

// Activity tracking variables
int dailySteps = 0;
int dailyCalories = 0;
bool isMoving = false;
unsigned long lastStepTime = 0;

// Step detection parameters
#define STEP_THRESHOLD 15000
#define STEP_MIN_INTERVAL 300  // ms between steps

void setupActivityTracking() {
    Wire.begin(21, 22);  // SDA, SCL
    accel.initialize();

    if (accel.testConnection()) {
        Serial.println("Activity: MPU6050 connected");
    } else {
        Serial.println("Activity: MPU6050 connection failed");
    }

    // Configure accelerometer
    accel.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
}

void updateActivityTracking() {
    int16_t ax, ay, az;
    accel.getAcceleration(&ax, &ay, &az);

    // Calculate magnitude
    long magnitude = sqrt(ax*ax + ay*ay + az*az);

    // Step detection
    if (magnitude > STEP_THRESHOLD) {
        unsigned long now = millis();
        if (now - lastStepTime > STEP_MIN_INTERVAL) {
            dailySteps++;
            lastStepTime = now;

            // Calculate calories (rough estimate)
            dailyCalories = dailySteps * 0.04;  // ~0.04 cal per step

            Serial.printf("Activity: Steps=%d, Calories=%d\n",
                dailySteps, dailyCalories);
        }
    }

    // Movement detection
    isMoving = (magnitude > 5000);
}

void resetDailyActivity() {
    dailySteps = 0;
    dailyCalories = 0;
}

String getActivityJSON() {
    StaticJsonDocument<256> doc;
    doc["steps"] = dailySteps;
    doc["calories"] = dailyCalories;
    doc["is_moving"] = isMoving;
    doc["timestamp"] = millis();

    String output;
    serializeJson(doc, output);
    return output;
}
```

---

## 📱 Parental Dashboard Frontend

### Technology Stack:

- **Framework**: React 18
- **Styling**: Tailwind CSS
- **Maps**: Leaflet / Google Maps
- **State**: React Context / Redux
- **Build**: Vite
- **Hosting**: Vercel

### Key Components:

#### 1. Login Page

```jsx
// src/pages/Login.jsx
import { useState } from "react";
import { signInWithEmailAndPassword } from "firebase/auth";
import { auth } from "../firebase";

export default function Login() {
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState("");

  const handleLogin = async (e) => {
    e.preventDefault();
    try {
      await signInWithEmailAndPassword(auth, email, password);
    } catch (err) {
      setError(err.message);
    }
  };

  return (
    <div className="min-h-screen flex items-center justify-center bg-gradient-to-br from-purple-600 to-blue-600">
      <div className="bg-white p-8 rounded-lg shadow-xl w-96">
        <h1 className="text-3xl font-bold mb-6 text-center">
          VOLT Parent Dashboard
        </h1>
        {error && (
          <div className="bg-red-100 text-red-700 p-3 rounded mb-4">
            {error}
          </div>
        )}
        <form onSubmit={handleLogin}>
          <input
            type="email"
            placeholder="Email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            className="w-full p-3 border rounded mb-4"
          />
          <input
            type="password"
            placeholder="Password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            className="w-full p-3 border rounded mb-4"
          />
          <button className="w-full bg-purple-600 text-white p-3 rounded hover:bg-purple-700">
            Login
          </button>
        </form>
      </div>
    </div>
  );
}
```

#### 2. Location Map

```jsx
// src/components/LocationMap.jsx
import { MapContainer, TileLayer, Marker, Popup } from "react-leaflet";
import "leaflet/dist/leaflet.css";

export default function LocationMap({ location }) {
  if (!location || !location.valid) {
    return <div className="text-center p-8">No location data available</div>;
  }

  return (
    <MapContainer
      center={[location.latitude, location.longitude]}
      zoom={15}
      className="h-96 rounded-lg"
    >
      <TileLayer
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
        attribution="&copy; OpenStreetMap contributors"
      />
      <Marker position={[location.latitude, location.longitude]}>
        <Popup>
          <div>
            <strong>Current Location</strong>
            <br />
            Lat: {location.latitude.toFixed(6)}
            <br />
            Lng: {location.longitude.toFixed(6)}
            <br />
            Satellites: {location.satellites}
          </div>
        </Popup>
      </Marker>
    </MapContainer>
  );
}
```

#### 3. Device Status

```jsx
// src/components/DeviceStatus.jsx
export default function DeviceStatus({ status }) {
  return (
    <div className="grid grid-cols-2 md:grid-cols-4 gap-4">
      <div className="bg-white p-4 rounded-lg shadow">
        <div className="text-gray-500 text-sm">Battery</div>
        <div className="text-2xl font-bold">{status.battery}%</div>
      </div>
      <div className="bg-white p-4 rounded-lg shadow">
        <div className="text-gray-500 text-sm">Steps Today</div>
        <div className="text-2xl font-bold">{status.steps}</div>
      </div>
      <div className="bg-white p-4 rounded-lg shadow">
        <div className="text-gray-500 text-sm">WiFi</div>
        <div className="text-2xl font-bold">{status.wifi ? "✓" : "✗"}</div>
      </div>
      <div className="bg-white p-4 rounded-lg shadow">
        <div className="text-gray-500 text-sm">GPS</div>
        <div className="text-2xl font-bold">{status.gps_valid ? "✓" : "✗"}</div>
      </div>
    </div>
  );
}
```

---

## ✅ Testing Checklist

### Hardware Testing:

- [ ] GPS module receives satellite signals
- [ ] GPS accuracy within 10 meters
- [ ] Audio quality improved vs. baseline
- [ ] Microphone picks up voice clearly
- [ ] Accelerometer detects movement
- [ ] Battery lasts 3+ days with normal use
- [ ] All components properly wired
- [ ] No interference between modules

### Firmware Testing:

- [ ] GPS data updates every 30 seconds
- [ ] SOS button triggers after 5-second hold
- [ ] SOS alert sent successfully
- [ ] Location API returns valid data
- [ ] Activity tracking counts steps accurately
- [ ] Deep sleep activates after 5 minutes
- [ ] Device wakes from deep sleep
- [ ] Battery percentage accurate

### Backend Testing:

- [ ] API endpoints respond correctly
- [ ] Authentication works
- [ ] Location data saves to database
- [ ] SOS alerts trigger notifications
- [ ] Activity history retrieves correctly
- [ ] API handles errors gracefully
- [ ] Rate limiting works
- [ ] CORS configured properly

### Frontend Testing:

- [ ] Login page works
- [ ] Map displays location correctly
- [ ] Real-time updates work
- [ ] Device status shows accurate data
- [ ] Settings can be changed
- [ ] Activity history displays
- [ ] Responsive on mobile
- [ ] Works on all browsers

### Integration Testing:

- [ ] ESP32 → API → Database flow works
- [ ] Real-time location updates on dashboard
- [ ] SOS alert appears on dashboard
- [ ] Settings sync between dashboard and device
- [ ] Activity data syncs correctly
- [ ] Multiple devices supported
- [ ] Offline mode
