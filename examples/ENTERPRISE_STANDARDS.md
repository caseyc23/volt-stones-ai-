# VOLT AI Watch - Enterprise Standards Framework

## Professional-Grade Development Standards

---

## 🎯 Executive Summary

This document establishes enterprise-grade standards for the VOLT AI Watch project. Based on competitive analysis showing VOLT tied at #1 (38/50) with Apple Watch SE and Echo Dot Kids, we must maintain AI leadership while achieving professional quality in all other areas.

**Mission**: Transform VOLT from innovative prototype into production-ready, enterprise-grade consumer product that competes with billion-dollar companies.

**Target Standards**: Match or exceed Apple, Google, and Amazon quality benchmarks.

---

## 📊 Current State vs Enterprise Requirements

### Current State (v5.00/v6.00)

| Category      | Current | Enterprise Target | Gap |
| ------------- | ------- | ----------------- | --- |
| Code Quality  | 6/10    | 9/10              | -3  |
| Security      | 5/10    | 10/10             | -5  |
| Testing       | 2/10    | 9/10              | -7  |
| Documentation | 6/10    | 9/10              | -3  |
| Reliability   | 7/10    | 10/10             | -3  |
| Performance   | 7/10    | 9/10              | -2  |
| DevOps        | 3/10    | 9/10              | -6  |

### Priority Order

1. **Security** (Critical - 5 point gap)
2. **Testing** (Critical - 7 point gap)
3. **DevOps** (High - 6 point gap)
4. **Code Quality** (High - 3 point gap)
5. **Documentation** (Medium - 3 point gap)
6. **Reliability** (Medium - 3 point gap)
7. **Performance** (Low - 2 point gap)

---

## 🏗️ SECTION 1: CODE ARCHITECTURE

### 1.1 Directory Structure (Enterprise Standard)

```
volt-ai-watch/
├── firmware/                           # ESP32 firmware
│   ├── src/
│   │   ├── core/                      # Core system (DO NOT MODIFY without review)
│   │   │   ├── system/
│   │   │   │   ├── boot_manager.cpp   # Boot sequence & initialization
│   │   │   │   ├── power_manager.cpp  # Power & battery management
│   │   │   │   ├── watchdog.cpp       # System monitoring & recovery
│   │   │   │   └── error_handler.cpp  # Centralized error handling
│   │   │   ├── hardware/
│   │   │   │   ├── hal_display.cpp    # Display abstraction layer
│   │   │   │   ├── hal_audio.cpp      # Audio I/O abstraction
│   │   │   │   ├── hal_button.cpp     # Button input handling
│   │   │   │   └── hal_sensors.cpp    # Sensor abstraction
│   │   │   └── network/
│   │   │       ├── wifi_manager.cpp   # WiFi connection management
│   │   │       ├── api_client.cpp     # HTTP/HTTPS client
│   │   │       ├── ota_manager.cpp    # Over-the-air updates
│   │   │       └── security.cpp       # TLS, encryption, auth
│   │   ├── features/                  # Feature modules (modular design)
│   │   │   ├── ai/
│   │   │   │   ├── voice_processor.cpp    # Voice I/O
│   │   │   │   ├── openai_client.cpp      # OpenAI API integration
│   │   │   │   ├── conversation_manager.cpp # Chat history & context
│   │   │   │   └── personality_engine.cpp  # Personality customization
│   │   │   ├── safety/
│   │   │   │   ├── sos_system.cpp         # Emergency alerts
│   │   │   │   ├── geofence.cpp           # Location boundaries
│   │   │   │   ├── content_filter.cpp     # Age-appropriate filtering
│   │   │   │   └── parental_controls.cpp  # Parent settings
│   │   │   ├── tracking/
│   │   │   │   ├── gps_tracker.cpp        # GPS location
│   │   │   │   ├── activity_tracker.cpp   # Steps, calories
│   │   │   │   └── health_monitor.cpp     # Heart rate, sleep
│   │   │   └── personalization/
│   │   │       ├── child_profile.cpp      # Child settings
│   │   │       ├── custom_messages.cpp    # Parent messages
│   │   │       └── preferences.cpp        # User preferences
│   │   ├── shared/                    # Shared utilities
│   │   │   ├── utils/
│   │   │   │   ├── logger.cpp             # Logging system
│   │   │   │   ├── crypto.cpp             # Encryption utilities
│   │   │   │   ├── json_parser.cpp        # JSON handling
│   │   │   │   └── time_sync.cpp          # NTP time sync
│   │   │   └── config/
│   │   │       ├── config_manager.cpp     # Configuration storage
│   │   │       ├── secrets_manager.cpp    # Secure credential storage
│   │   │       └── defaults.cpp           # Default settings
│   │   └── main.cpp                   # Application entry point
│   ├── include/                       # Header files
│   ├── lib/                          # Third-party libraries
│   ├── test/                         # Test suites
│   │   ├── unit/                     # Unit tests
│   │   ├── integration/              # Integration tests
│   │   └── mocks/                    # Mock objects
│   ├── platformio.ini                # Build configuration
│   └── CMakeLists.txt                # CMake build file
├── backend/                          # Cloud backend (Node.js)
│   ├── src/
│   │   ├── api/                      # REST API endpoints
│   │   ├── services/                 # Business logic
│   │   ├── models/                   # Data models
│   │   ├── middleware/               # Express middleware
│   │   └── utils/                    # Utilities
│   ├── tests/                        # Backend tests
│   ├── config/                       # Configuration
│   └── package.json
├── dashboard/                        # Parental dashboard (React)
│   ├── src/
│   │   ├── components/               # React components
│   │   ├── pages/                    # Page components
│   │   ├── services/                 # API services
│   │   ├── hooks/                    # Custom hooks
│   │   └── utils/                    # Utilities
│   ├── public/                       # Static assets
│   ├── tests/                        # Frontend tests
│   └── package.json
├── mobile/                           # Mobile app (React Native)
│   ├── src/
│   ├── android/
│   ├── ios/
│   └── package.json
├── docs/                             # Documentation
│   ├── api/                          # API documentation
│   ├── hardware/                     # Hardware guides
│   ├── architecture/                 # Architecture docs
│   └── user/                         # User manuals
├── tools/                            # Development tools
│   ├── build/                        # Build scripts
│   ├── test/                         # Test runners
│   └── deploy/                       # Deployment automation
├── .github/                          # GitHub workflows
│   └── workflows/                    # CI/CD pipelines
├── docker/                           # Docker configurations
├── scripts/                          # Utility scripts
└── README.md                         # Project overview
```

