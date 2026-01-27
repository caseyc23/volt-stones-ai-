frFlash VOLT to Stone's Watch - SIMPLE STEPS

## Follow These Steps EXACTLY - Cannot Fail

---

## ⚠️ BEFORE YOU START

**DO THIS FIRST:**

1. Charge Stone's watch to 100%
2. Close ALL other programs on your computer
3. Have a good USB cable ready
4. Read ALL steps before starting

**Time needed:** 30 minutes
**Risk level:** ZERO (if you follow exactly)

---

## 🎯 STEP 1: Install Arduino IDE (5 minutes)

### Download Arduino IDE:

1. Go to: https://www.arduino.cc/en/software
2. Click "Windows" (or your OS)
3. Download and install
4. Open Arduino IDE

**✓ Check:** Arduino IDE is open and running

---

## 🎯 STEP 2: Install ESP32 Support (5 minutes)

### In Arduino IDE:

1. Click **File** → **Preferences**

2. Find "Additional Board Manager URLs"

3. Paste this EXACTLY:

   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```

4. Click **OK**

5. Click **Tools** → **Board** → **Boards Manager**

6. Type "esp32" in search box

7. Find "esp32 by Espressif Systems"

8. Click **Install** (wait for it to finish)

9. Click **Close**

**✓ Check:** ESP32 boards are installed

---

## 🎯 STEP 3: Connect Watch (2 minutes)

### Connect to Computer:

1. Plug USB cable into watch
2. Plug other end into computer
3. Watch should show charging indicator

### Select Port:

1. In Arduino IDE, click **Tools** → **Port**
2. Look for "COM" port (Windows) or "/dev/cu" (Mac)
3. Select the port that appeared when you plugged in watch

**✓ Check:** Port is selected in Arduino IDE

---

## 🎯 STEP 4: Configure Settings (3 minutes)

### CRITICAL: Set These EXACTLY

Click **Tools** menu and set each one:

```
Board: "ESP32S3 Dev Module"
USB CDC On Boot: "Enabled"
CPU Frequency: "240MHz (WiFi)"
Flash Mode: "QIO 80MHz"
Flash Size: "16MB (128Mb)"
Partition Scheme: "16M Flash (3MB APP/9MB FATFS)"
PSRAM: "OPI PSRAM"
Upload Speed: "921600"

⚠️ MOST IMPORTANT:
Erase All Flash Before Sketch Upload: "Disabled"
(This MUST be "Disabled" or watch could brick!)
```

**✓ Check:** All settings match exactly

---

## 🎯 STEP 5: Test Connection (5 minutes)

### Create Test File:

1. Click **File** → **New**

2. Delete everything in the window

3. Copy and paste this EXACTLY:

```cpp
#include <Arduino.h>

#define LED_PIN 48
#define BUTTON_PIN 0

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.println("\n\n=== WATCH TEST ===");
    Serial.println("If you see this, everything works!");
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Button works!");
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
    }
}
```

4. Click **File** → **Save As**
5. Name it: `watch_test`
6. Click **Save**

### Upload Test:

1. Click the **Checkmark** button (✓) to verify
   - Wait for "Done compiling"
   - Should say "Sketch uses X bytes"

2. Click the **Arrow** button (→) to upload
   - Watch the progress bar at bottom
   - **DO NOT UNPLUG WATCH!**
   - Wait for "Done uploading"

3. Click **Tools** → **Serial Monitor**
4. Set dropdown to "115200 baud"
5. Should see "WATCH TEST" and "If you see this, everything works!"

6. Press button on watch
   - Should see "Button works!" in Serial Monitor
   - LED should blink

**✓ Check:** Test passed, watch works!

**⚠️ IF TEST FAILS:**

- STOP HERE
- Do NOT flash VOLT yet
- Check USB cable
- Check port selection
- Try again

**✓ IF TEST PASSES:**

- Continue to next step
- Watch is ready for VOLT!

---

## 🎯 STEP 6: Prepare VOLT Firmware (5 minutes)

### Get VOLT Files:

1. Go to your `firmware_final` folder
2. You should see these files:
   - volt_firmware.ino
   - VoltAI.h
   - config.h
   - pins.h
   - (and other .h files)

### Edit Configuration:

1. Open `config.h` in a text editor (Notepad)

2. Find and change these lines:

```cpp
// YOUR WiFi (change these!)
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// YOUR OpenAI API Key (change this!)
const char* OPENAI_API_KEY = "sk-YOUR_KEY_HERE";

