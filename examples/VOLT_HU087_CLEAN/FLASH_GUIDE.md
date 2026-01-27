# Flash VOLT to Stone's HU-087 Watch

## Simple, Safe, Step-by-Step Guide

---

## 🎯 What You Need

1. **Stone's HU-087 watch** (charged to 100%)
2. **USB cable** (good quality)
3. **Computer** with Arduino IDE
4. **WiFi credentials**
5. **OpenAI API key**
6. **30 minutes** of focused time

---

## 📋 Step 1: Install Arduino IDE

1. Download from: https://www.arduino.cc/en/software
2. Install and open Arduino IDE
3. Go to **File → Preferences**
4. In "Additional Board Manager URLs", paste:
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
5. Click **OK**
6. Go to **Tools → Board → Boards Manager**
7. Search for "esp32"
8. Install "esp32 by Espressif Systems"
9. Wait for installation to complete

---

## 📋 Step 2: Install Required Libraries

1. Go to **Tools → Manage Libraries**
2. Search and install each:
   - **TFT_eSPI** (for ST7789 display)
   - **ArduinoJson** (for API communication)
3. Close Library Manager

### Configure TFT_eSPI for HU-087:

1. Find TFT_eSPI library folder:
   - Windows: `Documents\Arduino\libraries\TFT_eSPI`
   - Mac: `~/Documents/Arduino/libraries/TFT_eSPI`
2. Open `User_Setup_Select.h`

3. Comment out the default setup (add // at start):

   ```cpp
   // #include <User_Setup.h>
   ```

4. Add this line:

   ```cpp
   #include <User_Setups/Setup25_TTGO_T_Display.h>
   ```

5. Save and close

---

## 📋 Step 3: Configure for Stone

1. Open `VOLT_HU087_CLEAN` folder
2. Open `config_stone.h` in a text editor
3. Edit these values:

```cpp
// Stone's WiFi
const char* WIFI_SSID = "YourWiFiName";
const char* WIFI_PASSWORD = "YourWiFiPassword";

// OpenAI API Key
const char* OPENAI_API_KEY = "sk-your-actual-key-here";

// Stone's info (already set, but verify)
const char* CHILD_NAME = "Stone";
const int CHILD_AGE = 8;
```

4. Save `config_stone.h`

---

## 📋 Step 4: Connect Watch

1. Plug USB cable into watch
2. Plug other end into computer
3. Watch should show charging indicator

---

## 📋 Step 5: Configure Arduino IDE

### Board Settings (CRITICAL - Must be exact):

1. **Tools → Board → ESP32 Arduino → ESP32S3 Dev Module**

2. Set these EXACTLY:

   ```
   USB CDC On Boot: "Enabled"
   CPU Frequency: "240MHz (WiFi)"
   Flash Mode: "QIO 80MHz"
   Flash Size: "16MB (128Mb)"
   Partition Scheme: "16M Flash (3MB APP/9MB FATFS)"
   PSRAM: "OPI PSRAM"
   Upload Speed: "921600"
   USB Mode: "Hardware CDC and JTAG"

   ⚠️ CRITICAL:
   Erase All Flash Before Sketch Upload: "Disabled"
   ```

3. **Tools → Port → [Select your COM port]**
   - Windows: COM3, COM4, etc.
   - Mac: /dev/cu.usbserial-xxx
   - Linux: /dev/ttyUSB0, etc.

---

## 📋 Step 6: Test Connection

1. Open `volt_stone.ino` in Arduino IDE
2. Click **Verify** button (✓)
3. Wait for compilation
4. Should say "Done compiling" with no errors

**If errors:**

- Check all libraries installed
- Check TFT_eSPI configured
- Check all files in same folder

---

## 📋 Step 7: Flash to Watch

1. Make sure watch is connected
2. Click **Upload** button (→)
3. **DO NOT DISCONNECT WATCH!**
4. Watch progress bar at bottom
5. May take 2-3 minutes
6. Should say "Done uploading"

**If upload fails:**

- Hold BOOT button while clicking Upload
- Release after "Connecting..." appears
- Try again

---

## 📋 Step 8: Verify It Works

1. Open **Tools → Serial Monitor**
2. Set baud rate to **115200**
3. Should see:

   ```
   === VOLT for Stone - Starting ===
   Power: Initialized
   WiFi: Connecting...
   WiFi: Connected!
   AI: Initialized successfully
   === VOLT Ready for Stone ===
   ```

4. Watch display should show:
   - "VOLT" in large text
   - "Ready to talk!" or "Offline mode"
   - Battery percentage

5. Press button once
   - Should show "Listening..."
   - LED should light up

**SUCCESS!** VOLT is ready for Stone!

---

## 🎮 How Stone Uses It

### Button Patterns:

**1 Press** → Talk to VOLT

- Say: "Hi VOLT, I need help"
- VOLT listens, thinks, and responds

**2 Presses** → Hear a Joke

- VOLT tells an age-appropriate joke
- Makes Stone laugh

**3 Presses** → Breathing Exercise

- Guided breathing for anxiety
- Calms Stone down

**4 Presses (Long Hold)** → Dad's Love Message

- Hear Dad's special message
- Feel connected and loved

**5 Presses** → WiFi Setup

- Configure networks
- Check settings

---

## 🆘 Troubleshooting

### Watch Won't Boot:

1. Check Serial Monitor for errors
2. Verify board settings match exactly
3. Try reflashing

### WiFi Won't Connect:

1. Check SSID and password (case-sensitive)
2. Ensure 2.4GHz network (not 5GHz)
3. Move closer to router

### Voice Doesn't Work:

1. Check OpenAI API key
2. Verify WiFi connected
3. Check Serial Monitor for errors

### Display Issues:

1. Verify TFT_eSPI configured correctly
2. Check User_Setup_Select.h
3. Try different setup file

---

## ✅ Success Checklist

After flashing, verify:

- ☐ Watch boots successfully
- ☐ Display shows VOLT screen
- ☐ WiFi connects
- ☐ Button responds
- ☐ LED blinks on press
- ☐ Serial Monitor shows no errors
- ☐ Voice recording works
- ☐ AI responds
- ☐ Speech plays clearly
- ☐ Battery shows percentage

**All checked?** Give to Stone and enjoy!

---

## 📞 Need Help?

1. Check Serial Monitor output
2. Look for specific error messages
3. Google the exact error
4. Check ESP32 forums
5. Review this guide again

---

**Made with ❤️ by Dad for Stone**