### 1.2 Code Quality Standards

#### Naming Conventions

```cpp
// Classes: PascalCase
class VoiceProcessor { };
class GPSTracker { };

// Functions/Methods: camelCase
void processAudioInput();
bool isLocationValid();

// Variables: camelCase
int batteryLevel;
String childName;

// Constants: UPPER_SNAKE_CASE
const int MAX_RETRIES = 3;
const char* API_ENDPOINT = "https://api.volt.com";

// Private members: prefix with underscore
class Example {
private:
    int _privateValue;
    void _privateMethod();
};

// Enums: PascalCase with UPPER_SNAKE_CASE values
enum class ErrorCode {
    SUCCESS,
    NETWORK_ERROR,
    GPS_ERROR
};
```

#### File Organization

```cpp
// header_file.h
#ifndef HEADER_FILE_H
#define HEADER_FILE_H

// 1. System includes
#include <Arduino.h>
#include <WiFi.h>

// 2. Third-party includes
#include <ArduinoJson.h>

// 3. Project includes
#include "config.h"
#include "logger.h"

// 4. Forward declarations
class DependentClass;

// 5. Constants
const int BUFFER_SIZE = 1024;

// 6. Class declaration
/**
 * @brief Brief description of class
 *
 * Detailed description of what this class does,
 * its responsibilities, and usage examples.
 */
class MyClass {
public:
    // Public interface
    MyClass();
    ~MyClass();

    bool initialize();
    void update();

private:
    // Private implementation
    int _internalState;
    void _helperMethod();
};

#endif // HEADER_FILE_H
```

#### Documentation Standards (Doxygen)

````cpp
/**
 * @file gps_tracker.h
 * @brief GPS tracking and location management
 * @author VOLT Team
 * @version 6.0.0
 * @date 2024-01-24
 *
 * This module handles all GPS-related functionality including
 * location tracking, geofencing, and distance calculations.
 */

