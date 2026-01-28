# 🚀 VOLT 3-Window Flash System
## Complete Setup Guide with All Links and Requirements

---

# 📋 OVERVIEW - What You'll Do

This guide uses a **3-window system** to make flashing easy:

- **WINDOW 1:** This guide (keep it open for reference)
- **WINDOW 2:** Web browser (download software and get API key)
- **WINDOW 3:** Arduino IDE (flash the firmware)

**Total Time:** 45 minutes
**Difficulty:** Easy (just follow the steps)

---

# ✅ CHECKLIST - What You Need

## Hardware (You Already Have):
- ✅ Stone's HU-087 ESP32-S3 watch
- ✅ USB-C cable (data-capable)
- ✅ Windows computer
- ✅ Internet connection

## Software (We'll Download):
- ⬜ Arduino IDE 2.3.2
- ⬜ ESP32 board support
- ⬜ TFT_eSPI library
- ⬜ ArduinoJson library
- ⬜ CH340 USB drivers (if needed)

## Information (We'll Get):
- ⬜ Your WiFi name (SSID)
- ⬜ Your WiFi password
- ⬜ OpenAI API key

---

# 🌐 WINDOW 2: WEB BROWSER SETUP

## Step 1: Download Arduino IDE

### **Open your web browser and go to:**
```
https://www.arduino.cc/en/software
```

### **What to download:**
1. Look for "Windows Win 10 and newer, 64 bits"
2. Click the **MSI installer** (recommended)
3. File name: `arduino-ide_2.3.2_Windows_64bit.msi`
4. Size: ~150 MB
5. Save to Downloads folder

### **Install Arduino IDE:**
1. Find the downloaded file in Downloads
2. Double-click to run installer
3. Click "Next" → "Next" → "Install"
4. Wait 2-3 minutes
5. Click "Finish"
6. **DON'T OPEN YET** - we'll open it in Step 3

---

## Step 2: Get OpenAI API Key

### **Open a new browser tab and go to:**
```
https://platform.openai.com/api-keys
```

### **If you don't have an account:**
1. Click "Sign up"
2. Create account with email
3. Verify email
4. Add payment method (required for API access)
5. Add $5-10 credit (VOLT uses about $0.10-0.50 per day)

### **Create API Key:**
1. Click "+ Create new secret key"
2. Name it: "VOLT for Stone"
3. Click "Create secret key"
4. **COPY THE KEY IMMEDIATELY** (starts with `sk-proj-`)
5. Save it in Notepad - you'll need it later
6. **IMPORTANT:** You can only see this key once!

### **Example API key format:**
```
sk-proj-abc123def456ghi789jkl012mno345pqr678stu901vwx234yz
```

---

## Step 3: Get Your WiFi Information

### **Find your WiFi name (SSID):**

**Windows 11:**
1. Click WiFi icon in taskbar (bottom right)
2. Look at "Connected" network
3. That's your WiFi name - write it down

**Example:** `MyHomeWiFi` or `NETGEAR-5G`

### **Important WiFi Requirements:**
- ✅ Must be **2.4GHz** network (NOT 5GHz)
- ✅ Most home WiFi has both - look for one WITHOUT "5G" in name
- ✅ If unsure, try both and see which works

### **Get your WiFi password:**
1. Open Settings → Network & Internet → WiFi
2. Click your network name
3. Click "Show password" (requires admin)
4. Write down the password

**OR ask whoever set up your WiFi!**

---

## Step 4: Download USB Drivers (If Needed)

### **Most Windows 11 systems auto-install drivers, but just in case:**

**Go to:**
```
https://sparks.gogo.co.nz/ch340.html
```

**Download:**
1. Click "CH341SER.EXE" download link
2. Save to Downloads
3. Run the installer
4. Click "INSTALL"
5. Restart computer if prompted

**You can also try:**
```
https://www.wch-ic.com/downloads/CH341SER_EXE.html
```

---

# 💻 WINDOW 3: ARDUINO IDE SETUP

## Step 5: Open Arduino IDE

### **Launch Arduino IDE:**
1. Press Windows key
2. Type "Arduino IDE"
3. Click to open
4. Wait for it to fully load (10-20 seconds)
5. You'll see a blank sketch window

