# 🚀 GET YOUR HU-087 WATCH ONLINE - Complete Guide

## 📋 Quick Summary

Your watch isn't showing up on the network because **WiFi credentials are not configured**. This is a 2-minute fix!

---

## ⚡ FASTEST FIX (2 Minutes)

### Step 1: Edit Configuration File

Open: `config_stone_FINAL.h`

Find these lines (around line 27-28):
```cpp
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
```

Replace with YOUR actual WiFi credentials:
```cpp
const char* WIFI_SSID = "YourActualWiFiName";      // ← Change this
const char* WIFI_PASSWORD = "YourActualPassword";   // ← Change this
```

### Step 2: Flash to Watch

1. Save the file
2. Click "Upload" in Arduino IDE
3. Wait for completion
4. Done! ✅

---

## ⚠️ CRITICAL REQUIREMENT

**Your WiFi MUST be 2.4GHz!**

ESP32 does NOT support 5GHz WiFi networks.

### How to Check Your WiFi Band:

**Option 1: Router Settings**
- Log into your router (usually 192.168.1.1 or 192.168.0.1)
- Look for "2.4GHz" network settings
- Some routers have separate SSIDs for 2.4GHz and 5GHz

**Option 2: Phone Settings**
- On Android: WiFi → Network Details → Frequency
- On iPhone: Not directly visible, but if network name has "5G" or "5GHz", it won't work

**Option 3: Create a 2.4GHz Hotspot**
- Use your phone as a temporary hotspot
- Set it to 2.4GHz in hotspot settings
- Test with the watch

---

## ✅ How to Verify It's Working

### Serial Monitor Output (Best Method)

Open Serial Monitor at 115200 baud and look for:

```
=== VOLT for Stone - Starting ===
WiFi: Connecting to YourWiFiName
.....
WiFi: Connected!
WiFi: IP address: 192.168.1.123  ← Your watch's IP!
AI: Ready
=== VOLT Ready for Stone ===
```

### Watch Display

You'll see:
- ✅ Green "WiFi Connected!" message during startup
- ✅ "Ready to talk!" on the idle screen
- ✅ Green WiFi status indicator

### Router Admin Panel

1. Log into your router
2. Check connected devices
3. Look for "ESP32" or the IP shown on watch

---

## 🔧 Troubleshooting Common Issues

### Issue 1: "WiFi Failed" on Watch Display

**Causes:**
- Wrong WiFi credentials (typo in SSID or password)
- Using 5GHz network instead of 2.4GHz
- WiFi signal too weak
- Special characters in password not handled correctly

**Solutions:**
1. Double-check SSID and password (case-sensitive!)
2. Verify you're using 2.4GHz network
3. Move watch closer to router during setup
4. Try a simpler password temporarily

### Issue 2: Connects Then Immediately Disconnects

**Causes:**
- Weak signal strength
- Router rejecting device
- Power management issues

**Solutions:**
1. Check signal strength (RSSI) in Serial Monitor
2. Disable MAC filtering on router temporarily
3. Reserve IP address for watch in router DHCP settings
4. Disable deep sleep temporarily:
   ```cpp
   const bool ENABLE_DEEP_SLEEP = false;
   ```

### Issue 3: Can't See Device on Network

**Causes:**
- AP isolation enabled on router
- Device on different subnet
- Firewall blocking device

**Solutions:**
1. Disable AP isolation in router settings
2. Check the IP address shown in Serial Monitor
3. Try pinging the IP address from your computer
4. Temporarily disable router firewall

### Issue 4: Special Characters in Password

If your WiFi password has quotes or special characters:

**Wrong:**
```cpp
const char* WIFI_PASSWORD = "My"Password"123";  // Syntax error!
```

**Correct:**
```cpp
const char* WIFI_PASSWORD = "My\"Password\"123";  // Escape quotes
```

Or just change your WiFi password to something simpler for testing.

---

## 📱 Test with Mobile Hotspot

If you're having trouble with your home WiFi, test with a phone hotspot:

1. **Create Hotspot on Phone:**
   - Enable mobile hotspot
   - Set to 2.4GHz (check phone settings)
   - Use simple name and password (no special characters)
   - Example: SSID="TestHotspot", Password="test1234"

2. **Update Config:**
   ```cpp
   const char* WIFI_SSID = "TestHotspot";
   const char* WIFI_PASSWORD = "test1234";
   ```

3. **Flash and Test:**
   - Upload to watch
   - Watch should connect immediately
   - If this works → problem is with home router settings
   - If this fails → check hardware or code issues

---

## 🔍 Advanced Diagnostics

### Add WiFi Diagnostics to Your Code

Add this function to `volt_stone_FINAL.ino`:

```cpp
void printWiFiDiagnostics() {
    Serial.println("\n=== WiFi Diagnostics ===");
    Serial.println("SSID: " + String(WIFI_SSID));
    Serial.println("Password Length: " + String(strlen(WIFI_PASSWORD)));
    Serial.println("WiFi Status: " + String(WiFi.status()));
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("✅ CONNECTED");
        Serial.println("IP: " + WiFi.localIP().toString());
        Serial.println("Gateway: " + WiFi.gatewayIP().toString());
        Serial.println("Subnet: " + WiFi.subnetMask().toString());
        Serial.println("DNS: " + WiFi.dnsIP().toString());
        Serial.println("RSSI: " + String(WiFi.RSSI()) + " dBm");
        Serial.println("Channel: " + String(WiFi.channel()));
    } else {
        Serial.println("❌ NOT CONNECTED");
        Serial.println("Error Code: " + String(WiFi.status()));
    }
    Serial.println("=======================\n");
}
```

Call it in `setup()` after WiFi connection attempt:
```cpp
wifiMgr.connect(WIFI_SSID, WIFI_PASSWORD, WIFI_TIMEOUT);
printWiFiDiagnostics();  // Add this line
```

### WiFi Status Codes

| Code | Constant | Meaning |
|------|----------|---------|
| 0 | WL_IDLE_STATUS | WiFi is idle |
| 1 | WL_NO_SSID_AVAIL | SSID not found (wrong name or out of range) |
| 3 | WL_CONNECTED | ✅ Successfully connected! |
| 4 | WL_CONNECT_FAILED | Wrong password or authentication failed |
| 6 | WL_DISCONNECTED | Disconnected from network |

---

## 📝 Configuration Examples

### Example 1: Simple Home WiFi
```cpp
const char* WIFI_SSID = "HomeNetwork";
const char* WIFI_PASSWORD = "password123";
```

### Example 2: WiFi with Spaces
```cpp
const char* WIFI_SSID = "My Home WiFi";  // Spaces in SSID are OK
const char* WIFI_PASSWORD = "MyPassword";
```

### Example 3: Dual-Band Router (Separate Networks)
```cpp
const char* WIFI_SSID = "MyRouter-2.4G";  // Use the 2.4GHz network
const char* WIFI_PASSWORD = "RouterPass123";
```

### Example 4: Mobile Hotspot
```cpp
const char* WIFI_SSID = "iPhone";
const char* WIFI_PASSWORD = "hotspot123";
```

---

## 🎯 What Works After WiFi Connects?

**Online Features (Require WiFi):**
- ✅ GPT-4 AI conversations
- ✅ Voice recognition (Whisper)
- ✅ Text-to-speech (OpenAI TTS)
- ✅ AI-generated jokes
- ✅ Auto-reconnect if connection drops

**Offline Features (Work Without WiFi):**
- ✅ Pre-loaded jokes
- ✅ Breathing exercises
- ✅ Dad's love messages
- ✅ All button controls
- ✅ Display functions

---

## 🔐 Security Notes

**WiFi Credentials:**
- Stored in plain text in config file
- Not encrypted on device
- Don't share your config file publicly
- Consider using a guest network for IoT devices

**Best Practices:**
- Use WPA2 or WPA3 encryption on router
- Don't use WEP (outdated and insecure)
- Consider creating a separate IoT network
- Use strong, unique password

---

## 📞 Still Need Help?

### Before Asking for Help, Provide:

1. **Serial Monitor Output:**
   - Full log from device startup
   - Include all WiFi connection messages

2. **Your Setup:**
   - Router model and brand
   - WiFi security type (WPA2, WPA3, etc.)
   - Whether mobile hotspot works

3. **What You've Tried:**
   - Configuration changes made
   - Troubleshooting steps attempted
   - Any error messages

### Additional Resources:

- **QUICK_WIFI_FIX.md** - Ultra-fast 2-minute fix guide
- **WIFI_TROUBLESHOOTING_GUIDE.md** - Detailed troubleshooting
- **config_stone_EXAMPLE.h** - Example configuration file

---

## ✅ Success Checklist

Before considering the issue resolved, verify:

- [ ] WiFi credentials updated in config file
- [ ] Using 2.4GHz WiFi network (not 5GHz)
- [ ] Code compiles without errors
- [ ] Uploaded to watch successfully
- [ ] Serial Monitor shows "WiFi: Connected!"
- [ ] Watch display shows green "WiFi Connected!"
- [ ] IP address visible in Serial Monitor
- [ ] Can ping the watch's IP address
- [ ] Voice chat works (1 button press)
- [ ] AI responses working

---

## 🎉 You're All Set!

Once WiFi is connected, your watch can:
- Have conversations with GPT-4
- Tell AI-generated jokes
- Provide voice responses
- Auto-reconnect if WiFi drops
- Show connection status on display

**Enjoy your VOLT AI companion watch! 🚀**

---

*Last Updated: 2025-01-25*
*For Stone's HU-087 Watch*