/**
 * @class GPSTracker
 * @brief Manages GPS hardware and location data
 *
 * The GPSTracker class provides a high-level interface for GPS
 * operations, including location updates, power management, and
 * geofencing capabilities.
 *
 * @example
 * ```cpp
 * GPSTracker gps;
 * gps.begin(16, 17);  // RX, TX pins
 * gps.update();
 * if (gps.isValid()) {
 *     Serial.printf("Lat: %.6f, Lng: %.6f\n",
 *         gps.getLatitude(), gps.getLongitude());
 * }
 * ```
 */
class GPSTracker {
public:
    /**
     * @brief Initialize GPS module
     * @param rxPin UART RX pin number
     * @param txPin UART TX pin number
     * @param baudRate Communication baud rate (default: 9600)
     * @return true if initialization successful, false otherwise
     * @throws None (embedded system - no exceptions)
     */
    bool begin(int rxPin, int txPin, int baudRate = 9600);

    /**
     * @brief Update GPS data from module
     *
     * Reads available data from GPS module and updates internal
     * location state. Should be called regularly in main loop.
     *
     * @note This is a non-blocking operation
     * @see isValid() to check if location data is current
     */
    void update();

    /**
     * @brief Get current latitude
     * @return Latitude in decimal degrees (-90 to +90)
     * @warning Check isValid() before using this value
     */
    double getLatitude() const;
};
````

---

## 🔒 SECTION 2: SECURITY STANDARDS

### 2.1 Security Architecture

#### Threat Model

```
┌─────────────────────────────────────────────────────────┐
│                    THREAT LANDSCAPE                      │
├─────────────────────────────────────────────────────────┤
│ 1. Network Attacks                                       │
│    - Man-in-the-middle (MITM)                           │
│    - DNS spoofing                                        │
│    - API key theft                                       │
│                                                          │
│ 2. Physical Attacks                                      │
│    - Device theft                                        │
│    - Firmware extraction                                 │
│    - Debug port access                                   │
│                                                          │
│ 3. Software Attacks                                      │
│    - Malicious OTA updates                              │
│    - Buffer overflows                                    │
│    - Injection attacks                                   │
│                                                          │
│ 4. Privacy Attacks                                       │
│    - Location tracking                                   │
│    - Conversation eavesdropping                         │
│    - Data exfiltration                                   │
└─────────────────────────────────────────────────────────┘
```

#### Security Layers

```cpp
// Layer 1: Hardware Security
class HardwareSecurity {
public:
    // Secure boot with signature verification
    bool verifyBootSignature();

    // Flash encryption (ESP32 feature)
    void enableFlashEncryption();

    // Secure key storage in eFuse
    void storeSecureKey(const uint8_t* key);
};

// Layer 2: Network Security
class NetworkSecurity {
public:
    // TLS 1.3 with certificate pinning
    bool setupSecureConnection(const char* host);

    // Certificate validation
    bool validateCertificate(const char* cert);

    // Mutual TLS authentication
    bool authenticateDevice();
};

// Layer 3: Data Security
class DataSecurity {
public:
    // AES-256-GCM encryption
    bool encryptData(const uint8_t* input, uint8_t* output, size_t len);

    // Secure key derivation (PBKDF2)
    void deriveKey(const char* password, uint8_t* key);

    // Secure random number generation
    void getRandomBytes(uint8_t* buffer, size_t len);
};

// Layer 4: Application Security
class ApplicationSecurity {
public:
    // Input validation
    bool validateInput(const String& input);

    // SQL injection prevention (for backend)
    String sanitizeQuery(const String& query);

    // XSS prevention
    String escapeHTML(const String& html);
};
```

### 2.2 Secure Coding Practices

#### Input Validation

