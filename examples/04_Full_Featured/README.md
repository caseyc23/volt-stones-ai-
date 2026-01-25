# VOLT Full Featured Example

This example includes ALL features of VOLT:

- ✅ WiFi connectivity with multi-network support
- ✅ OpenAI API integration (GPT-4, Whisper, TTS)
- ✅ Voice recognition and response
- ✅ Web interface and REST API
- ✅ OTA updates
- ✅ Deep sleep power management
- ✅ Watchdog timer
- ✅ Button patterns (1-5 presses)
- ✅ Display management
- ✅ Child safety features
- ✅ Crash recovery
- ✅ Battery monitoring

## Configuration Required

Before uploading, edit the configuration in the main file:

```cpp
// WiFi credentials
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_PASSWORD";

// OpenAI API
const char* OPENAI_API_KEY = "sk-YOUR_API_KEY_HERE";

// Child information
const char* CHILD_NAME = "Stone";
const int CHILD_AGE = 8;
```

## Features Included

### 1. WiFi Management

- Automatic connection to configured networks
- Fallback to AP mode if connection fails
- Network scanning and selection
- Signal strength monitoring

### 2. Voice & AI

- Press button to talk
- 5-second voice recording
- Speech-to-text via Whisper
- AI response via GPT-4
- Text-to-speech playback
- ECHO voice (warm, conversational)

### 3. Button Patterns

- **1 press**: Talk to VOLT
- **2 presses**: Tell a joke
- **3 presses**: Breathing exercise
- **4 presses (long)**: Emergency love message
- **5 presses**: WiFi setup mode

### 4. Web Interface

Access at `http://VOLT-IP-ADDRESS/`

- Network scanning
- Add/remove WiFi networks
- Device status
- Configuration

### 5. REST API

All endpoints require authentication:

```bash
# Scan networks
curl -H "Authorization: volt2024" http://VOLT-IP/api/wifi/scan

# Get status
curl -H "Authorization: volt2024" http://VOLT-IP/api/status
```

### 6. Power Management

- Automatic deep sleep after 5 minutes idle
- Wake on button press
- Battery monitoring
- Low battery warnings

### 7. OTA Updates

Update firmware over WiFi:

```bash
# Using Arduino IDE
Tools → Port → Network Ports → VOLT-Watch

# Using PlatformIO
pio run -t upload --upload-port VOLT-Watch.local
```

### 8. Safety Features

- Watchdog timer (30 second timeout)
- Crash recovery
- Safe mode on errors
- Parental controls
- Age-appropriate responses

## Upload Instructions

1. **Install dependencies** (if not already installed):
   - Adafruit GFX Library
   - Adafruit SSD1306
   - ArduinoJson
   - HTTPClient

2. **Configure settings** in the main .ino file

3. **Select board**: ESP32-S3 Dev Module

4. **Upload** via USB or OTA

5. **Monitor** serial output at 115200 baud

## First Boot

On first boot, VOLT will:

1. Show welcome screen
2. Try to connect to configured WiFi
3. If WiFi fails, enter AP mode
4. Display AP credentials on screen
5. Wait for configuration

## Troubleshooting

### WiFi won't connect

- Check SSID and password (case-sensitive)
- Ensure 2.4GHz network (not 5GHz)
- Move closer to router
- Check serial monitor for errors

### Voice not working

- Check OpenAI API key
- Verify internet connection
- Check microphone wiring
- Monitor serial output

### Display issues

- Check I2C address (usually 0x3C)
- Verify wiring (SDA, SCL)
- Try different display library

### OTA not working

- Ensure on same WiFi network
- Check firewall settings
- Verify OTA password
- Use IP address instead of hostname

## Performance Tips

1. **Battery Life**
   - Enable deep sleep
   - Reduce WiFi reconnection attempts
   - Lower display brightness
   - Disable unused features

2. **Response Speed**
   - Use faster WiFi network
   - Reduce AI response length
   - Cache common responses
   - Optimize audio quality

3. **Reliability**
   - Keep watchdog enabled
   - Monitor free heap
   - Handle all errors
   - Test thoroughly

## Advanced Customization

### Change Voice

Edit in main file:

```cpp
const char* TTS_VOICE = "echo";  // or nova, fable, shimmer, alloy, onyx
```

### Adjust AI Personality

Edit system prompt:

```cpp
const char* SYSTEM_PROMPT = "You are VOLT, a friendly AI companion...";
```

### Modify Button Actions

Edit button handler:

```cpp
void handleButtonPress(int pressCount) {
  switch(pressCount) {
    case 1: // Your custom action
    case 2: // Your custom action
    // ...
  }
}
```

## Support

For issues or questions:

1. Check serial monitor output
2. Review troubleshooting section
3. Test with simpler examples first
4. Check hardware connections

## License

This example is part of the VOLT AI Watch project.
Made with ❤️ for Stone by Dad.
