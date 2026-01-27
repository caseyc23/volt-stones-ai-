# Arduino IDE Compilation Guide

## Pre-Flight Compilation Test for VOLT Firmware

This guide helps you verify the firmware compiles correctly **before** flashing to Stone's watch.

---

## 🎯 Purpose

Compilation testing ensures:

- ✅ All code syntax is correct
- ✅ All libraries are installed
- ✅ Board settings are correct
- ✅ Memory usage is acceptable
- ✅ No warnings or errors

**Do this BEFORE connecting the watch!**

---

## 📋 Step 1: Install Arduino IDE

### Download and Install:

1. Go to: https://www.arduino.cc/en/software
2. Download Arduino IDE 2.x (latest version)
3. Install and launch

### Add ESP32 Board Support:

1. Open Arduino IDE
2. Go to **File → Preferences**
3. In "Additional Board Manager URLs", add:
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
4. Click **OK**
5. Go to **Tools → Board → Boards Manager**
6. Search for "esp32"
7. Install **"esp32 by Espressif Systems"** (version 2.0.11 or later)
8. Wait for installation to complete

---

## 📋 Step 2: Install Required Libraries

### Install via Library Manager:

1. Go to **Tools → Manage Libraries** (or Ctrl+Shift+I)
2. Search and install each library:

#### Required Libraries:

| Library Name    | Version | Purpose               |
| --------------- | ------- | --------------------- |
| **TFT_eSPI**    | 2.5.0+  | ST7789 display driver |
| **ArduinoJson** | 6.21.0+ | JSON parsing for APIs |

### Install Process:

**For TFT_eSPI:**

1. Search "TFT_eSPI"
2. Click **Install**
3. Wait for completion

**For ArduinoJson:**

1. Search "ArduinoJson"
2. Click **Install**
3. Wait for completion

---

## 📋 Step 3: Configure TFT_eSPI Library

### CRITICAL: This step is required for the display to work!

### Find TFT_eSPI Library Folder:

**Windows:**

```
C:\Users\[YourUsername]\Documents\Arduino\libraries\TFT_eSPI
```

**Mac:**

```
~/Documents/Arduino/libraries/TFT_eSPI
```

**Linux:**

```
~/Arduino/libraries/TFT_eSPI
```

### Edit Configuration:

1. Open the TFT_eSPI folder
2. Find and open **`User_Setup_Select.h`** in a text editor
3. Find this line (around line 22):
   ```cpp
   #include <User_Setup.h>
   ```
4. Comment it out by adding `//` at the start:
   ```cpp
   // #include <User_Setup.h>
   ```
5. Add this line below it:
   ```cpp
   #include <User_Setups/Setup25_TTGO_T_Display.h>
   ```
6. Save and close the file

### Verify Configuration:

Your `User_Setup_Select.h` should look like this:

```cpp
// Only ONE line below should be uncommented

// #include <User_Setup.h>           // ← COMMENTED OUT
#include <User_Setups/Setup25_TTGO_T_Display.h>  // ← ACTIVE

// #include <User_Setups/Setup0_ILI9341.h>
// ... (other setups commented out)
```

---

## 📋 Step 4: Open VOLT Firmware

1. Navigate to your VOLT folder:

   ```
   volt v5.00 flash/examples/VOLT_HU087_CLEAN/
   ```

2. Open **`volt_stone_FINAL.ino`** in Arduino IDE

3. Verify all tabs are loaded:
   - volt_stone_FINAL (main file)
   - config_stone_FINAL.h
   - volt_ai_FINAL.h
   - power_mgmt.h
   - wifi_mgmt.h
   - pins_hu087.h

---

## 📋 Step 5: Configure Board Settings

### Select Board:

1. Go to **Tools → Board → esp32**
2. Select **"ESP32S3 Dev Module"**

### Configure Settings (CRITICAL - Must Match Exactly):

| Setting              | Value                         |
| -------------------- | ----------------------------- |
| **USB CDC On Boot**  | Enabled                       |
| **CPU Frequency**    | 240MHz (WiFi)                 |
| **Flash Mode**       | QIO 80MHz                     |
| **Flash Size**       | 16MB (128Mb)                  |
| **Partition Scheme** | 16M Flash (3MB APP/9MB FATFS) |
| **PSRAM**            | OPI PSRAM                     |
| **Upload Speed**     | 921600                        |
| **USB Mode**         | Hardware CDC and JTAG         |
| **Arduino Runs On**  | Core 1                        |
| **Events Run On**    | Core 1                        |

### How to Set:

1. Go to **Tools** menu
2. Find each setting listed above
3. Select the exact value shown
4. Double-check all settings match

---

## 📋 Step 6: Verify Compilation

### Compile Without Upload:

1. Click the **Verify** button (✓ checkmark icon)
   - OR press **Ctrl+R** (Windows/Linux)
   - OR press **Cmd+R** (Mac)

2. Wait for compilation to complete

### Expected Output:

```
Sketch uses XXXXX bytes (XX%) of program storage space. Maximum is 3145728 bytes.
Global variables use XXXXX bytes (XX%) of dynamic memory, leaving XXXXX bytes for local variables. Maximum is 327680 bytes.
```

### ✅ Success Criteria:

- **Status:** "Done compiling"
- **Errors:** 0
- **Warnings:** 0 (or only library warnings, not your code)
- **Program Storage:** < 80% (should be around 40-60%)
- **Dynamic Memory:** < 80% (should be around 20-40%)

