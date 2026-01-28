# 🔧 WiFi Troubleshooting Guide for HU-087 Watch

## ❌ Problem: Device Not Showing Up on Network

You're experiencing this because the WiFi credentials in `config_stone_FINAL.h` are still set to placeholder values.

---

## ✅ SOLUTION: Configure WiFi Credentials

### Step 1: Open Configuration File

Open `config_stone_FINAL.h` and find these lines (around line 27-28):

```cpp
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
```

### Step 2: Replace with YOUR Actual WiFi Credentials

**IMPORTANT:** Only 2.4GHz WiFi networks work! ESP32 does NOT support 5GHz.

```cpp
const char* WIFI_SSID = "YourActualWiFiName";      // Replace with your 2.4GHz WiFi name
const char* WIFI_PASSWORD = "YourActualPassword";   // Replace with your WiFi password
```

**Example:**
```cpp
const char* WIFI_SSID = "HomeNetwork_2.4G";
const char* WIFI_PASSWORD = "MySecurePassword123";
```

### Step 3: Save and Re-flash

1. Save the file
2. Re-compile and flash to the watch
3. The watch should now connect to your WiFi network

---

## 🔍 How to Verify WiFi Connection

### Method 1: Serial Monitor (Recommended)

1. Open Arduino IDE Serial Monitor (115200 baud)
2. Reset the watch
3. Look for these messages:

```
WiFi: Connecting to YourWiFiName
.....
WiFi: Connected!
WiFi: IP address: 192.168.1.XXX
```

### Method 2: Check Your Router

1. Log into your router's admin panel
2. Look for connected devices
3. Search for "ESP32" or the IP address shown on the watch display

### Method 3: Watch Display

The watch display will show:
- **Green "WiFi Connected!"** = Success ✅
- **Yellow "WiFi Failed"** = Connection problem ❌

---

## 🚨 Common WiFi Issues & Fixes

### Issue 1: "WiFi Failed" Message

**Possible Causes:**
- ❌ Wrong WiFi credentials
- ❌ Using 5GHz WiFi (ESP32 only supports 2.4GHz)
- ❌ WiFi network too far away
- ❌ Special characters in password not escaped properly

**Solutions:**
1. Double-check SSID and password (case-sensitive!)
2. Ensure you're using a 2.4GHz network
3. Move closer to the router during initial setup
4. If password has quotes, escape them: `\"` instead of `"`

### Issue 2: Connects Then Disconnects

**Possible Causes:**
- ❌ Weak signal strength
- ❌ Router DHCP issues
- ❌ Power management issues

**Solutions:**
1. Check signal strength in Serial Monitor (RSSI value)
2. Reserve an IP address for the watch in your router
3. Disable deep sleep temporarily:
   ```cpp
   const bool ENABLE_DEEP_SLEEP = false;
   ```

### Issue 3: Can't See Device on Network

**Possible Causes:**
- ❌ Device connected but not visible
- ❌ Network isolation enabled on router
- ❌ Different subnet

**Solutions:**
1. Check Serial Monitor for the assigned IP address
2. Disable AP isolation in router settings
3. Try pinging the IP address shown in Serial Monitor

### Issue 4: Special WiFi Network Types

**WPA2-Enterprise Networks (School/Work):**
- ❌ NOT SUPPORTED - ESP32 basic WiFi only supports WPA/WPA2-PSK
- ✅ Use personal hotspot or home network instead

**Hidden Networks:**
- ✅ Should work, but may need additional configuration
- Add this before `WiFi.begin()`:
  ```cpp
  WiFi.begin(wifiSSID, wifiPassword, 0, NULL, true);
  ```

---

## 🛠️ Alternative: Use AP Setup Mode

If you can't get WiFi working, use the built-in AP setup mode:

### Step 1: Activate AP Mode
Press the button **5 times quickly** on the watch

### Step 2: Connect to Watch's WiFi
1. On your phone/computer, look for WiFi network: **VOLT-Setup**
2. Password: **volt2024**
3. Connect to it

### Step 3: Configure WiFi
1. Open browser and go to: **192.168.4.1**
2. Enter your WiFi credentials
3. Watch will restart and connect

**Note:** The web interface for AP mode needs to be implemented. For now, manually edit the config file.

---

## 📊 WiFi Diagnostics Code

Add this to your `setup()` function for detailed WiFi diagnostics:

```cpp
void printWiFiDiagnostics() {
    Serial.println("\n=== WiFi Diagnostics ===");
    Serial.println("SSID: " + String(WIFI_SSID));
    Serial.println("Password Length: " + String(strlen(WIFI_PASSWORD)));
    Serial.println("WiFi Mode: " + String(WiFi.getMode()));
    Serial.println("Status: " + String(WiFi.status()));
    
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

Call it after attempting to connect:
```cpp
wifiMgr.connect(WIFI_SSID, WIFI_PASSWORD, WIFI_TIMEOUT);
printWiFiDiagnostics();
```

---

## 🔢 WiFi Status Codes

| Code | Status | Meaning |
|------|--------|---------|
| 0 | WL_IDLE_STATUS | WiFi is idle |
| 1 | WL_NO_SSID_AVAIL | SSID not found |
| 3 | WL_CONNECTED | ✅ Connected! |
| 4 | WL_CONNECT_FAILED | Wrong password |
| 6 | WL_DISCONNECTED | Disconnected |

---

## 📝 Quick Checklist

Before asking for help, verify:

- [ ] WiFi credentials are correct (not placeholder values)
- [ ] Using 2.4GHz WiFi network (not 5GHz)
- [ ] Password is correct (case-sensitive)
- [ ] Watch is within range of router
- [ ] Serial Monitor shows connection attempts
- [ ] Router allows new device connections
- [ ] No special characters causing issues in password

---

## 🆘 Still Not Working?

### Enable Verbose Logging

In `config_stone_FINAL.h`:
```cpp
const bool VERBOSE_LOGGING = true;
```

### Test with Mobile Hotspot

1. Create a 2.4GHz hotspot on your phone
2. Use simple SSID and password (no special characters)
3. Try connecting the watch to the hotspot
4. If this works, the issue is with your home router settings

### Factory Reset ESP32

If all else fails:
```cpp
// Add to setup()
WiFi.disconnect(true);  // Disconnect and erase stored credentials
delay(1000);
```

---

## 📞 Getting Help

When asking for help, provide:
1. Serial Monitor output (full log from startup)
2. Your WiFi router model
3. Network type (WPA2, WPA3, etc.)
4. Whether mobile hotspot works
5. Any error messages from compilation

---

## ✅ Success Indicators

You'll know WiFi is working when you see:

**Serial Monitor:**
```
WiFi: Connecting to YourNetwork
.....
WiFi: Connected!
WiFi: IP address: 192.168.1.123
AI: Ready
```

**Watch Display:**
- Green "WiFi Connected!" message
- "Ready to talk!" on idle screen
- IP address visible in status

**Router:**
- Device appears in connected devices list
- Can ping the IP address

---

## 🎯 Next Steps After WiFi Works

Once connected:
1. Test voice chat (1 button press)
2. Verify OpenAI API key is configured
3. Test all features
4. Check battery life with WiFi enabled

Good luck! 🚀
