# 🔧 Fix VOLT Connection - Step by Step

## 🚨 Current Problem Detected

Your VOLT watch is connected but showing as:

- ❌ **"Unknown USB Device (Device Descriptor Request Failed)"**
- ❌ **No COM port available**
- ❌ **Error status in Device Manager**

This means Windows can't communicate with the watch.

---

## ✅ Solution: 3-Step Fix

### Step 1: Install CP210x USB Drivers

The VOLT watch uses a **Silicon Labs CP210x USB-to-UART bridge chip**. You need the driver.

**Download and Install:**

1. **Go to:** https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers

2. **Download:** Click "Downloads" tab → Select **"CP210x Windows Drivers"**

3. **Install:**
   - Run the downloaded `.exe` file
   - Click "Next" through the installer
   - Allow administrator access if prompted
   - Wait for "Installation Complete"

4. **Restart your computer** (important!)

---

### Step 2: Reset the USB Connection

After restarting:

1. **Unplug** the VOLT watch from USB
2. **Wait 10 seconds**
3. **Plug it back in** to a **different USB port**
4. **Listen** for Windows connection sound
5. **Watch the screen** - does it power on?

---

### Step 3: Verify Connection

Run this command in PowerShell to check:

```powershell
Get-PnpDevice -PresentOnly | Where-Object { $_.FriendlyName -match 'CP210x|Serial|COM' }
```

**You should now see:**

- ✅ "Silicon Labs CP210x USB to UART Bridge (COM3)" or similar
- ✅ Status: OK
- ✅ A COM port number (COM3, COM4, etc.)

---

## 🔍 Alternative: Check Device Manager Manually

1. **Press** `Windows + X`
2. **Select** "Device Manager"
3. **Look for:**
   - **Ports (COM & LPT)** → Should show "Silicon Labs CP210x USB to UART Bridge (COM#)"
   - **If you see a yellow triangle** → Right-click → "Update driver" → "Search automatically"

---

## 🛠️ If Still Not Working

### Try: Manual Driver Installation

1. **Open Device Manager** (Windows + X → Device Manager)
2. **Find** "Unknown USB Device" under "Other devices" or "Universal Serial Bus controllers"
3. **Right-click** → "Update driver"
4. **Select** "Browse my computer for drivers"
5. **Select** "Let me pick from a list of available drivers"
6. **Choose** "Ports (COM & LPT)"
7. **Select** "Silicon Labs" → "CP210x USB to UART Bridge"
8. **Click** "Next" and install

---

### Try: Different USB Cable

Some USB cables are **charge-only** and don't have data wires!

**Test:**

- ✅ Try a **different USB cable**
- ✅ Use a cable that works for data transfer (like one from a phone that can transfer files)
- ✅ Avoid very long cables (under 6 feet is best)

---

### Try: USB 2.0 Port

ESP32 devices sometimes have issues with USB 3.0 ports:

- ✅ Try a **USB 2.0 port** (usually the black ones, not blue)
- ✅ Avoid USB hubs - connect **directly to computer**
- ✅ Try ports on the **back of desktop** (more reliable than front panel)

---

### Try: Boot Mode Manually

The watch might need to be put in flash mode manually:

1. **Locate** the **BOOT button** on your VOLT watch
2. **Hold down** the BOOT button
3. **While holding BOOT**, plug in the USB cable
4. **Keep holding** for 3 seconds
5. **Release** BOOT button
6. **Check** Device Manager again

---

## 📋 Checklist Before Flashing

Once the driver is installed and device is recognized:

- [ ] ✅ CP210x driver installed
- [ ] ✅ Computer restarted
- [ ] ✅ Watch connected via USB
- [ ] ✅ Watch powers on (screen lights up)
- [ ] ✅ Device Manager shows "Silicon Labs CP210x USB to UART Bridge (COM#)"
- [ ] ✅ No yellow warning triangles in Device Manager
- [ ] ✅ COM port number noted (e.g., COM3)

---

## 🚀 Next: Download Firmware Files

**Important:** You still need the actual firmware files!

The current folder only has documentation. Download from OneDrive:

**Latest link you provided:**
https://1drv.ms/u/c/0DC5D6C0CD3D8559/IQAFp98ClbVVSq7dFdes9HmHAfYQ03gS6bqm7hptNtBquNE?e=NOeXhx

**What you need:**

- `volt_firmware.ino` - Main code
- `platformio.ini` - Build config
- `config.h` - Settings
- All `.h` header files

**Extract to:** `c:/Users/Holle/Desktop/volt v5.00 flash`

---

## 🎯 After Everything is Ready

1. **Open VSCode**
2. **Open folder:** `c:/Users/Holle/Desktop/volt v5.00 flash`
3. **Verify** PlatformIO extension is installed
4. **Look at bottom blue bar**
5. **Click** the **→** (Upload) icon
6. **If prompted**, hold BOOT button during upload

---

## 📞 Quick Command Reference

### Check if driver installed:

```powershell
Get-WmiObject Win32_PnpSignedDriver | Where-Object { $_.DeviceName -match 'CP210x' }
```

### Check COM ports:

```powershell
[System.IO.Ports.SerialPort]::getportnames()
```

### Check USB devices:

```powershell
Get-PnpDevice -PresentOnly | Where-Object { $_.Class -eq 'Ports' }
```

---

## ✅ Success Indicators

**You'll know it's working when:**

1. ✅ Device Manager shows COM port with no errors
2. ✅ PowerShell command shows COM3 (or similar)
3. ✅ Watch screen turns on when plugged in
4. ✅ PlatformIO can detect the device
5. ✅ Upload button in VSCode is clickable

---

## 🎉 You're Almost There!

The main issue is the **missing CP210x driver**. Once installed:

- Windows will recognize the watch
- A COM port will appear
- You can flash the firmware

**Download the driver now and restart your computer!**

Driver link: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers

---

**Good luck!** ⚡💙
