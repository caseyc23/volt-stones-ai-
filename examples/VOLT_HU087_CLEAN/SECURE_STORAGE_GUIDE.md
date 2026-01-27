# 🔐 VOLT Secure Storage System

## Safe Credential Management for Stone

---

## 🎯 Overview

VOLT now has a **Secure Key Box** that safely stores:

- 🔑 API keys (OpenAI, Hugging Face, etc.)
- 📡 WiFi passwords (multiple networks)
- ⚙️ User preferences
- 🔒 All data encrypted in ESP32's secure storage

---

## ✨ Features

### **1. Secure API Key Storage**

- Store multiple API keys safely
- Encrypted storage (not visible in code)
- Easy to add/update/delete keys
- Survives firmware updates

### **2. WiFi Network Management**

- Scan for available networks
- Save up to 5 WiFi networks
- Auto-connect to saved networks
- Visual network selector
- Signal strength display

### **3. Auto-Connect on Startup**

- VOLT scans for WiFi on boot
- Automatically connects to strongest saved network
- Falls back to next network if first fails
- Shows connection status on screen

---

## 🚀 How It Works

### **First Time Setup:**

1. **VOLT boots up**
2. **Scans for WiFi networks**
3. **Shows list on screen**
4. **Stone (or Dad) selects network**
5. **Enters password via web interface**
6. **VOLT saves credentials securely**
7. **Connects to WiFi**

### **Every Boot After:**

1. **VOLT boots up**
2. **Checks for saved networks**
3. **Scans for available networks**
4. **Auto-connects to strongest saved network**
5. **Ready to use!**

---

## 📱 Using the Secure Storage

### **Saving WiFi Networks:**

```cpp
// In your code
SecureStorage storage;
storage.begin();

// Save a WiFi network
storage.saveWiFiNetwork("Home-WiFi", "mypassword123");
storage.saveWiFiNetwork("School-WiFi", "schoolpass456");

// VOLT will auto-connect to these on next boot!
```

### **Saving API Keys:**

```cpp
// Save OpenAI key
storage.saveAPIKey("openai", "sk-your-key-here");

// Save Hugging Face key
storage.saveAPIKey("huggingface", "hf-your-key-here");

// Save Spotify credentials
storage.saveAPIKey("spotify_id", "your-client-id");
storage.saveAPIKey("spotify_secret", "your-client-secret");

// Retrieve later
String openaiKey = storage.getAPIKey("openai");
```

### **Managing Networks:**

```cpp
// Get all saved networks
String networks[5];
int count = storage.getSavedNetworks(networks, 5);

// Delete a network
storage.deleteWiFiNetwork("Old-WiFi");

// Clear everything (factory reset)
storage.clearAll();
```

---

## 🔧 WiFi Scanner Features

### **Network Display:**

```
WiFi Networks:
━━━━━━━━━━━━━━━━━━
→ Home-WiFi        🔒 ✓
  ▮▮▮▮ (Strong)

  School-WiFi      🔒 ✓
  ▮▮▮ (Good)

  Coffee-Shop
  ▮▮ (Weak)
━━━━━━━━━━━━━━━━━━
Press to select
```

**Legend:**

- `→` = Selected network
- `🔒` = Password protected
- `✓` = Saved (will auto-connect)
- `▮▮▮▮` = Signal strength

### **Auto-Connect Process:**

```
1. Scanning WiFi...
   ↓
2. Found 8 networks
   ↓
3. Checking saved networks...
   ↓
4. Connecting to: Home-WiFi
   ↓
5. Connected! ✓
```

---

## 🎮 Button Controls

### **WiFi Setup Mode (5 presses):**

1. Press button 5 times quickly
2. VOLT enters WiFi setup
3. Shows available networks
4. Press to cycle through networks
5. Long press to select
6. Enter password via web interface
7. VOLT saves and connects

---

## 🔒 Security Features

### **Encryption:**

- All data stored in ESP32's encrypted NVS (Non-Volatile Storage)
- Unique encryption key per device
- Data survives power loss
- Protected from casual inspection

### **Access Control:**

- Only VOLT firmware can access stored data
- No external access without physical device
- Secure erase available (factory reset)

### **Privacy:**

- Passwords never displayed on screen
- API keys never logged to serial
- Secure transmission only (HTTPS)

---

## 📊 Storage Capacity

| Item          | Limit       | Current |
| ------------- | ----------- | ------- |
| WiFi Networks | 5           | 0       |
| API Keys      | Unlimited\* | 0       |
| Preferences   | Unlimited\* | 0       |

\*Limited by ESP32 NVS space (~512KB total)

---

## 🛠️ Advanced Usage

### **Checking Storage:**

```cpp
// Print storage info
storage.printStorageInfo();

// Output:
// === Secure Storage Info ===
// WiFi Networks: 2/5
//   1. Home-WiFi
//   2. School-WiFi
// ===========================
```

### **Preferences:**