---

## Step 6: Install ESP32 Board Support

### **Add ESP32 Board Manager URL:**

1. Click **File** → **Preferences** (or press `Ctrl+Comma`)

2. Find "Additional boards manager URLs" field

3. **Copy and paste this EXACT URL:**
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```

4. Click **OK**

### **Install ESP32 Boards:**

1. Click **Tools** → **Board** → **Boards Manager**

2. In search box, type: `esp32`

3. Find "**esp32 by Espressif Systems**"

4. Click **INSTALL** button

5. **IMPORTANT:** Install version **2.0.11** or newer (latest is fine)

6. Wait 5-10 minutes for download (it's ~250 MB)

7. You'll see progress bar at bottom

8. When done, close Boards Manager

---

## Step 7: Install Required Libraries

### **Install TFT_eSPI (Display Driver):**

1. Click **Tools** → **Manage Libraries** (or press `Ctrl+Shift+I`)

2. In search box, type: `TFT_eSPI`

3. Find "**TFT_eSPI by Bodmer**"

4. Click **INSTALL**

5. Wait for installation (30 seconds)

### **Install ArduinoJson (JSON Parser):**

1. In same Library Manager, search: `ArduinoJson`

2. Find "**ArduinoJson by Benoit Blanchon**"

3. **IMPORTANT:** Install version **6.x.x** (NOT 7.x)

4. Click **INSTALL**

5. Wait for installation (30 seconds)

6. Close Library Manager

---

## Step 8: Configure TFT_eSPI Library

### **CRITICAL STEP - Display won't work without this!**

### **Find TFT_eSPI folder:**

**Windows path:**
```
C:\Users\[YourUsername]\Documents\Arduino\libraries\TFT_eSPI
```

**To find it easily:**
1. Open File Explorer
2. Go to Documents
3. Open Arduino folder
4. Open libraries folder
5. Open TFT_eSPI folder

### **Edit User_Setup_Select.h:**

1. In TFT_eSPI folder, find `User_Setup_Select.h`

2. Right-click → Open with → Notepad

3. Find this line (around line 22):
   ```cpp
   #include <User_Setup.h>
   ```

4. Add `//` at the start to make it:
   ```cpp
   // #include <User_Setup.h>
   ```

5. Scroll down to find (around line 53):
   ```cpp
   //#include <User_Setups/Setup25_TTGO_T_Display.h>
   ```

6. Remove the `//` to make it:
   ```cpp
   #include <User_Setups/Setup25_TTGO_T_Display.h>
   ```

7. **Save the file** (Ctrl+S)

8. Close Notepad

---

## Step 9: Open VOLT Firmware

### **Navigate to VOLT folder:**

1. In Arduino IDE, click **File** → **Open**

2. Navigate to:
   ```
   C:\Users\Holle\Desktop\volt v5.00 flash\examples\examples\VOLT_HU087_CLEAN
   ```

3. Select `volt_stone_FINAL.ino`

4. Click **Open**

5. You'll see multiple tabs open at top:
   - volt_stone_FINAL
   - config_stone_FINAL.h
   - volt_ai_FINAL.h
   - pins_hu087_FINAL.h
   - power_mgmt_FINAL.h
   - wifi_mgmt_FINAL.h

---

## Step 10: Configure WiFi and API Key

### **Edit config_stone_FINAL.h:**

1. Click the **config_stone_FINAL.h** tab

2. Find line 23-24 (WiFi settings):
   ```cpp
   const char* WIFI_SSID = "YOUR_WIFI_NAME";
   const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
   ```

3. Replace with YOUR WiFi info:
   ```cpp
   const char* WIFI_SSID = "MyHomeWiFi";      // Your actual WiFi name
   const char* WIFI_PASSWORD = "MyPassword123"; // Your actual password
   ```

4. Find line 33 (OpenAI API key):
   ```cpp
   const char* OPENAI_API_KEY = "sk-YOUR_OPENAI_KEY_HERE";
   ```

5. Replace with YOUR API key from Step 2:
   ```cpp
   const char* OPENAI_API_KEY = "sk-proj-abc123def456..."; // Your real key
   ```

6. **Save all files** (Ctrl+S or File → Save)

---

## Step 11: Connect the Watch