### ❌ Common Errors and Fixes:

#### Error: "TFT_eSPI.h: No such file or directory"

**Fix:** Install TFT_eSPI library (Step 2)

#### Error: "ArduinoJson.h: No such file or directory"

**Fix:** Install ArduinoJson library (Step 2)

#### Error: "User_Setup.h not configured"

**Fix:** Configure TFT_eSPI (Step 3)

#### Error: "ESP32S3 Dev Module not found"

**Fix:** Install ESP32 board support (Step 1)

#### Warning: "Large stack usage"

**Status:** ✅ OK - This is expected for JSON processing

#### Warning: "Unused variable"

**Status:** ✅ OK - Feature flags in config are intentionally unused

---

## 📋 Step 7: Check Memory Usage

### Analyze Compilation Output:

Look at the final compilation message:

```
Sketch uses 847234 bytes (26%) of program storage space. Maximum is 3145728 bytes.
Global variables use 45678 bytes (13%) of dynamic memory, leaving 281002 bytes for local variables. Maximum is 327680 bytes.
```

### Memory Guidelines:

| Memory Type         | Current      | Maximum | Status                |
| ------------------- | ------------ | ------- | --------------------- |
| **Program Storage** | ~850KB (26%) | 3MB     | ✅ Excellent          |
| **Dynamic Memory**  | ~45KB (13%)  | 320KB   | ✅ Excellent          |
| **Free RAM**        | ~280KB       | -       | ✅ Plenty for runtime |

### ⚠️ Warning Signs:

- **Program Storage > 80%:** Code too large, may not fit
- **Dynamic Memory > 80%:** Risk of stack overflow
- **Free RAM < 100KB:** May crash during runtime

### ✅ VOLT Expected Usage:

- **Program Storage:** 25-35% (800KB - 1.1MB)
- **Dynamic Memory:** 10-20% (30KB - 65KB)
- **Free RAM:** 260KB+ (plenty for audio buffers)

---

## 📋 Step 8: Verify Configuration

### Before First Flash, Check:

1. Open **`config_stone_FINAL.h`**

2. Verify these are set:

   ```cpp
   const char* WIFI_SSID = "YOUR_WIFI_NAME";  // ← Change this
   const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";  // ← Change this
   const char* OPENAI_API_KEY = "sk-YOUR_KEY_HERE";  // ← Change this
   ```

3. If not set, you'll see compile-time warnings:
   ```
   #warning "WiFi credentials not configured!"
   #warning "OpenAI API key not configured!"
   ```

### ⚠️ These warnings are OK for compilation testing!

You can compile without real credentials, but you MUST add them before flashing to the watch.

---

## 📋 Step 9: Pre-Flash Checklist

### Before connecting the watch:

- [ ] Arduino IDE installed and configured
- [ ] ESP32 board support installed
- [ ] TFT_eSPI library installed and configured
- [ ] ArduinoJson library installed
- [ ] Board settings match exactly (Step 5)
- [ ] Firmware compiles with 0 errors
- [ ] Memory usage is acceptable (< 80%)
- [ ] WiFi credentials added to config
- [ ] OpenAI API key added to config
- [ ] Watch is charged to 100%

### ✅ All checked? Ready to flash!

Proceed to **FIXES_AND_SETUP_GUIDE.md** for flashing instructions.

---

## 🆘 Troubleshooting

### Compilation Fails:

1. **Check library installation**
   - Tools → Manage Libraries
   - Verify TFT_eSPI and ArduinoJson are installed

2. **Check board selection**
   - Tools → Board → esp32 → ESP32S3 Dev Module

3. **Check TFT_eSPI configuration**
   - Verify User_Setup_Select.h is edited correctly

4. **Clean and rebuild**
   - Sketch → Clean Build Folder
   - Try compiling again

### Memory Warnings:

1. **If program storage > 80%:**
   - Disable unused features in config_stone_FINAL.h
   - Set DEBUG_MODE = false
   - Set VERBOSE_LOGGING = false

2. **If dynamic memory > 80%:**
   - Reduce BUFFER_SIZE in config
   - Reduce MAX_TOKENS in config

### Library Conflicts:

1. **Multiple TFT libraries installed:**
   - Uninstall other TFT libraries
   - Keep only TFT_eSPI

2. **Old ESP32 board version:**
   - Update to ESP32 board support 2.0.11+
   - Tools → Boards Manager → esp32 → Update

---

## 📊 Expected Compilation Time

| Step                    | Time          |
| ----------------------- | ------------- |
| First compilation       | 2-3 minutes   |
| Subsequent compilations | 30-60 seconds |
| Clean build             | 2-3 minutes   |

**Slow compilation?**

- Normal for ESP32 projects
- First compile is always slower
- Subsequent compiles use cache

---

## ✅ Success!

If you see:

```
Done compiling
Sketch uses XXXXX bytes (XX%) of program storage space.
Global variables use XXXXX bytes (XX%) of dynamic memory.
```

**You're ready to flash to Stone's watch!**

Next steps:

1. Add WiFi credentials to config_stone_FINAL.h
2. Add OpenAI API key to config_stone_FINAL.h
3. Connect watch via USB
4. Follow FIXES_AND_SETUP_GUIDE.md to flash

---

**Made with ❤️ by Dad for Stone**

_Compilation successful? Time to make Stone's watch come alive!_