```cpp
// Save user preferences
storage.savePref("voice", "echo");
storage.savePref("volume", "80");
storage.savePrefInt("brightness", 200);

// Retrieve
String voice = storage.getPref("voice", "echo");
int brightness = storage.getPrefInt("brightness", 200);
```

### **Factory Reset:**

```cpp
// Clear ALL stored data
storage.clearAll();

// VOLT will be like new:
// - No saved WiFi networks
// - No saved API keys
// - No preferences
// - Will need setup again
```

---

## 🎯 Integration with VOLT

### **In volt_stone.ino:**

```cpp
#include "secure_storage.h"
#include "wifi_scanner.h"

SecureStorage storage;
WiFiScanner scanner(&display, &storage);

void setup() {
    // Initialize secure storage
    storage.begin();

    // Try auto-connect
    if (!scanner.autoConnect(20)) {
        // No saved networks or connection failed
        // Show network selector
        scanner.scanNetworks();
        scanner.displayNetworks();
        // Wait for user selection...
    }

    // Load API keys from storage
    String openaiKey = storage.getAPIKey("openai");
    if (openaiKey.length() > 0) {
        bot.begin(openaiKey.c_str(), STONE_PERSONALITY);
    }
}
```

---

## 💡 Use Cases

### **1. Multiple Locations:**

```
Stone's watch automatically connects to:
- Home WiFi (when at home)
- School WiFi (when at school)
- Grandma's WiFi (when visiting)
- Dad's phone hotspot (when traveling)
```

### **2. API Key Management:**

```
Dad can easily:
- Add new API keys as services are enabled
- Update keys when they expire
- Switch between different AI providers
- Test different services
```

### **3. Personalization:**

```
Stone's preferences saved:
- Favorite voice (echo, nova, etc.)
- Volume level
- Display brightness
- Preferred features
```

---

## 🔐 Best Practices

### **For Dad:**

1. **Use Strong Passwords**
   - Mix letters, numbers, symbols
   - Different for each network
   - Change periodically

2. **Protect API Keys**
   - Don't share keys
   - Set spending limits
   - Monitor usage
   - Rotate keys periodically

3. **Regular Backups**
   - Note down saved networks
   - Keep API keys in password manager
   - Document preferences

### **For Stone:**

1. **WiFi Safety**
   - Only connect to known networks
   - Ask Dad before new networks
   - Don't share passwords

2. **Device Security**
   - Keep watch with you
   - Don't let others use it
   - Tell Dad if lost

---

## 🆘 Troubleshooting

### **WiFi Won't Connect:**

```
1. Check if network is in range
2. Verify password is correct
3. Try deleting and re-adding network
4. Check if network is 2.4GHz (not 5GHz)
5. Restart VOLT
```

### **Can't Save Network:**

```
1. Check if storage is full (5 network limit)
2. Delete old networks
3. Try factory reset if needed
```

### **API Keys Not Working:**

```
1. Verify key is correct
2. Check key hasn't expired
3. Ensure billing is active
4. Try re-entering key
```

---

## 📝 Example Workflow

### **Setting Up VOLT for Stone:**

```
Day 1 - At Home:
1. Flash VOLT firmware
2. Boot up watch
3. VOLT scans WiFi
4. Select "Home-WiFi"
5. Enter password via web
6. VOLT saves and connects
7. Add OpenAI API key
8. Test voice chat
9. Give to Stone!

Day 2 - At School:
1. Stone arrives at school
2. VOLT tries Home-WiFi (not in range)
3. Shows "No WiFi" message
4. Dad helps add School-WiFi
5. VOLT saves it
6. Now auto-connects at school!

Day 3 - At Home:
1. Stone comes home
2. VOLT auto-connects to Home-WiFi
3. Works perfectly!
4. No setup needed!
```

---

## 🎉 Benefits

### **For Stone:**

- ✅ WiFi "just works" everywhere
- ✅ No complicated setup
- ✅ Seamless experience
- ✅ Always connected

### **For Dad:**

- ✅ Easy to manage
- ✅ Secure storage
- ✅ Flexible configuration
- ✅ Peace of mind

---

## 🔮 Future Enhancements

Possible additions:

- 📱 Mobile app for credential management
- 🌐 Cloud backup of settings
- 🔄 Sync between multiple VOLT devices
- 🎯 Location-based auto-connect
- 📊 Network usage statistics
- 🔔 Notifications for weak signals

---

## ✅ Quick Reference

### **Common Commands:**

```cpp
// WiFi
storage.saveWiFiNetwork(ssid, password);
storage.getWiFiPassword(ssid);
storage.deleteWiFiNetwork(ssid);

// API Keys
storage.saveAPIKey(service, key);
storage.getAPIKey(service);
storage.deleteAPIKey(service);

// Preferences
storage.savePref(key, value);
storage.getPref(key, default);

// Utility
storage.printStorageInfo();
storage.clearAll();
```

---

**Made with ❤️ by Dad for Stone**

_Secure, simple, and always connected!_
