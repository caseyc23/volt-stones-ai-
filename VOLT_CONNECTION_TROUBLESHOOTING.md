# 🔌 VOLT Watch Connection Troubleshooting Guide

## ⚠️ IMPORTANT: Missing Firmware Files

**The current folder only contains documentation files!**

You need to download the complete firmware from the OneDrive link you provided:
**https://1drv.ms/f/c/0DC5D6C0CD3D8559/IgAEj97MZX4QRIPe4lGwMqDDAfHivl7IbyweC8M4ub4LTyw?e=MoEQRB**

### Required Files (Currently Missing):

- ✅ `volt_firmware.ino` - Main firmware code
- ✅ `config.h` - Configuration settings
- ✅ `wifi_manager.h` - WiFi management
- ✅ `web_api.h` - REST API server
- ✅ `voice.h` - Voice settings
- ✅ `memory.h` - Storage management
- ✅ `content.h` - Messages and content
- ✅ `pins.h` - Hardware pin definitions
- ✅ `platformio.ini` - Build configuration

---

## 📥 Step 1: Download Complete Firmware

1. **Open the OneDrive link** in your browser
2. **Download all files** to this folder: `c:/Users/Holle/Desktop/volt v5.00 flash`
3. **Verify** you have the `.ino` files and `platformio.ini`

---

## 🔍 Step 2: Check if VOLT is Detected

### Option A: Check Device Manager (Windows)

1. **Press** `Windows + X`
2. **Select** "Device Manager"
3. **Look for** one of these:
   - **Ports (COM & LPT)** → "Silicon Labs CP210x USB to UART Bridge (COM#)"
   - **Ports (COM & LPT)** → "USB Serial Device (COM#)"
   - **Other devices** → "CP2102 USB to UART Bridge Controller" (needs driver)

### Option B: Use PowerShell Command

Run this in PowerShell (already open in VSCode):

```powershell
Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match '^USB' } | Select-Object Status, Class, FriendlyName, InstanceId
```

Or simpler:

```powershell
Get-WmiObject Win32_PnpEntity | Where-Object { $_.Name -match 'COM' } | Select-Object Name, DeviceID
```

---

## 🔧 Step 3: Troubleshooting Connection Issues

### Issue 1: Watch Not Detected at All

**Symptoms:**

- No new device appears in Device Manager
- Windows doesn't make a sound when plugging in
- Watch doesn't power on

**Solutions:**

✅ **Check USB Cable**

- Try a **different USB cable** (must support data, not just charging)
- Some cables are charge-only and won't work

✅ **Check USB Port**

- Try a **different USB port** on your computer
- Use a **USB 2.0 port** (not USB-C hub if possible)
- Avoid USB hubs - connect directly to computer

✅ **Check Watch Power**

- Does the watch screen turn on when plugged in?
- Try holding the power button for 5 seconds
- Check if battery is completely dead (charge for 10 minutes first)

---

### Issue 2: Device Detected but Shows as "Unknown Device"

**Symptoms:**

- Device appears in Device Manager with yellow warning triangle
- Shows as "Unknown Device" or "CP2102 USB to UART Bridge Controller"
- No COM port assigned

**Solution: Install CP210x Drivers**

1. **Download driver** from Silicon Labs:
   - URL: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
   - Download the **Windows** version

2. **Install the driver:**
   - Run the downloaded installer
   - Follow installation prompts
   - **Restart your computer** after installation

3. **Verify installation:**
   - Unplug and replug the watch
   - Check Device Manager again
   - Should now show "Silicon Labs CP210x USB to UART Bridge (COM#)"

---

### Issue 3: COM Port Detected but Upload Fails

**Symptoms:**

- Device shows in Device Manager with COM port
- PlatformIO can't upload firmware
- Error: "Port not found" or "Upload failed"

**Solutions:**

✅ **Hold BOOT Button During Upload**

1. Locate the **BOOT button** on your watch
2. **Hold it down**
3. Click **Upload (→)** in VSCode
4. **Keep holding** BOOT until you see "Connecting..."
5. **Release** BOOT button
6. Upload should proceed

✅ **Check COM Port in PlatformIO**

1. Open `platformio.ini` file
2. Look for `upload_port` setting
3. Make sure it matches your COM port from Device Manager
4. Example:
   ```ini
   upload_port = COM3
   ```

✅ **Close Other Programs**

- Close any **Serial Monitor** windows
- Close **Arduino IDE** if open
- Close any other program that might be using the COM port

