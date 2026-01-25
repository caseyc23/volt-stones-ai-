# ⚡ VOLT v5.00 - WiFi Manager & API Edition

**Welcome to VOLT v5.00!** This firmware adds comprehensive WiFi management and API capabilities to your VOLT watch.

---

## 🚀 Quick Start - Flash Your Watch

### **3 Simple Steps:**

1. **Open this folder in VSCode**
   - File → Open Folder
   - Select: `volt v5.00 flash`

2. **Connect your watch**
   - Plug USB cable into watch and computer

3. **Click Upload**
   - Look at the **bottom of VSCode** (blue bar)
   - Click the **→** (right arrow) icon
   - Wait 1-2 minutes

**Done!** Your watch will reboot with v5.00 installed.

📖 **Need detailed instructions?** See [HOW_TO_FLASH.md](HOW_TO_FLASH.md)

---

## 🆕 What's New in v5.00

### WiFi Features:

✅ **WiFi API Key Access** - Manage OpenAI API remotely  
✅ **WiFi Network Sniffing** - Scan for available networks  
✅ **Add WiFi by Password** - Store up to 5 networks  
✅ **Automatic Fallback** - Switches to backup networks  
✅ **Web Interface** - Easy browser-based setup  
✅ **REST API** - Full remote control

### New Button Control:

- **5 quick presses** = Enter WiFi setup mode ⭐

---

## 📱 First Time WiFi Setup

After flashing, your watch will automatically enter **WiFi Setup Mode**:

1. **On your phone**, connect to WiFi: `VOLT-Setup-XXXX`
2. **Password:** `volt2024`
3. **Open browser** to: `http://192.168.4.1`
4. **Scan for networks** and add your WiFi
5. **Enter password** and save
6. **Restart watch** - Done!

📖 **Full WiFi setup guide:** [WIFI_SETUP_GUIDE.md](WIFI_SETUP_GUIDE.md)

---

## 🎤 Voice Information

**Current Voice:** ECHO (warm, conversational male voice)

### All Available Voices:

1. **ECHO** ⭐ (Current) - Male, warm, conversational
2. **NOVA** - Female, bright, energetic
3. **FABLE** - Male, warm, storytelling
4. **SHIMMER** - Female, soft, gentle
5. **ALLOY** - Neutral, smooth
6. **ONYX** - Male, deep, authoritative

📖 **Change voices:** [VOICE_OPTIONS.md](VOICE_OPTIONS.md)

---

## 🎮 Button Controls

| Presses        | Action                      |
| -------------- | --------------------------- |
| 1              | Talk to VOLT                |
| 2              | Tell a joke                 |
| 3              | Breathing exercise          |
| 4 (long press) | Emergency love message      |
| **5**          | **WiFi setup mode** ⭐ NEW! |

---

## 📚 Documentation Files

### Getting Started:

- **[README.md](README.md)** ⭐ You are here!
- **[HOW_TO_FLASH.md](HOW_TO_FLASH.md)** - Simple flashing guide
- **[VOICE_OPTIONS.md](VOICE_OPTIONS.md)** - Voice configuration

### WiFi & API:

- **[WIFI_SETUP_GUIDE.md](WIFI_SETUP_GUIDE.md)** - WiFi setup instructions
- **[WIFI_API_DOCUMENTATION.md](WIFI_API_DOCUMENTATION.md)** - Complete API reference
- **[WIFI_IMPLEMENTATION_SUMMARY.md](WIFI_IMPLEMENTATION_SUMMARY.md)** - Technical details

### Testing:

- **[HARDWARE_TESTING_CHECKLIST.md](HARDWARE_TESTING_CHECKLIST.md)** - Testing guide

### Advanced:

- **[VSCODE_FLASHING_GUIDE.md](VSCODE_FLASHING_GUIDE.md)** - Detailed flashing instructions

---

## 🌐 Web Interface Features