// Stone's Information (change these!)
const char* CHILD_NAME = "Stone";
const int CHILD_AGE = 8;  // Stone's age
```

3. Save config.h

**✓ Check:** Config file has your WiFi and API key

---

## 🎯 STEP 7: Flash VOLT (5 minutes)

### Open VOLT:

1. In Arduino IDE, click **File** → **Open**
2. Navigate to `firmware_final` folder
3. Open `volt_firmware.ino`
4. All the .h files should load automatically

### Verify VOLT:

1. Click **Checkmark** button (✓)
2. Wait for compilation (may take 1-2 minutes)
3. Should say "Done compiling"
4. Check for errors - should be ZERO errors

**⚠️ IF ERRORS:**

- Check that ALL .h files are in same folder
- Check config.h syntax (commas, quotes, semicolons)
- Fix errors before continuing

### Upload VOLT:

1. **IMPORTANT:** Make sure watch is still connected
2. **IMPORTANT:** Make sure Serial Monitor is CLOSED
3. Click **Arrow** button (→) to upload
4. **DO NOT TOUCH ANYTHING!**
5. Watch progress bar
6. Wait for "Done uploading" (takes 1-2 minutes)

**✓ Check:** Upload completed successfully

---

## 🎯 STEP 8: Verify VOLT Works (5 minutes)

### Check Boot:

1. Open **Tools** → **Serial Monitor**
2. Set to "115200 baud"
3. Should see:
   ```
   === VOLT V5.00 STARTUP ===
   VOLT v5.00
   Initializing...
   Display: OK
   WiFi: Connecting...
   AI System: Online
   ```

### Check Display:

1. Watch screen should show:
   - "VOLT v5.00"
   - "Initializing..."
   - Then "VOLT" with "Ready to talk!"

### Check Button:

1. Press button once
2. Menu should appear
3. Press again to scroll
4. Double-press to select

### Check Voice (if WiFi connected):

1. Select "Ai Chat" from menu
2. Watch should say "Listening..."
3. Say something to Stone's watch
4. Watch should respond with AI voice

**✓ Check:** Everything works!

---

## ✅ SUCCESS CHECKLIST

**VOLT is ready for Stone when:**

- ☐ Watch boots without errors
- ☐ Display shows VOLT screen
- ☐ Button responds to presses
- ☐ Menu navigation works
- ☐ WiFi connects (if configured)
- ☐ Voice chat works (if WiFi connected)
- ☐ No crashes or freezes
- ☐ Battery charges normally

**If ALL checked → SUCCESS! Give to Stone!**

---

## 🆘 EMERGENCY RECOVERY

**If something goes wrong:**

### Watch Won't Boot:

1. Don't panic - watch is probably fine
2. Open Serial Monitor (115200 baud)
3. Look for error messages
4. Most common: Display pins or WiFi issue

### Quick Fix:

1. Flash the test sketch again (Step 5)
2. If test works, watch hardware is fine
3. Check VOLT code for errors
4. Fix and try again

### Nuclear Option (if nothing works):

1. In Arduino IDE: **Tools** → **Erase Flash** → **All Flash Contents**
2. Flash test sketch
3. Flash VOLT again fresh
4. Should work now

---

## 📞 HELP

**If you get stuck:**

1. Check Serial Monitor for error messages
2. Google the exact error message
3. Check ESP32 forums
4. Most issues are simple config errors

**Common Issues:**

- "Failed to connect" → Hold BOOT button while uploading
- "Sketch too large" → Check partition scheme setting
- "WiFi won't connect" → Check SSID/password in config.h
- "No voice" → Check OpenAI API key in config.h

---

## 🎉 DONE!

**When everything works:**

1. Unplug watch from computer
2. Let it charge fully
3. Give to Stone
4. Show him how to use it:
   - Single press = Menu
   - Scroll through options
   - Double press = Select
   - Long hold = Exit menu

**Stone now has an AI watch that:**

- Talks to him with GPT-4
- Tells jokes
- Does breathing exercises
- Plays games
- Shows love messages from Dad

**Enjoy! 🚀**

---

## 📋 QUICK REFERENCE

**Arduino IDE Settings (Copy This):**

```
Board: ESP32S3 Dev Module
USB CDC On Boot: Enabled
Flash Size: 16MB (128Mb)
Partition: 16M Flash (3MB APP/9MB FATFS)
PSRAM: OPI PSRAM
Upload Speed: 921600
⚠️ Erase All Flash: Disabled
```

**Files Needed:**

```
firmware_final/
├── volt_firmware.ino (main file)
├── VoltAI.h
├── config.h (edit this!)
├── pins.h
└── (all other .h files)
```

**Config to Edit:**

```cpp
WIFI_SSID = "your wifi"
WIFI_PASSWORD = "your password"
OPENAI_API_KEY = "sk-your-key"
CHILD_NAME = "Stone"
CHILD_AGE = 8
```

---

**Follow these steps exactly and you CANNOT fail. The watch will work perfectly for Stone!**