### **Prepare the watch:**

1. **Charge Stone's watch to 100%** (or at least 50%)

2. **Connect USB-C cable:**
   - Plug into watch
   - Plug into computer USB port
   - Watch should show charging indicator

3. **Check if computer recognizes it:**
   - In Arduino IDE, click **Tools** → **Port**
   - You should see a COM port (e.g., "COM3", "COM5", "COM7")
   - If you see multiple, unplug watch and see which disappears
   - That's your watch's port!

4. **If NO port appears:**
   - Try different USB cable (must be data cable, not charge-only)
   - Try different USB port on computer
   - Install CH340 drivers from Step 4
   - Restart computer

---

## Step 12: Configure Board Settings

### **CRITICAL - These settings MUST be EXACT!**

### **Select Board:**
1. Click **Tools** → **Board** → **ESP32 Arduino** → **ESP32S3 Dev Module**

### **Configure ALL these settings:**

Click **Tools** and set each one:

```
✅ USB CDC On Boot: "Enabled"
✅ CPU Frequency: "240MHz (WiFi)"
✅ Core Debug Level: "None"
✅ Erase All Flash Before Sketch Upload: "Disabled"
✅ Events Run On: "Core 1"
✅ Flash Mode: "QIO 80MHz"
✅ Flash Size: "16MB (128Mb)"
✅ JTAG Adapter: "Disabled"
✅ Arduino Runs On: "Core 1"
✅ Partition Scheme: "16M Flash (3MB APP/9.9MB FATFS)"
✅ PSRAM: "OPI PSRAM"
✅ Upload Mode: "UART0 / Hardware CDC"
✅ Upload Speed: "921600"
✅ USB Mode: "Hardware CDC and JTAG"
✅ Port: [Your COM port from Step 11]
```

### **Double-check these are EXACT:**
- Partition Scheme: **16M Flash (3MB APP/9.9MB FATFS)**
- PSRAM: **OPI PSRAM**
- USB CDC On Boot: **Enabled**

---

## Step 13: Verify Code Compiles

### **Test compilation (don't upload yet):**

1. Click the **✓ (checkmark)** button at top left

2. This compiles without uploading

3. Watch the black console at bottom

4. You'll see:
   ```
   Compiling sketch...
   Compiling libraries...
   Linking...
   ```

5. Should take 1-2 minutes

6. Should end with:
   ```
   Sketch uses XXXXX bytes (XX%) of program storage space.
   Global variables use XXXXX bytes (XX%) of dynamic memory.
   ```

7. **If you see "Done compiling"** → SUCCESS! Go to Step 14

8. **If you see errors:**
   - Check all 6 files are in same folder
   - Check libraries installed (TFT_eSPI, ArduinoJson)
   - Check TFT_eSPI configuration (Step 8)
   - Copy error message and Google it

---

## Step 14: Flash to Watch

### **Upload firmware:**

1. **Make sure watch is connected** (check Tools → Port)

2. Click the **→ (arrow)** button at top left

3. **DO NOT DISCONNECT WATCH!**

4. You'll see in console:
   ```
   Connecting........_____.....
   Chip is ESP32-S3 (revision v0.1)
   Features: WiFi, BLE
   Crystal is 40MHz
   MAC: xx:xx:xx:xx:xx:xx
   Uploading stub...
   Running stub...
   Stub running...
   Changing baud rate to 921600
   Changed.
   Configuring flash size...
   Flash will be erased from 0x00000000 to 0x00003fff...
   Flash will be erased from 0x00008000 to 0x00008fff...
   Flash will be erased from 0x0000e000 to 0x0000ffff...
   Flash will be erased from 0x00010000 to 0x001fffff...
   Compressed 3072 bytes to 146...
   Writing at 0x00000000... (100 %)
   Wrote 3072 bytes (146 compressed) at 0x00000000 in 0.0 seconds...
   ...
   Writing at 0x00010000... (10%)
   Writing at 0x00020000... (20%)
   Writing at 0x00030000... (30%)
   ...
   Writing at 0x001f0000... (100%)
   Wrote 2031616 bytes (1234567 compressed) at 0x00010000 in 25.3 seconds...
   Hash of data verified.
   
   Leaving...
   Hard resetting via RTS pin...
   ```