Once connected (via AP mode or your WiFi), access the web interface:

### In AP Mode:

- URL: `http://192.168.4.1`

### On Your WiFi:

- URL: `http://<VOLT_IP_ADDRESS>`

### Features:

- 📶 Scan for WiFi networks
- ➕ Add new networks
- 💾 View stored networks
- ℹ️ Check device status
- 🔧 Manage settings

---

## 🔌 REST API Endpoints

All endpoints require authentication with password: `volt2024`

### Available Endpoints:

- `GET /api/wifi/scan` - Scan for networks
- `GET /api/wifi/list` - List stored networks
- `POST /api/wifi/add` - Add new network
- `DELETE /api/wifi/remove` - Remove network
- `GET /api/status` - Device status

### Example:

```bash
curl -H "Authorization: volt2024" http://192.168.4.1/api/wifi/scan
```

📖 **Full API documentation:** [WIFI_API_DOCUMENTATION.md](WIFI_API_DOCUMENTATION.md)

---

## 🔧 Configuration Files

### Main Files:

- `volt_firmware.ino` - Main firmware code
- `config.h` - Configuration settings
- `wifi_manager.h` - WiFi management
- `web_api.h` - REST API server
- `voice.h` - Voice settings
- `memory.h` - Storage management
- `content.h` - Messages and content
- `pins.h` - Hardware pin definitions

### To Change Settings:

1. Open the file in VSCode
2. Edit the values
3. Save (Ctrl+S)
4. Re-flash to watch

---

## ⚙️ Quick Configuration

### Change WiFi (Before Flashing):

Edit `config.h`:

```cpp
const char* WIFI_SSID = "YourWiFiName";
const char* WIFI_PASSWORD = "YourPassword";
```

### Change OpenAI API Key:

Edit `config.h`:

```cpp
const char* OPENAI_API_KEY = "sk-your-api-key-here";
```

### Change Voice:

Edit `voice.h`:

```cpp
const char* TTS_VOICE = "echo";  // or nova, fable, shimmer, alloy, onyx
```

### Change Child's Name:

Edit `config.h`:

```cpp
const char* CHILD_NAME = "Stone";
const int CHILD_AGE = 8;
```

---

## 🧪 Testing Your Watch

After flashing, use the comprehensive testing checklist:

📖 **[HARDWARE_TESTING_CHECKLIST.md](HARDWARE_TESTING_CHECKLIST.md)**

This covers:

- ✅ Flash process
- ✅ WiFi functionality
- ✅ Web interface
- ✅ API endpoints
- ✅ Voice & AI
- ✅ Button patterns
- ✅ Display & hardware
- ✅ Memory & storage
- ✅ Power & stability

---

## 🆘 Troubleshooting

### Can't Flash?

- Hold BOOT button while clicking Upload
- Try different USB port/cable
- Install CP210x drivers

### WiFi Won't Connect?

- Check SSID and password (case-sensitive!)
- Ensure 2.4GHz WiFi (not 5GHz)
- Move closer to router

### Web Interface Won't Load?

- Make sure you're connected to VOLT's WiFi
- Try `http://192.168.4.1` (not https)
- Clear browser cache

### API Returns 401?

- Include Authorization header
- Password: `volt2024`
- Format: `Authorization: volt2024`

📖 **More help:** [WIFI_SETUP_GUIDE.md](WIFI_SETUP_GUIDE.md) - Troubleshooting section

---

## 📊 Technical Specifications

### Firmware:

- **Version:** 5.00
- **Platform:** ESP32-S3
- **Framework:** Arduino
- **Build System:** PlatformIO

### WiFi:

- **Networks:** Up to 5 stored
- **Modes:** Station + Access Point
- **Security:** WPA/WPA2/WPA3
- **Frequency:** 2.4GHz only

### API:

- **Protocol:** REST (HTTP)
- **Format:** JSON
- **Authentication:** Password-based
- **Port:** 80

### Voice:

- **Current:** ECHO (male, warm)
- **Options:** 6 voices available
- **Speed:** 1.08x (adjustable)
- **Quality:** HD (tts-1-hd)

### AI:

- **Model:** GPT-4o-mini
- **STT:** Whisper-1
- **TTS:** OpenAI TTS
- **Max Response:** 150 tokens

---

## 📁 Folder Structure

```
volt v5.00 flash/
├── README.md ⭐ (You are here!)
├── HOW_TO_FLASH.md
├── VOICE_OPTIONS.md
├── WIFI_SETUP_GUIDE.md
├── WIFI_API_DOCUMENTATION.md
├── WIFI_IMPLEMENTATION_SUMMARY.md
├── HARDWARE_TESTING_CHECKLIST.md
├── VSCODE_FLASHING_GUIDE.md
├── volt_firmware.ino (Main firmware)
├── config.h (Settings)
├── wifi_manager.h (WiFi management)
├── web_api.h (REST API)
├── voice.h (Voice settings)
├── memory.h (Storage)
├── content.h (Messages)
├── pins.h (Hardware)
├── platformio.ini (Build config)
└── ... (other files)
```

---

## ✨ Features Summary

### WiFi Management:

✅ Multi-network storage (5 max)  
✅ Priority-based connection  
✅ Automatic fallback  
✅ Network scanning  
✅ Signal strength display  
✅ Access Point mode

### Web Interface:

✅ Mobile-friendly design  
✅ Network scanning  
✅ Easy network addition  
✅ Device status display  
✅ Password-protected

### REST API:

✅ Full WiFi control  
✅ JSON responses  
✅ Authentication  
✅ Device monitoring  
✅ Remote management

### Voice & AI:

✅ 6 voice options  
✅ Natural conversation  
✅ Speech recognition  
✅ AI responses  
✅ Text-to-speech

### Hardware:

✅ Button patterns  
✅ LED indicators  
✅ Display messages  
✅ Sleep mode  
✅ Battery monitoring

---

## 🎯 Next Steps

1. **Flash the firmware** (see HOW_TO_FLASH.md)
2. **Set up WiFi** (automatic AP mode or manual config)
3. **Test features** (use HARDWARE_TESTING_CHECKLIST.md)
4. **Customize settings** (edit config.h, voice.h)
5. **Enjoy VOLT!** ⚡💙

---

## 💡 Pro Tips

1. **Change default passwords** in config.h for security
2. **Add multiple WiFi networks** for home, work, school
3. **Try different voices** to find Stone's favorite
4. **Use the API** for advanced automation
5. **Keep firmware updated** for new features

---

## 📞 Support

### Documentation:

- All guides included in this folder
- Check README.md for overview
- See specific guides for details

### Testing:

- Use HARDWARE_TESTING_CHECKLIST.md
- Test all features after flashing
- Report any issues found

### Updates:

- Check for firmware updates
- Re-flash to update
- Settings are preserved

---

## 🎉 Ready to Flash!

Everything you need is in this folder:

- ✅ Firmware v5.00
- ✅ Complete documentation
- ✅ Testing checklist
- ✅ Configuration files
- ✅ All features working

**Open this folder in VSCode and click the Upload button to get started!**

---

**Version:** 5.00 - WiFi Manager & API Edition  
**Created:** 2024  
**For:** Stone's VOLT Watch  
**Status:** ✅ Ready to Flash

**Made with love** 💙 **by Dad**

---

## 📖 Quick Links

- [How to Flash](HOW_TO_FLASH.md) - Start here!
- [WiFi Setup](WIFI_SETUP_GUIDE.md) - Configure WiFi
- [Voice Options](VOICE_OPTIONS.md) - Change voice
- [API Docs](WIFI_API_DOCUMENTATION.md) - API reference
- [Testing](HARDWARE_TESTING_CHECKLIST.md) - Test checklist

**Happy flashing!** ⚡