```cpp
class InputValidator {
public:
    /**
     * @brief Validate WiFi SSID
     * @param ssid SSID to validate
     * @return true if valid, false otherwise
     */
    static bool validateSSID(const String& ssid) {
        // Length check
        if (ssid.length() == 0 || ssid.length() > 32) {
            return false;
        }

        // Character validation (printable ASCII only)
        for (size_t i = 0; i < ssid.length(); i++) {
            if (ssid[i] < 32 || ssid[i] > 126) {
                return false;
            }
        }

        return true;
    }

    /**
     * @brief Validate API key format
     */
    static bool validateAPIKey(const String& key) {
        // OpenAI key format: sk-[48 alphanumeric chars]
        if (!key.startsWith("sk-")) return false;
        if (key.length() != 51) return false;

        // Validate characters
        for (size_t i = 3; i < key.length(); i++) {
            char c = key[i];
            if (!isalnum(c)) return false;
        }

        return true;
    }

    /**
     * @brief Validate GPS coordinates
     */
    static bool validateCoordinates(double lat, double lng) {
        return (lat >= -90.0 && lat <= 90.0 &&
                lng >= -180.0 && lng <= 180.0);
    }
};
```

#### Buffer Overflow Prevention

```cpp
class SafeString {
public:
    /**
     * @brief Safe string copy with bounds checking
     */
    static void safeCopy(char* dest, const char* src, size_t destSize) {
        if (destSize == 0) return;

        size_t i;
        for (i = 0; i < destSize - 1 && src[i] != '\0'; i++) {
            dest[i] = src[i];
        }
        dest[i] = '\0';  // Always null-terminate
    }

    /**
     * @brief Safe string concatenation
     */
    static void safeConcat(char* dest, const char* src, size_t destSize) {
        size_t destLen = strnlen(dest, destSize);
        if (destLen >= destSize - 1) return;  // No space

        safeCopy(dest + destLen, src, destSize - destLen);
    }
};
```

#### Secure API Communication

```cpp
class SecureAPIClient {
private:
    WiFiClientSecure _client;
    const char* _caCert;  // Certificate for pinning

public:
    bool begin(const char* caCert) {
        _caCert = caCert;

        // Set certificate for validation
        _client.setCACert(_caCert);

        // Disable insecure connections
        _client.setInsecure(false);

        return true;
    }

    /**
     * @brief Make secure API request
     */
    int makeRequest(const char* host, const char* endpoint,
                    const char* apiKey, const String& payload) {
        // Validate inputs
        if (!InputValidator::validateAPIKey(apiKey)) {
            Logger::error("Invalid API key format");
            return -1;
        }

        // Connect with TLS
        if (!_client.connect(host, 443)) {
            Logger::error("TLS connection failed");
            return -1;
        }

        // Verify certificate
        if (!_client.verify(_caCert, host)) {
            Logger::error("Certificate verification failed");
            _client.stop();
            return -1;
        }

        // Build request with proper headers
        String request = "POST " + String(endpoint) + " HTTP/1.1\r\n";
        request += "Host: " + String(host) + "\r\n";
        request += "Authorization: Bearer " + String(apiKey) + "\r\n";
        request += "Content-Type: application/json\r\n";
        request += "Content-Length: " + String(payload.length()) + "\r\n";
        request += "Connection: close\r\n\r\n";
        request += payload;

        // Send request
        _client.print(request);

        // Read response
        // ... (implementation)

        return 200;  // HTTP status code
    }
};
```

### 2.3 Secrets Management

```cpp
/**
 * @brief Secure storage for sensitive data
 *
 * Uses ESP32 NVS (Non-Volatile Storage) with encryption
 */
class SecretsManager {
private:
    static const char* NAMESPACE;
    Preferences _prefs;

public:
    bool begin() {
        return _prefs.begin(NAMESPACE, false);  // Read-write mode
    }

    /**
     * @brief Store API key securely
     */
    bool storeAPIKey(const char* key) {
        if (!InputValidator::validateAPIKey(key)) {
            return false;
        }

        // Encrypt before storing
        uint8_t encrypted[64];
        size_t encLen = encryptData((uint8_t*)key, encrypted, strlen(key));

        return _prefs.putBytes("api_key", encrypted, encLen) == encLen;
    }

    /**
     * @brief Retrieve API key
     */
    String getAPIKey() {
        uint8_t encrypted[64];
        size_t len = _prefs.getBytes("api_key", encrypted, sizeof(encrypted));

        if (len == 0) return "";

        // Decrypt
        uint8_t decrypted[64];
        decryptData(encrypted, decrypted, len);

        return String((char*)decrypted);
    }

private:
    size_t encryptData(const uint8_t* input, uint8_t* output, size_t len);
    size_t decryptData(const uint8_t* input, uint8_t* output, size_t len);
};
```