5. **Total time: 2-3 minutes**

6. Should end with:
   ```
   Hard resetting via RTS pin...
   Done uploading.
   ```

### **If "Connecting..." hangs forever:**

1. **Hold the BOOT button** on the watch (the main button)

2. While holding, click **Upload** (→) again

3. Keep holding until you see "Writing..."

4. Then release the button

5. Upload should continue

### **If still fails:**

1. Try lower upload speed: Tools → Upload Speed → "115200"

2. Try different USB cable

3. Try different USB port

4. Restart Arduino IDE

5. Restart computer

---

## Step 15: Verify It Works

### **Open Serial Monitor:**

1. Click **Tools** → **Serial Monitor**

2. Set baud rate to **115200** (bottom right dropdown)

3. You should see boot messages:
   ```
   === VOLT for Stone - Starting ===
   Power: Initialized
   Display: Initialized (ST7789)
   WiFi: Connecting to MyHomeWiFi...
   WiFi: Connected! IP: 192.168.1.123
   AI: Initialized successfully
   === VOLT Ready for Stone ===
   ```

### **Check the watch display:**

1. Screen should show:
   ```
   VOLT
   
   Ready to talk!
   
   Battery: 95%
   
   Press button to start
   ```

2. Colors should be clear (cyan and white text)

3. No flickering or artifacts

### **Test the button:**

1. Press the button once

2. LED should light up

3. Display should show "Listening..."

4. Serial Monitor shows:
   ```
   Button pressed: 1
   State: LISTENING
   Recording audio...
   ```

5. **If all this works → SUCCESS!**

---

# ✅ FINAL CHECKLIST

## Before Giving to Stone:

### **Hardware Tests:**
- [ ] Watch boots successfully
- [ ] Display shows clear text
- [ ] WiFi connects automatically
- [ ] Button responds (LED lights up)
- [ ] Battery shows percentage

### **Voice Tests (requires WiFi):**
- [ ] Press button → "Listening..." appears
- [ ] Speak → LED stays on while recording
- [ ] Release → "Thinking..." appears
- [ ] AI responds with speech
- [ ] Speech plays clearly from speaker

### **All Button Patterns:**
- [ ] 1 press → Talk to VOLT (voice conversation)
- [ ] 2 presses → Hear a joke
- [ ] 3 presses → Breathing exercise
- [ ] Long press (4+ sec) → Dad's love message
- [ ] 5 presses → WiFi setup mode

### **Battery:**
- [ ] Charges when plugged in
- [ ] Percentage updates correctly
- [ ] Lasts 2+ days with normal use

---

# 🆘 TROUBLESHOOTING

## Problem: "Port not found"

**Solution:**
1. Unplug and replug USB cable
2. Try different USB port on computer
3. Try different USB cable (must be data cable)
4. Install CH340 drivers (Step 4)
5. Restart computer
6. Check Device Manager → Ports (COM & LPT)

## Problem: "Compilation error"

**Solution:**
1. Check all 6 files in same folder:
   - volt_stone_FINAL.ino
   - config_stone_FINAL.h
   - volt_ai_FINAL.h
   - pins_hu087_FINAL.h
   - power_mgmt_FINAL.h
   - wifi_mgmt_FINAL.h

2. Verify libraries installed:
   - Tools → Manage Libraries
   - Search "TFT_eSPI" - should show "INSTALLED"
   - Search "ArduinoJson" - should show "INSTALLED"

3. Check TFT_eSPI configuration (Step 8)

4. Copy exact error and Google it

## Problem: "Connecting..." hangs

**Solution:**
1. Hold BOOT button while uploading
2. Release after "Writing..." appears
3. Lower upload speed to 115200
4. Try different USB cable
5. Try different USB port
6. Restart Arduino IDE

## Problem: Display shows nothing

**Solution:**
1. Check TFT_eSPI configuration (Step 8)
2. Verify Setup25_TTGO_T_Display.h is enabled
3. Reflash firmware
4. Check display connections (if DIY build)

## Problem: WiFi won't connect

**Solution:**
1. Check WiFi credentials (case-sensitive!)
2. Verify 2.4GHz network (not 5GHz)
3. Move closer to router
4. Check Serial Monitor for exact error
5. Try different WiFi network
6. Restart router

