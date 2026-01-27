# VOLT for HU-087 - Safe Flashing Guide

## Flash VOLT to Stone's Watch Without Risk

---

## ⚠️ SAFETY FIRST - Read This!

**Before flashing anything:**

1. ✅ Backup current firmware (if possible)
2. ✅ Charge watch to 100%
3. ✅ Have USB cable ready
4. ✅ Close all other programs
5. ✅ Read this guide completely first

**What could go wrong (and how we prevent it):**

- ❌ Wrong board selected → We'll verify settings
- ❌ Wrong pins configured → We'll use HU-087 specific config
- ❌ Bricked device → We'll use safe flash settings
- ❌ Lost features → We'll test before full flash

---

## 🎯 Three-Window System for Safe Flashing

### Window 1: Arduino IDE (Flashing)

### Window 2: Serial Monitor (Debugging)

### Window 3: This Guide (Reference)

**Setup:**

```
┌─────────────────────────────────────────────────────────┐
│  Screen Layout:                                          │
│  ┌──────────────┬──────────────┬──────────────┐        │
│  │   Arduino    │    Serial    │     This     │        │
│  │     IDE      │   Monitor    │    Guide     │        │
│  │  (Flashing)  │ (Debugging)  │ (Reference)  │        │
│  └──────────────┴──────────────┴──────────────┘        │
└─────────────────────────────────────────────────────────┘
```

---

## 📋 Pre-Flight Checklist

### Step 1: Verify Hardware

**Check your HU-087 watch:**

```
Physical Inspection:
☐ Watch powers on
☐ Display shows something
☐ Button responds
☐ USB port not damaged
☐ Battery charged >50%
☐ No physical damage

Current Firmware Check:
☐ Note current version
☐ Test all current features
☐ Take photos/videos of working state
☐ Document any custom settings
```

### Step 2: Prepare Computer

**Install Required Software:**

```
1. Arduino IDE 2.x
   Download: https://www.arduino.cc/en/software
   ☐ Installed
   ☐ Opened successfully

2. ESP32 Board Support
   In Arduino IDE:
   File → Preferences → Additional Board Manager URLs
   Add: https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ☐ Added
   ☐ ESP32 boards installed

3. USB Drivers (if needed)
   - Windows: CH340 or CP2102 drivers
   - Mac: Usually automatic
   - Linux: Usually automatic
   ☐ Drivers installed
   ☐ Device recognized
```

### Step 3: Test Connection

**Before flashing, verify connection:**

```
1. Connect watch to computer via USB
   ☐ Watch shows charging indicator
   ☐ Computer recognizes device
   ☐ COM port appears in Arduino IDE

2. Select correct settings:
   Tools → Board → ESP32 Arduino → ESP32S3 Dev Module
   ☐ Board selected

   Tools → Port → [Your COM port]
   ☐ Port selected

3. Test connection:
   Tools → Get Board Info
   ☐ Board info displayed
   ☐ No errors
```

---

## 🔧 Arduino IDE Settings for HU-087

### CRITICAL: Use These Exact Settings

```
Board Settings (Tools menu):
┌─────────────────────────────────────────────┐
│ Board: "ESP32S3 Dev Module"                 │
│ USB CDC On Boot: "Enabled"                  │
│ CPU Frequency: "240MHz (WiFi)"              │
│ Core Debug Level: "None"                    │
│ USB DFU On Boot: "Disabled"                 │
│ Erase All Flash: "Disabled" ⚠️ IMPORTANT    │
│ Events Run On: "Core 1"                     │
│ Flash Mode: "QIO 80MHz"                     │
│ Flash Size: "16MB (128Mb)"                  │
│ JTAG Adapter: "Disabled"                    │
│ Arduino Runs On: "Core 1"                   │
│ USB Firmware MSC On Boot: "Disabled"        │
│ Partition Scheme: "16M Flash (3MB APP/9MB FATFS)" │
│ PSRAM: "OPI PSRAM"                          │
│ Upload Mode: "UART0 / Hardware CDC"         │
│ Upload Speed: "921600"                      │
│ USB Mode: "Hardware CDC and JTAG"           │
│ Zigbee Mode: "Disabled"                     │
└─────────────────────────────────────────────┘

⚠️ CRITICAL: "Erase All Flash" MUST be "Disabled"
   (Enabled will wipe everything including bootloader!)
```

---

## 📦 Prepare VOLT Firmware

### Option A: Test Flash (Recommended First)

**Start with minimal test to verify everything works:**

```cpp
// Create: test_hu087.ino
// Minimal test sketch to verify HU-087 works

#include <Arduino.h>

#define LED_PIN 48
#define BUTTON_PIN 0

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.println("\n\n=== HU-087 Test ===");
    Serial.println("If you see this, USB works!");
    Serial.println("Press button to blink LED");
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Button pressed!");
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
    }
}
```

**Flash Test Sketch:**