---

## 🧪 SECTION 3: TESTING STANDARDS

### 3.1 Testing Strategy

```
┌─────────────────────────────────────────────────────────┐
│                  TESTING PYRAMID                         │
├─────────────────────────────────────────────────────────┤
│                                                          │
│                    ┌──────────┐                         │
│                    │   E2E    │  5% - Full system       │
│                    │  Tests   │                         │
│                    └──────────┘                         │
│                ┌────────────────┐                       │
│                │  Integration   │  15% - Module         │
│                │     Tests      │       interaction     │
│                └────────────────┘                       │
│            ┌────────────────────────┐                   │
│            │     Unit Tests         │  80% - Individual │
│            │                        │       functions   │
│            └────────────────────────┘                   │
│                                                          │
└─────────────────────────────────────────────────────────┘
```

### 3.2 Unit Testing Framework

```cpp
// test/unit/test_gps_tracker.cpp
#include <unity.h>
#include "gps_tracker.h"
#include "mocks/mock_serial.h"

// Test fixture
GPSTracker* gps;
MockSerial* mockSerial;

void setUp() {
    gps = new GPSTracker();
    mockSerial = new MockSerial();
}

void tearDown() {
    delete gps;
    delete mockSerial;
}

// Test cases
void test_gps_initialization() {
    bool result = gps->begin(16, 17);
    TEST_ASSERT_TRUE(result);
}

void test_gps_valid_coordinates() {
    // Inject mock GPS data
    mockSerial->inject("$GPGGA,123519,3723.2475,N,12158.3416,W,1,08,0.9,545.4,M,46.9,M,,*47");

    gps->update();

    TEST_ASSERT_TRUE(gps->isValid());
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 37.387458, gps->getLatitude());
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -121.972360, gps->getLongitude());
}

void test_gps_invalid_data() {
    mockSerial->inject("INVALID_DATA");

    gps->update();

    TEST_ASSERT_FALSE(gps->isValid());
}

void test_gps_distance_calculation() {
    double lat1 = 37.7749;
    double lon1 = -122.4194;
    double lat2 = 37.7849;
    double lon2 = -122.4094;

    float distance = gps->distanceBetween(lat1, lon1, lat2, lon2);

    // Should be approximately 1.4 km
    TEST_ASSERT_FLOAT_WITHIN(100.0, 1400.0, distance);
}

void test_gps_geofence() {
    gps->setGeofence(37.7749, -122.4194, 1000);  // 1km radius

    // Inside geofence
    TEST_ASSERT_TRUE(gps->isWithinGeofence(37.7750, -122.4195));

    // Outside geofence
    TEST_ASSERT_FALSE(gps->isWithinGeofence(37.8000, -122.4000));
}

// Test runner
int main() {
    UNITY_BEGIN();

    RUN_TEST(test_gps_initialization);
    RUN_TEST(test_gps_valid_coordinates);
    RUN_TEST(test_gps_invalid_data);
    RUN_TEST(test_gps_distance_calculation);
    RUN_TEST(test_gps_geofence);

    return UNITY_END();
}
```

### 3.3 Integration Testing

```cpp
// test/integration/test_sos_system.cpp
#include <unity.h>
#include "sos_system.h"
#include "gps_tracker.h"
#include "network_manager.h"

void test_sos_end_to_end() {
    // Setup
    SOSSystem sos;
    GPSTracker gps;
    NetworkManager network;

    sos.begin();
    gps.begin(16, 17);
    network.connect("TestWiFi", "password");

    // Simulate GPS lock
    gps.setMockLocation(37.7749, -122.4194);

    // Trigger SOS
    bool triggered = sos.trigger(
        gps.getLatitude(),
        gps.getLongitude(),
        gps.isValid(),
        85  // battery %
    );

    // Verify
    TEST_ASSERT_TRUE(triggered);
    TEST_ASSERT_TRUE(sos.wasAlertSent());
    TEST_ASSERT_EQUAL(200, sos.getLastHTTPCode());
}
```

### 3.4 Performance Testing

