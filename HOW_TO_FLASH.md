# 🚀 How to Flash VOLT v5.00 to Your Watch

## Quick Steps (3 Minutes!)

### Step 1: Open in VSCode

1. Open **VSCode**
2. Click **File → Open Folder**
3. Select this folder: `volt v5.00 flash`
4. Click **Select Folder**

### Step 2: Connect Your Watch

1. Plug USB cable into your watch
2. Connect other end to your computer
3. Watch should power on

### Step 3: Flash the Firmware

**Look at the BOTTOM of VSCode** (the blue bar at the very bottom)

You'll see several icons. Click the **→** (right arrow) icon that says "PlatformIO: Upload"

**That's it!** The firmware will compile and upload automatically.

---

## 📍 Where to Click in VSCode

```
┌─────────────────────────────────────────────────────────┐
│  VSCode Window                                          │
│                                                         │
│  Your code files here...                                │
│                                                         │
└─────────────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────────────┐
│ ✓ | ⚠ | 🏠 | 🔍 | ⚙️ | → | 🔌 | 🗑️ |  volt_watch      │  ← BLUE BAR
└─────────────────────────────────────────────────────────┘
              ↑
         CLICK THIS ARROW (→)
         "PlatformIO: Upload"
```

---

## ⏱️ What You'll See

1. **Building...** (30-60 seconds)
   - VSCode compiles the firmware
   - You'll see progress in the terminal

2. **Uploading...** (10-20 seconds)
   - Firmware transfers to watch
   - Progress bar shows percentage

3. **Success!** ✅
   - Terminal shows "SUCCESS"
   - Watch reboots automatically

---

## 🎯 After Flashing

### Your watch will show:

1. **VOLT logo** (boot screen)
2. **"Finding WiFi..."** message
3. **WiFi Setup screen** (if no WiFi configured)

### To Set Up WiFi:

**Option 1: Automatic (Easiest)**

1. Watch enters AP mode automatically
2. On your phone, connect to WiFi: `VOLT-Setup-XXXX`
3. Password: `volt2024`
4. Open browser to: `http://192.168.4.1`
5. Add your WiFi network
6. Restart watch

**Option 2: Manual (Before Flashing)**

1. Open `config.h` in VSCode
2. Find these lines:
   ```cpp
   const char* WIFI_SSID = "YOUR_WIFI_NAME";
   const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
   const char* OPENAI_API_KEY = "sk-YOUR_API_KEY_HERE";
   ```
3. Replace with your actual WiFi name, password, and OpenAI API key
4. Save the file (Ctrl+S)
5. Then flash as normal

---

## 🆘 Troubleshooting

### "Port not found" or "Upload failed"

**Solution 1: Hold BOOT button**

1. Hold the BOOT button on your watch
2. Click Upload (→) in VSCode
3. Keep holding BOOT until upload starts
4. Release BOOT button

**Solution 2: Try different USB port**

- Unplug and plug into different USB port
- Try a different USB cable

**Solution 3: Install drivers**

- Download CP210x driver from: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
- Install and restart computer

### "Compilation error"

**Check these:**

1. Did you open the correct folder in VSCode?
2. Is PlatformIO extension installed?
3. Try: Click Terminal → Run Task → PlatformIO: Clean

---

## 🎮 New Features in v5.00

### Button Controls:

- **1 press**: Talk to VOLT
- **2 presses**: Tell a joke
- **3 presses**: Breathing exercise
- **4 presses (long)**: Emergency love message
- **5 presses**: WiFi setup mode ⭐ NEW!

### WiFi Features:

✅ Store up to 5 WiFi networks
✅ Automatic network switching
✅ WiFi scanning
✅ Web-based setup
✅ REST API for remote control

---

## 📱 Quick Reference

### VSCode Shortcuts:

- **Upload**: Click → in bottom bar OR press `Ctrl+Alt+U`
- **Serial Monitor**: Click 🔌 in bottom bar OR press `Ctrl+Alt+S`
- **Clean Build**: `Ctrl+Alt+C`

### Watch is Ready When You See:

```
⚡ VOLT - AI Companion Watch
💙 Dad's love, always with Stone
📶 Connecting to WiFi...
✅ WiFi connected!
✅ VOLT is ready for Stone!
```

---

## 🎉 That's It!

Your watch is now running VOLT v5.00 with WiFi management!

**Need more help?** Check these files:

- `VSCODE_FLASHING_GUIDE.md` - Detailed instructions
- `WIFI_SETUP_GUIDE.md` - WiFi configuration help
- `WIFI_API_DOCUMENTATION.md` - API reference

---

**Version:** 5.00 - WiFi Manager & API Edition  
**Ready to flash!** Just click the → arrow in VSCode!