```
1. Open test_hu087.ino in Arduino IDE
2. Verify settings (see above)
3. Click Upload (→ button)
4. Watch for "Done uploading"
5. Open Serial Monitor (115200 baud)
6. Should see "HU-087 Test"
7. Press button, LED should blink

If this works → Safe to flash VOLT
If this fails → STOP, troubleshoot first
```

### Option B: Full VOLT Flash (After Test Passes)

**Prepare VOLT firmware:**

```
1. Copy firmware_final folder to Arduino folder
2. Rename to: VOLT_HU087
3. Open VOLT_HU087.ino
4. Verify all required files present:
   ☐ volt_firmware.ino
   ☐ VoltAI.h
   ☐ config.h
   ☐ pins.h (HU-087 specific)
   ☐ All other .h files
```

---

## 🚀 Safe Flashing Procedure

### Phase 1: Backup (If Possible)

```
If watch has working firmware:
1. Try to read current firmware:
   Tools → ESP32 Sketch Data Upload
   (May not work, but worth trying)

2. Document current state:
   - Take photos of all screens
   - Note all settings
   - Test all features
   - Record any custom data
```

### Phase 2: Test Flash

```
Window 1 (Arduino IDE):
1. Open test_hu087.ino
2. Verify board settings
3. Click Verify (✓) first
   ☐ Compiles without errors
4. Click Upload (→)
   ☐ Watch progress bar
   ☐ Wait for "Done uploading"

Window 2 (Serial Monitor):
1. Open Serial Monitor
2. Set baud rate: 115200
3. Should see test messages
4. Press button, verify LED blinks

Window 3 (This Guide):
☐ Follow each step
☐ Check off completed items
☐ Note any errors
```

**If test flash succeeds → Continue**
**If test flash fails → STOP, see Troubleshooting**

### Phase 3: VOLT Flash

```
Window 1 (Arduino IDE):
1. Close test sketch
2. Open VOLT_HU087.ino
3. Edit config.h:
   - Add your WiFi credentials
   - Add OpenAI API key
   - Set Stone's name and age
4. Click Verify (✓)
   ☐ Compiles without errors
   ☐ Note: "Sketch uses X bytes"
5. Click Upload (→)
   ☐ Watch progress carefully
   ☐ Don't disconnect during upload!
   ☐ Wait for "Done uploading"

Window 2 (Serial Monitor):
1. Keep Serial Monitor open
2. Watch for boot messages
3. Should see:
   "=== VOLT V5.00 STARTUP ==="
   "Display: OK"
   "WiFi: Connecting..."
   etc.

Window 3 (This Guide):
☐ Monitor progress
☐ Check for errors
☐ Verify each boot message
```

### Phase 4: Verification

```
After upload completes:

1. Watch Display:
   ☐ Shows VOLT boot screen
   ☐ Shows "Initializing..."
   ☐ Shows idle screen
   ☐ No error messages

2. Serial Monitor:
   ☐ Boot sequence completes
   ☐ No error messages
   ☐ WiFi connects (if configured)
   ☐ AI system initializes

3. Button Test:
   ☐ Single press works
   ☐ Menu appears
   ☐ Navigation works
   ☐ Features respond

4. Voice Test:
   ☐ Microphone works
   ☐ Speaker works
   ☐ AI responds
   ☐ Voice quality good
```

---

## 🔍 Troubleshooting

### Problem: Upload Fails

**Error: "Failed to connect"**

```
Solutions:
1. Hold BOOT button (GPIO 0) while clicking Upload
2. Release after "Connecting..." appears
3. Try lower upload speed (115200)
4. Try different USB cable
5. Try different USB port
6. Restart Arduino IDE
```

**Error: "Timed out waiting for packet header"**

```
Solutions:
1. Watch might be in deep sleep
2. Press and hold BOOT button
3. Press RESET (if available)
4. Try upload again
5. Disconnect and reconnect USB
```

**Error: "Sketch too large"**

```
Solutions:
1. Check partition scheme
2. Should be "16M Flash (3MB APP/9MB FATFS)"
3. If still too large, disable features in config.h
4. Reduce PSRAM usage
```

### Problem: Upload Succeeds But Watch Doesn't Boot

**Symptoms: Blank screen, no response**

```
Solutions:
1. Don't panic! Watch is probably fine
2. Open Serial Monitor (115200 baud)
3. Press RESET button
4. Check for error messages
5. Common issues:
   - Display pins wrong → Check pins.h
   - Missing library → Install required libraries
   - Config error → Check config.h syntax
```

**Recovery:**

```
1. Flash test sketch again
2. If test works, VOLT code has issue
3. Check Serial Monitor for specific error
4. Fix error in code
5. Try VOLT flash again
```

### Problem: Features Don't Work

**WiFi won't connect:**