---

### Issue 4: ESP32 Not Entering Flash Mode

**Symptoms:**

- Upload starts but fails with "Failed to connect to ESP32"
- Timeout errors during upload

**Solution: Manual Boot Mode**

**Method 1: BOOT + RESET Sequence**

1. Hold **BOOT** button
2. Press and release **RESET** button (while still holding BOOT)
3. Release **BOOT** button
4. Click **Upload** in VSCode immediately

**Method 2: BOOT During Power-On**

1. Unplug USB cable
2. Hold **BOOT** button
3. Plug in USB cable (while holding BOOT)
4. Click **Upload** in VSCode
5. Release BOOT when upload starts

---

## 🛠️ Step 4: Verify PlatformIO Setup

### Check PlatformIO Extension

1. **Open VSCode Extensions** (Ctrl+Shift+X)
2. **Search for** "PlatformIO IDE"
3. **Verify** it's installed and enabled
4. **Restart VSCode** if you just installed it

### Check Project Structure

After downloading firmware files, verify:

```
volt v5.00 flash/
├── platformio.ini          ← Must have this!
├── volt_firmware.ino       ← Must have this!
├── config.h
├── wifi_manager.h
├── src/ (or lib/)
└── ... other files
```

### Initialize PlatformIO Project

If PlatformIO doesn't recognize the project:

1. **Open Terminal** in VSCode (Ctrl+`)
2. **Run:**
   ```bash
   pio init
   ```
3. **Restart VSCode**

---

## 📋 Step 5: Complete Pre-Flash Checklist

Before attempting to flash:

- [ ] ✅ All firmware files downloaded from OneDrive
- [ ] ✅ `platformio.ini` file exists in project folder
- [ ] ✅ PlatformIO extension installed in VSCode
- [ ] ✅ USB cable connected (data cable, not charge-only)
- [ ] ✅ Watch powers on when connected
- [ ] ✅ CP210x drivers installed (if needed)
- [ ] ✅ Device appears in Device Manager with COM port
- [ ] ✅ No other programs using the COM port
- [ ] ✅ Know which COM port to use (e.g., COM3)

---

## 🚀 Step 6: Try Flashing

Once everything is ready:

1. **Open this folder** in VSCode: `c:/Users/Holle/Desktop/volt v5.00 flash`
2. **Look at bottom blue bar** in VSCode
3. **Click the → (Upload) icon**
4. **If it fails**, hold BOOT button and try again
5. **Wait** for compilation and upload (1-2 minutes)

---

## 🔍 Diagnostic Commands

Run these in PowerShell to gather information:

### Check USB Devices

```powershell
Get-PnpDevice -PresentOnly | Where-Object { $_.Class -eq 'Ports' }
```

### Check COM Ports

```powershell
[System.IO.Ports.SerialPort]::getportnames()
```

### Check Driver Status

```powershell
Get-WmiObject Win32_PnpSignedDriver | Where-Object { $_.DeviceName -match 'CP210x' }
```

---

## 📞 Quick Reference

### Common Error Messages

| Error               | Cause                  | Solution               |
| ------------------- | ---------------------- | ---------------------- |
| "Port not found"    | No COM port detected   | Install CP210x drivers |
| "Upload failed"     | Can't enter flash mode | Hold BOOT button       |
| "Timeout"           | Wrong COM port         | Check Device Manager   |
| "Access denied"     | Port in use            | Close other programs   |
| "Compilation error" | Missing files          | Download from OneDrive |

### Important Links

- **CP210x Drivers:** https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
- **OneDrive Firmware:** https://1drv.ms/f/c/0DC5D6C0CD3D8559/IgAEj97MZX4QRIPe4lGwMqDDAfHivl7IbyweC8M4ub4LTyw?e=MoEQRB
- **PlatformIO Docs:** https://docs.platformio.org/

---

## ✅ Next Steps

1. **Download firmware** from OneDrive link
2. **Check connection** using Device Manager
3. **Install drivers** if needed (CP210x)
4. **Verify COM port** is detected
5. **Try flashing** with BOOT button if needed

---

## 🆘 Still Having Issues?

If you've tried everything above and VOLT still won't connect:

1. **Take a photo** of Device Manager showing USB devices
2. **Copy error messages** from VSCode terminal
3. **Note your COM port number** (if detected)
4. **Check if watch screen turns on** when plugged in

This information will help diagnose the specific issue!

---

**Good luck getting VOLT connected!** ⚡💙
