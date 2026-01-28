# 🚀 VOLT Easy Flash Guide for Stone's Watch

## Three Simple Methods to Flash Your Watch

---

## 📋 What You'll Need

### Hardware:

- ✅ Stone's HU-087 ESP32-S3 watch (fully charged)
- ✅ USB-C cable (good quality, data-capable)
- ✅ Windows computer

### Software (we'll install together):

- ✅ Arduino IDE 2.x OR ESP Flash Download Tool
- ✅ USB drivers (CH340 or CP2102)

### Information:

- ✅ Your WiFi name (SSID)
- ✅ Your WiFi password
- ✅ OpenAI API key (from https://platform.openai.com/api-keys)

**Time Required:** 30-45 minutes first time, 10 minutes after that

---

## 🎯 Choose Your Method

### **Method 1: Arduino IDE** (RECOMMENDED)

- ✅ Best for beginners
- ✅ Easy to customize code
- ✅ See real-time debugging
- ✅ Most control
- ⏱️ 30-45 minutes setup

### **Method 2: ESP Flash Download Tool** (FASTEST)

- ✅ Fastest flashing (2 minutes)
- ✅ No coding knowledge needed
- ✅ Official Espressif tool
- ❌ Can't customize easily
- ⏱️ 15 minutes setup

### **Method 3: Web Flasher** (EASIEST)

- ✅ No software installation
- ✅ Works in Chrome browser
- ✅ Click and flash
- ❌ Requires pre-compiled firmware
- ⏱️ 5 minutes

---

# METHOD 1: Arduino IDE (RECOMMENDED)

## Step 1: Install Arduino IDE

1. **Download Arduino IDE 2.3.2:**
   - Go to: https://www.arduino.cc/en/software
   - Click "Windows Win 10 and newer, 64 bits"
   - Download the `.exe` installer

2. **Install Arduino IDE:**
   - Run the downloaded `.exe` file
   - Click "I Agree" → "Next" → "Install"
   - Wait for installation (2-3 minutes)
   - Click "Finish"

3. **Launch Arduino IDE:**
   - Open Arduino IDE from Start Menu
   - Wait for it to fully load

---

## Step 2: Install ESP32 Board Support

1. **Open Preferences:**
   - Click `File` → `Preferences` (or press `Ctrl+Comma`)

2. **Add ESP32 Board Manager URL:**
   - Find "Additional boards manager URLs"
   - Paste this URL:
     ```
     https://espressif.github.io/arduino-esp32/package_esp32_index.json
     ```
   - Click "OK"

3. **Install ESP32 Boards:**
   - Click `Tools` → `Board` → `Boards Manager`
   - In the search box, type: `esp32`
   - Find "esp32 by Espressif Systems"
   - Click "INSTALL" (version 2.0.11 or newer)
   - Wait 5-10 minutes for download
   - Close Boards Manager when done

---

## Step 3: Install Required Libraries

1. **Open Library Manager:**
   - Click `Tools` → `Manage Libraries` (or press `Ctrl+Shift+I`)

2. **Install TFT_eSPI:**
   - Search for: `TFT_eSPI`
   - Find "TFT_eSPI by Bodmer"
   - Click "INSTALL"
   - Wait for installation

3. **Install ArduinoJson:**
   - Search for: `ArduinoJson`
   - Find "ArduinoJson by Benoit Blanchon"
   - Click "INSTALL" (version 6.x)
   - Wait for installation

4. **Close Library Manager**

---

## Step 4: Configure TFT_eSPI Library

**CRITICAL:** This step is essential for the display to work!

1. **Find TFT_eSPI Library Folder:**
   - Windows: `C:\Users\[YourUsername]\Documents\Arduino\libraries\TFT_eSPI`
   - Or click `File` → `Preferences` and note the "Sketchbook location"

2. **Open User_Setup_Select.h:**
   - Navigate to the TFT_eSPI folder
   - Open `User_Setup_Select.h` in Notepad

3. **Comment Out Default Setup:**
   - Find this line (around line 22):
     ```cpp
     #include <User_Setup.h>
     ```
   - Add `//` at the start to make it:
     ```cpp
     // #include <User_Setup.h>
     ```

4. **Enable TTGO T-Display Setup:**
   - Find this line (around line 53):
     ```cpp
     //#include <User_Setups/Setup25_TTGO_T_Display.h>
     ```
   - Remove the `//` to make it:
     ```cpp
     #include <User_Setups/Setup25_TTGO_T_Display.h>
     ```

5. **Save and Close** the file

---

## Step 5: Configure VOLT for Stone

1. **Open VOLT Firmware:**
   - In Arduino IDE, click `File` → `Open`
   - Navigate to: `C:\Users\Holle\Desktop\volt v5.00 flash\examples\examples\VOLT_HU087_CLEAN`
   - Open `volt_stone_FINAL.ino`

2. **Open Configuration Tab:**
   - You'll see multiple tabs at the top
   - Click on the `config_stone_FINAL.h` tab

3. **Edit WiFi Settings:**
   - Find these lines (around line 23):
     ```cpp
     const char* WIFI_SSID = "YOUR_WIFI_NAME";
     const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
     ```
   - Replace with YOUR actual WiFi:
     ```cpp
     const char* WIFI_SSID = "MyHomeWiFi";  // Your WiFi name
     const char* WIFI_PASSWORD = "MyPassword123";  // Your WiFi password
     ```
   - **IMPORTANT:** WiFi must be 2.4GHz (not 5GHz)

4. **Add OpenAI API Key:**
   - Find this line (around line 33):
     ```cpp
     const char* OPENAI_API_KEY = "sk-YOUR_OPENAI_KEY_HERE";
     ```
   - Replace with your actual key:
     ```cpp
     const char* OPENAI_API_KEY = "sk-proj-abc123...";  // Your real key
     ```
   - Get your key from: https://platform.openai.com/api-keys

5. **Verify Stone's Info:**
   - Find these lines (around line 18):
     ```cpp
     const char* CHILD_NAME = "Stone";
     const int CHILD_AGE = 8;
     ```
   - These should already be correct!

6. **Save All Files:**
   - Press `Ctrl+S` or click `File` → `Save`

---

## Step 6: Connect the Watch

1. **Charge the Watch:**
   - Make sure Stone's watch is charged to at least 50%
   - Ideally 100% for first flash

2. **Connect USB Cable:**
   - Plug USB-C cable into the watch
   - Plug other end into your computer
   - Watch should show charging indicator

3. **Install Drivers (if needed):**
   - Windows should auto-install drivers
   - If not, download CH340 drivers from:
     https://sparks.gogo.co.nz/ch340.html

4. **Check Connection:**
   - In Arduino IDE, click `Tools` → `Port`
   - You should see a COM port (e.g., "COM3", "COM5")
   - If you see multiple, unplug the watch and see which one disappears
   - Select the correct COM port

---

## Step 7: Configure Board Settings

**CRITICAL:** These settings MUST be exact!

1. **Select Board:**
   - Click `Tools` → `Board` → `ESP32 Arduino` → `ESP32S3 Dev Module`

2. **Configure Settings:**
   Set these EXACTLY as shown:

   ```
   USB CDC On Boot: "Enabled"
   CPU Frequency: "240MHz (WiFi)"
   Core Debug Level: "None"
   Erase All Flash Before Sketch Upload: "Disabled"
   Events Run On: "Core 1"
   Flash Mode: "QIO 80MHz"
   Flash Size: "16MB (128Mb)"
   JTAG Adapter: "Disabled"
   Arduino Runs On: "Core 1"
   Partition Scheme: "16M Flash (3MB APP/9.9MB FATFS)"
   PSRAM: "OPI PSRAM"
   Upload Mode: "UART0 / Hardware CDC"
   Upload Speed: "921600"
   USB Mode: "Hardware CDC and JTAG"
   ```

3. **Double-Check Port:**
   - `Tools` → `Port` → Select your COM port

---

## Step 8: Flash the Firmware

1. **Verify Code First:**
   - Click the ✓ (checkmark) button at top left
   - This compiles the code without uploading
   - Wait 1-2 minutes
   - Should say "Done compiling" at bottom
   - If errors appear, see Troubleshooting section

2. **Upload to Watch:**
   - Click the → (arrow) button at top left
   - This uploads to the watch
   - **DO NOT DISCONNECT THE WATCH!**
   - You'll see progress:
     ```
     Connecting........_____.....
     Chip is ESP32-S3 (revision v0.1)
     Writing at 0x00010000... (10%)
     Writing at 0x00020000... (20%)
     ...
     Writing at 0x00100000... (100%)
     Hard resetting via RTS pin...
     Done uploading.
     ```

3. **If "Connecting..." Hangs:**
   - Hold the BOOT button on the watch
   - While holding, click Upload again
   - Keep holding until you see "Writing..."
   - Then release the button

4. **Wait for Completion:**
   - Total time: 2-3 minutes
   - Don't touch anything!
   - Should say "Done uploading"

---

## Step 9: Verify It Works

1. **Open Serial Monitor:**
   - Click `Tools` → `Serial Monitor`
   - Set baud rate to `115200` (bottom right)

2. **Watch Should Boot:**
   - You'll see startup messages:
     ```
     === VOLT for Stone - Starting ===
     Power: Initialized
     Display: Initialized
     WiFi: Connecting to MyHomeWiFi...
     WiFi: Connected! IP: 192.168.1.123
     AI: Initialized successfully
     === VOLT Ready for Stone ===
     ```

3. **Check the Display:**
   - Watch screen should show:
     - "VOLT" in large cyan text
     - "Ready to talk!" or "Offline mode"
     - Battery percentage
     - "Press button to start"

4. **Test the Button:**
   - Press the button once
   - LED should light up
   - Display should show "Listening..."
   - Serial Monitor shows "Button pressed: 1"

5. **Success!**
   - If all above works, VOLT is ready!
   - Disconnect USB cable
   - Give to Stone!

---

# METHOD 2: ESP Flash Download Tool (FASTEST)

## Coming Soon!

This method requires pre-compiled firmware files. I'll create these for you if you prefer this method.

---

# METHOD 3: Web Flasher (EASIEST)

## Coming Soon!

This method requires hosting the firmware online. I'll set this up if you prefer this method.

---

# 🆘 Troubleshooting

## Problem: "Port not found" or "No COM port"

**Solution:**

1. Unplug and replug the USB cable
2. Try a different USB port
3. Try a different USB cable (must be data cable, not charge-only)
4. Install CH340 drivers: https://sparks.gogo.co.nz/ch340.html
5. Restart computer

## Problem: "Compilation error" or "Error compiling"

**Solution:**

1. Check that all files are in the same folder:
   - volt_stone_FINAL.ino
   - config_stone_FINAL.h
   - volt_ai_FINAL.h
   - pins_hu087_FINAL.h
   - power_mgmt_FINAL.h
   - wifi_mgmt_FINAL.h

2. Make sure you installed:
   - ESP32 board support (version 2.0.11+)
   - TFT_eSPI library
   - ArduinoJson library

3. Check TFT_eSPI configuration (Step 4)

4. Copy the exact error message and search Google

## Problem: "Connecting........" hangs forever

**Solution:**

1. Hold BOOT button while clicking Upload
2. Release after "Writing..." appears
3. If still fails, try:
   - Lower upload speed to 115200
   - Different USB cable
   - Different USB port
   - Restart Arduino IDE

## Problem: Display shows nothing or garbage

**Solution:**

1. Check TFT_eSPI configuration (Step 4)
2. Make sure you enabled Setup25_TTGO_T_Display.h
3. Reflash the firmware
4. Check display connections (if DIY build)

## Problem: WiFi won't connect

**Solution:**

1. Check WiFi credentials (case-sensitive!)
2. Make sure WiFi is 2.4GHz (not 5GHz)
3. Move closer to router
4. Check router allows new devices
5. Try different WiFi network
6. Check Serial Monitor for exact error

## Problem: Voice doesn't work

**Solution:**

1. Check OpenAI API key is correct
2. Verify WiFi is connected (check Serial Monitor)
3. Check API key has credits: https://platform.openai.com/usage
4. Test microphone hardware
5. Check Serial Monitor for API errors

## Problem: Battery drains fast

**Solution:**

1. Enable deep sleep in config:
   ```cpp
   const bool ENABLE_DEEP_SLEEP = true;
   ```
2. Reduce display brightness:
   ```cpp
   const int DISPLAY_BRIGHTNESS = 150;  // Lower = longer battery
   ```
3. Enable WiFi sleep:
   ```cpp
   const bool ENABLE_WIFI_SLEEP = true;
   ```
4. Check for battery hardware issues

## Problem: Watch keeps restarting

**Solution:**

1. Check Serial Monitor for crash reason
2. Might be memory issue - check code
3. Might be power issue - check battery
4. Try reflashing with "Erase All Flash" enabled
5. Check for hardware shorts

---

# ✅ Success Checklist

After flashing, verify these work:

### Boot & Display:

- [ ] Watch boots successfully
- [ ] Display shows VOLT screen clearly
- [ ] Battery percentage shows correctly
- [ ] No flickering or artifacts

### WiFi:

- [ ] WiFi connects automatically
- [ ] Shows "Ready to talk!" when online
- [ ] Shows "Offline mode" when no WiFi
- [ ] Reconnects after WiFi drops

### Button:

- [ ] Button press lights up LED
- [ ] Display responds to button
- [ ] Serial Monitor shows button presses
- [ ] No false triggers

### Voice (requires WiFi):

- [ ] Press button → "Listening..." appears
- [ ] Can record voice (LED stays on)
- [ ] Voice gets transcribed (check Serial Monitor)
- [ ] AI responds with speech
- [ ] Speech plays clearly

### All Button Patterns:

- [ ] 1 press → Talk to VOLT
- [ ] 2 presses → Hear a joke
- [ ] 3 presses → Breathing exercise
- [ ] Long press → Dad's love message
- [ ] 5 presses → WiFi setup

### Power:

- [ ] Battery lasts 2+ days
- [ ] Deep sleep works
- [ ] Wakes from sleep properly
- [ ] Charges correctly

**All checked?** 🎉 VOLT is ready for Stone!

---

# 📞 Need More Help?

1. **Check Serial Monitor** - Shows real-time debugging
2. **Read error messages carefully** - Usually tells you the problem
3. **Google the exact error** - Someone else has solved it
4. **Check Arduino forums** - Helpful community
5. **Review this guide again** - Might have missed a step

---

# 🎉 You Did It!

**Congratulations!** You've successfully flashed VOLT to Stone's watch!

**Next Steps:**

1. ✅ Test all features (use TESTING_CHECKLIST.md)
2. ✅ Let Stone try it
3. ✅ Monitor for any issues
4. ✅ Enjoy watching Stone use his AI companion!

**Remember:**

- VOLT learns from Stone's usage
- Battery life improves after first few charges
- You can reflash anytime to update
- Stone's data is private and secure

---

**Made with ❤️ by Dad for Stone**

_Last Updated: January 26, 2025_
_Version: FINAL - Production Ready_