```
1. Check config.h credentials
2. Verify 2.4GHz network (not 5GHz)
3. Check Serial Monitor for error
4. Try different network
5. Check WiFi antenna (if external)
```

**Voice doesn't work:**

```
1. Check pins.h matches HU-087
2. Verify I2S pins correct
3. Test with simple audio sketch
4. Check microphone/speaker connections
5. Verify OpenAI API key
```

**Display issues:**

```
1. Verify TFT_eSPI library installed
2. Check User_Setup.h in library
3. Verify pins match HU-087
4. Try different rotation setting
5. Check display power
```

---

## 📊 Post-Flash Checklist

### Immediate Tests (First 5 Minutes):

```
Basic Functionality:
☐ Watch boots successfully
☐ Display shows correctly
☐ Button responds
☐ LED works
☐ Serial output normal

Core Features:
☐ WiFi connects
☐ Display updates
☐ Menu navigation works
☐ Settings accessible
☐ No crashes

Audio System:
☐ Microphone picks up sound
☐ Speaker plays sound
☐ Voice chat works
☐ AI responds
☐ Audio quality good
```

### Extended Tests (First Hour):

```
Stability:
☐ No random reboots
☐ No freezes
☐ Memory stable
☐ Temperature normal
☐ Battery charging

Features:
☐ All menu items work
☐ Voice recognition accurate
☐ AI responses appropriate
☐ Breathing exercise works
☐ Jokes work
☐ Love messages work

Power:
☐ Deep sleep works
☐ Wake from sleep works
☐ Battery percentage accurate
☐ Charging indicator works
☐ Power consumption reasonable
```

### Long-Term Tests (First Week):

```
Reliability:
☐ 24-hour continuous operation
☐ Multiple charge cycles
☐ Daily use by Stone
☐ No degradation
☐ No new issues

Performance:
☐ Response time good
☐ Battery life acceptable
☐ WiFi stable
☐ AI quality consistent
☐ No memory leaks
```

---

## 🎯 Success Criteria

**Flash is successful when:**

1. ✅ Watch boots without errors
2. ✅ All features work as expected
3. ✅ No crashes or freezes
4. ✅ Battery life normal
5. ✅ Stone can use it happily
6. ✅ No regression from previous version
7. ✅ Ready for daily use

---

## 🔄 Rollback Plan

**If something goes wrong:**

### Option 1: Reflash Previous Version

```
1. Flash test sketch first (verify hardware OK)
2. Flash previous working firmware
3. Verify everything works
4. Debug VOLT issue offline
5. Try VOLT flash again when fixed
```

### Option 2: Factory Reset

```
1. In Arduino IDE:
   Tools → Erase Flash → "All Flash Contents"
2. Flash test sketch
3. Flash VOLT fresh
4. Reconfigure from scratch
```

### Option 3: Professional Help

```
If nothing works:
1. Don't force it
2. Watch hardware is probably fine
3. Issue is likely software
4. Seek help on ESP32 forums
5. Provide Serial Monitor output
```

---

## 📝 Flashing Log Template

**Keep track of your flash:**

```
Date: _______________
Time: _______________

Pre-Flash State:
- Current firmware: _______________
- Working features: _______________
- Issues: _______________

Flash Attempt:
- VOLT version: _______________
- Arduino IDE version: _______________
- Board settings: _______________
- Upload speed: _______________
- Result: ☐ Success ☐ Failed

Post-Flash State:
- Boot successful: ☐ Yes ☐ No
- Features working: _______________
- New issues: _______________
- Notes: _______________

Next Steps:
_______________
_______________
```

---

## 🎓 Best Practices

### Before Every Flash:

1. ✅ Charge watch fully
2. ✅ Close other programs
3. ✅ Verify settings
4. ✅ Test compile first
5. ✅ Have rollback plan

### During Flash:

1. ✅ Don't disconnect USB
2. ✅ Don't close Arduino IDE
3. ✅ Watch Serial Monitor
4. ✅ Note any errors
5. ✅ Be patient

### After Flash:

1. ✅ Test immediately
2. ✅ Monitor for issues
3. ✅ Document problems
4. ✅ Test with Stone
5. ✅ Keep notes

---

## 🚀 Ready to Flash?

**Final Checklist:**

```
Preparation:
☐ Read this entire guide
☐ Watch charged >50%
☐ USB cable connected
☐ Arduino IDE configured
☐ Board settings verified
☐ Test sketch ready
☐ VOLT firmware prepared
☐ Config.h edited
☐ Three windows open
☐ Rollback plan ready

Mental Preparation:
☐ Not rushed
☐ Focused
☐ Patient
☐ Ready to troubleshoot
☐ Confident

GO/NO-GO Decision:
☐ All checks passed → GO
☐ Any concerns → NO-GO (address first)
```

---

**When ready, start with test flash, then proceed to VOLT flash. Take your time, follow each step, and Stone will have an amazing AI watch!**

**Good luck! 🚀**