## Problem: Voice doesn't work

**Solution:**
1. Verify OpenAI API key is correct
2. Check WiFi is connected (Serial Monitor)
3. Check API key has credits: https://platform.openai.com/usage
4. Test microphone hardware
5. Check Serial Monitor for API errors

## Problem: "Out of memory" error

**Solution:**
1. This is normal during compilation
2. Make sure Partition Scheme is correct:
   - Tools → Partition Scheme
   - Select "16M Flash (3MB APP/9.9MB FATFS)"
3. Make sure PSRAM is enabled:
   - Tools → PSRAM → "OPI PSRAM"

---

# 📊 WHAT VOLT NEEDS FROM INTERNET

## During Flashing (One-time):

### **Downloads Required:**
1. **Arduino IDE** (~150 MB)
   - From: https://www.arduino.cc/en/software

2. **ESP32 Board Support** (~250 MB)
   - Auto-downloaded through Arduino IDE
   - URL: https://espressif.github.io/arduino-esp32/package_esp32_index.json

3. **TFT_eSPI Library** (~5 MB)
   - Auto-downloaded through Arduino IDE Library Manager

4. **ArduinoJson Library** (~1 MB)
   - Auto-downloaded through Arduino IDE Library Manager

5. **CH340 USB Drivers** (~1 MB) - if needed
   - From: https://sparks.gogo.co.nz/ch340.html

**Total Download: ~400 MB**

## During Use (Ongoing):

### **VOLT Uses These Internet Services:**

1. **OpenAI Whisper API** (Speech-to-Text)
   - Converts Stone's voice to text
   - Cost: ~$0.006 per minute of audio
   - Example: 10 conversations/day = ~$0.06/day

2. **OpenAI GPT-4 API** (AI Chat)
   - Generates responses to Stone
   - Cost: ~$0.03 per conversation
   - Example: 10 conversations/day = ~$0.30/day

3. **OpenAI TTS API** (Text-to-Speech)
   - Converts AI responses to voice
   - Cost: ~$0.015 per 1000 characters
   - Example: 10 responses/day = ~$0.05/day

**Total Daily Cost: ~$0.40/day = ~$12/month**

### **Internet Requirements:**
- WiFi: 2.4GHz network
- Speed: Any home internet (even slow)
- Data: ~50-100 MB per day
- Latency: Works with any normal connection

### **What Works Offline:**
- ✅ Jokes (pre-loaded)
- ✅ Breathing exercises
- ✅ Dad's love messages
- ✅ Display and buttons
- ❌ Voice conversations (needs internet)
- ❌ AI responses (needs internet)

---

# 🎉 SUCCESS!

## You Did It!

**If you completed all steps:**
- ✅ Arduino IDE installed
- ✅ ESP32 support installed
- ✅ Libraries installed
- ✅ TFT_eSPI configured
- ✅ VOLT firmware configured
- ✅ Firmware flashed to watch
- ✅ Watch boots and works

**VOLT is ready for Stone!**

---

## Next Steps:

1. **Disconnect USB cable** from watch

2. **Let Stone try it:**
   - Show him the button patterns
   - Let him talk to VOLT
   - Watch his reaction!

3. **Monitor for issues:**
   - Check battery life
   - Listen to voice quality
   - Watch for any errors

4. **Enjoy!**
   - Stone has his AI companion
   - You built something amazing
   - Dad of the year! 🏆

---

# 📞 NEED HELP?

## Quick Reference:

**Arduino IDE:** https://www.arduino.cc/en/software
**ESP32 Docs:** https://docs.espressif.com/projects/arduino-esp32/
**TFT_eSPI:** https://github.com/Bodmer/TFT_eSPI
**OpenAI API:** https://platform.openai.com/docs
**CH340 Drivers:** https://sparks.gogo.co.nz/ch340.html

## Forums:

**Arduino:** https://forum.arduino.cc/
**ESP32:** https://www.esp32.com/
**Reddit:** https://reddit.com/r/esp32

---

**Made with ❤️ by Dad for Stone**

*Last Updated: January 26, 2025*
*Version: 3-Window System Guide*
*Status: ✅ COMPLETE - READY TO USE*