```cpp
// test/performance/test_battery_life.cpp
void test_power_consumption() {
    PowerManager power;
    power.begin();

    // Measure idle power
    unsigned long start = millis();
    float idlePower = power.measureCurrent();

    // Should be < 50mA in idle
    TEST_ASSERT_LESS_THAN(50.0, idlePower);

    // Measure active power (GPS + WiFi)
    gps.wake();
    WiFi.begin();
    float activePower = power.measureCurrent();

    // Should be < 300mA active
    TEST_ASSERT_LESS_THAN(300.0, activePower);
}

void test_response_time() {
    VoiceProcessor voice;

    unsigned long start = micros();
    voice.recordAudio();
    unsigned long recordTime = micros() - start;

    // Recording should complete in < 5.1 seconds
    TEST_ASSERT_LESS_THAN(5100000, recordTime);
}
```

### 3.5 Test Coverage Requirements

```
┌─────────────────────────────────────────────────────────┐
│              MINIMUM CODE COVERAGE                       │
├─────────────────────────────────────────────────────────┤
│ Core System Modules:        95% coverage required       │
│ Safety Features:            100% coverage required       │
│ Network/Security:           90% coverage required        │
│ Feature Modules:            80% coverage required        │
│ UI/Display:                 70% coverage required        │
│                                                          │
│ Overall Project:            85% coverage minimum         │
└─────────────────────────────────────────────────────────┘
```

---

## 🔄 SECTION 4: CI/CD & DEVOPS

### 4.1 Continuous Integration Pipeline

```yaml
# .github/workflows/ci.yml
name: VOLT CI Pipeline

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]

jobs:
  # Job 1: Code Quality
  code-quality:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3

      - name: Run Linter
        run: |
          pip install cpplint
          cpplint --recursive firmware/src/

      - name: Check Code Formatting
        run: |
          clang-format --dry-run --Werror firmware/src/**/*.cpp

      - name: Static Analysis
        run: |
          cppcheck --enable=all --error-exitcode=1 firmware/src/

  # Job 2: Unit Tests
  unit-tests:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3

      - name: Setup PlatformIO
        run: |
          pip install platformio

      - name: Run Unit Tests
        run: |
          cd firmware
          pio test -e native

      - name: Generate Coverage Report
        run: |
          pio test -e native --coverage
          lcov --capture --directory . --output-file coverage.info

      - name: Upload Coverage
        uses: codecov/codecov-action@v3
        with:
          files: ./coverage.info
          fail_ci_if_error: true
          flags: unittests

  # Job 3: Integration Tests
  integration-tests:
    runs-on: ubuntu-latest
    needs: unit-tests
    steps:
      - uses: actions/checkout@v3

      - name: Run Integration Tests
        run: |
          cd firmware
          pio test -e esp32s3

  # Job 4: Security Scan
  security-scan:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3

      - name: Run Security Scan
        uses: aquasecurity/trivy-action@master
        with:
          scan-type: "fs"
          scan-ref: "."
          severity: "CRITICAL,HIGH"

      - name: Dependency Check
        run: |
          pip install safety
          safety check --json

  # Job 5: Build Firmware
  build:
    runs-on: ubuntu-latest
    needs: [code-quality, unit-tests, security-scan]
    steps:
      - uses: actions/checkout@v3

      - name: Build Firmware
        run: |
          cd firmware
          pio run -e esp32s3

      - name: Upload Artifacts
        uses: actions/upload-artifact@v3
        with:
          name: firmware
          path: firmware/.pio/build/esp32s3/firmware.bin
```

### 4.2 Continuous Deployment

```yaml
# .github/workflows/cd.yml
name: VOLT CD Pipeline

on:
  release:
    types: [published]

jobs:
  deploy-firmware:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3

      - name: Build Production Firmware
        run: |
          cd firmware
          pio run -e esp32s3 --target release

      - name: Sign Firmware
        run: |
          openssl dgst -sha256 -sign private_key.pem \
            -out firmware.sig firmware.bin

      - name: Upload to OTA Server
        run: |
          aws s3 cp firmware.bin s3://volt-ota/firmware/${{ github.ref_name }}/
          aws s3 cp firmware.sig s3://volt-ota/firmware/${{ github.ref_name }}/

      - name: Update Version Manifest
        run: |
          echo "${{ github.ref_name }}" > version.txt
          aws s3 cp version.txt s3://volt-ota/latest_version
```
