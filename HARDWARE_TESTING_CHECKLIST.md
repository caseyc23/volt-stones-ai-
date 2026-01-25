# 🧪 VOLT v5.00 Hardware Testing Checklist

Use this checklist after flashing the firmware to your watch to verify everything works correctly.

---

## ✅ Pre-Flash Checklist

Before flashing, verify:

- [ ] VSCode is installed
- [ ] PlatformIO extension is installed in VSCode
- [ ] USB cable is connected to watch and computer
- [ ] Watch powers on when connected
- [ ] Correct COM port is detected
- [ ] `config.h` has your WiFi credentials (optional - can use AP mode)
- [ ] `config.h` has your OpenAI API key

---

## 🔧 Flash Process Testing

### Step 1: Compilation

- [ ] Firmware compiles without errors
- [ ] No warnings about memory overflow
- [ ] Build completes successfully
- [ ] Estimated time: 30-60 seconds

### Step 2: Upload

- [ ] Upload starts successfully
- [ ] Progress bar shows percentage
- [ ] Upload completes without errors
- [ ] Watch reboots automatically
- [ ] Estimated time: 10-20 seconds

### Step 3: Serial Monitor

- [ ] Serial monitor connects at 115200 baud
- [ ] Boot messages appear
- [ ] No error messages in boot sequence
- [ ] Version shows "5.00"

---

## 📱 Basic Hardware Testing

### Display Tests

- [ ] Display turns on
- [ ] VOLT logo appears (boot screen)
- [ ] Text is readable
- [ ] Colors display correctly
- [ ] Backlight works
- [ ] Screen doesn't flicker

### Button Tests

- [ ] Single press detected
- [ ] Double press detected (joke)
- [ ] Triple press detected (breathing)
- [ ] Long press detected (love message)
- [ ] 5 quick presses detected (AP mode)
- [ ] Button debouncing works (no false triggers)

### LED Tests

- [ ] LED turns on during recording
- [ ] LED blinks correctly
- [ ] LED turns off after recording

### Speaker Tests

- [ ] Speaker produces sound
- [ ] Volume is adequate
- [ ] No distortion
- [ ] Audio is clear

---

## 📶 WiFi Manager Testing

### Automatic AP Mode (No WiFi Configured)

- [ ] Watch enters AP mode automatically on first boot
- [ ] Display shows AP information
- [ ] AP SSID appears: `VOLT-Setup-XXXX`
- [ ] Can connect to AP from phone
- [ ] AP password works: `volt2024`
- [ ] AP IP is: `192.168.4.1`

### Manual AP Mode (5 Button Presses)

- [ ] 5 quick presses triggers AP mode
- [ ] Display updates to show AP info
- [ ] AP starts successfully
- [ ] Can connect from phone
- [ ] Previous WiFi disconnects

### WiFi Connection (Legacy)

- [ ] Connects to WiFi from config.h
- [ ] Connection completes within timeout
- [ ] IP address is assigned
- [ ] Display shows "WiFi OK!"
- [ ] Serial monitor shows IP address

### WiFi Connection (Multi-Network)

- [ ] Tries networks in priority order
- [ ] Falls back to backup networks
- [ ] Remembers last successful network
- [ ] Reconnects after power cycle
- [ ] Handles network disconnection

---

## 🌐 Web Interface Testing

### Access in AP Mode

- [ ] Can open `http://192.168.4.1` in browser
- [ ] Web page loads completely
- [ ] Page is mobile-friendly
- [ ] All sections visible
- [ ] No JavaScript errors

### Network Scanning

- [ ] "Scan for Networks" button works
- [ ] Scan completes successfully
- [ ] Networks appear in list
- [ ] Signal strength shows correctly
- [ ] Encryption type displays
- [ ] Stored networks marked with ✓

### Network Addition

- [ ] Can click network from scan list
- [ ] SSID auto-fills in form
- [ ] Can enter password
- [ ] "Add Network" button works
- [ ] Success message appears
- [ ] Network appears in stored list

### Stored Networks Display

- [ ] Shows all stored networks
- [ ] Priority numbers correct
- [ ] Enabled/disabled status shows
- [ ] Can refresh list
- [ ] Updates after adding network

### Device Status

- [ ] Shows firmware version (5.00)
- [ ] Shows WiFi connection status
- [ ] Shows IP address
- [ ] Shows signal strength (RSSI)
- [ ] Shows uptime
- [ ] Shows free memory
- [ ] Refresh button works

---

## 🔌 REST API Testing

### Authentication

- [ ] Requests without auth return 401
- [ ] Requests with correct password work
- [ ] Bearer token format works
- [ ] Direct password format works

### GET /api/wifi/scan

```bash
curl -H "Authorization: volt2024" http://192.168.4.1/api/wifi/scan
```

- [ ] Returns JSON response
- [ ] `success: true`
- [ ] Networks array populated
- [ ] SSID, RSSI, encryption included
- [ ] isStored flag correct

### GET /api/wifi/list

```bash
curl -H "Authorization: volt2024" http://192.168.4.1/api/wifi/list
```

- [ ] Returns stored networks
- [ ] SSID, priority, enabled included
- [ ] Passwords NOT included (security)
- [ ] Empty array if no networks

### POST /api/wifi/add

```bash
curl -X POST -H "Authorization: volt2024" \
  -H "Content-Type: application/json" \
  -d '{"ssid":"TestNet","password":"test123"}' \
  http://192.168.4.1/api/wifi/add
```

- [ ] Accepts valid JSON
- [ ] Returns success message
- [ ] Network is stored
- [ ] Appears in list
- [ ] Can connect to network

### DELETE /api/wifi/remove

```bash
curl -X DELETE -H "Authorization: volt2024" \
  -H "Content-Type: application/json" \
  -d '{"ssid":"TestNet"}' \
  http://192.168.4.1/api/wifi/remove
```

- [ ] Removes network successfully
- [ ] Returns success message
- [ ] Network no longer in list
- [ ] Doesn't affect other networks

### GET /api/status

```bash
curl -H "Authorization: volt2024" http://192.168.4.1/api/status
```

- [ ] Returns device information
- [ ] Version correct (5.00)
- [ ] WiFi status accurate
- [ ] IP address correct
- [ ] RSSI value reasonable
- [ ] Uptime incrementing
- [ ] Free heap reasonable

---

## 🎤 Voice & AI Testing

### Speech Recognition (STT)

- [ ] Press button to start recording
- [ ] LED lights up during recording
- [ ] Records for 5 seconds
- [ ] Audio uploads to OpenAI
- [ ] Transcription returns
- [ ] Transcription is accurate

### AI Response (GPT)

- [ ] User speech sent to GPT
- [ ] Response generated
- [ ] Response is appropriate
- [ ] Response is short (under 150 tokens)
- [ ] Personality matches VOLT
- [ ] Mentions child's name

### Text-to-Speech (TTS)

- [ ] Response sent to TTS
- [ ] ECHO voice used
- [ ] Audio downloads
- [ ] Audio plays through speaker
- [ ] Voice is clear
- [ ] Speed is correct (1.08x)
- [ ] No audio glitches

### Full Conversation Flow

- [ ] Press button
- [ ] Say something
- [ ] LED blinks during recording
- [ ] "Thinking..." appears on display
- [ ] Response plays through speaker
- [ ] Display shows "Speaking..."
- [ ] Returns to idle after response

---

## 🎮 Button Pattern Testing

### Single Press

- [ ] Triggers listening mode (if online)
- [ ] Shows offline message (if offline)
- [ ] LED activates
- [ ] Recording starts

### Double Press

- [ ] Tells a joke
- [ ] Joke displays on screen
- [ ] Joke counter increments
- [ ] Returns to idle after 5 seconds

### Triple Press

- [ ] Starts breathing exercise
- [ ] Shows breathing instructions
- [ ] Circle animation works
- [ ] 4 breathing cycles complete
- [ ] "Great job!" message appears

### Long Press (Hold 2+ seconds)

- [ ] Shows love message
- [ ] Message displays on screen
- [ ] Speaks message if online
- [ ] Love reminder counter increments
- [ ] Returns to idle after 4 seconds

### 5 Quick Presses

- [ ] Enters AP mode
- [ ] Display shows AP info
- [ ] WiFi AP starts
- [ ] Can connect from phone
- [ ] Web interface accessible

---

## 💾 Memory & Storage Testing

### WiFi Network Storage

- [ ] Can store 1 network
- [ ] Can store 5 networks (maximum)
- [ ] Cannot store more than 5
- [ ] Networks persist after reboot
- [ ] Priorities saved correctly
- [ ] Passwords encrypted/secure

### Child Profile Storage

- [ ] Profile loads on boot
- [ ] Conversation counter works
- [ ] Love reminder counter works
- [ ] Joke counter works
- [ ] Milestones save correctly
- [ ] Data persists after reboot

### Memory Management

- [ ] No memory leaks during operation
- [ ] Free heap doesn't decrease over time
- [ ] PSRAM used for audio buffers
- [ ] No crashes from memory issues

---

## 🔋 Power & Stability Testing

### Power On/Off

- [ ] Watch boots correctly
- [ ] Boot sequence completes
- [ ] All systems initialize
- [ ] No crashes during boot

### Sleep Mode

- [ ] Enters sleep after 5 minutes idle
- [ ] Display shows sleep message
- [ ] Backlight turns off
- [ ] Wakes on button press
- [ ] Resumes normal operation

### Long-Term Stability

- [ ] Runs for 1 hour without issues
- [ ] No random reboots
- [ ] WiFi stays connected
- [ ] No memory errors
- [ ] Responds to all button presses

### AP Mode Timeout

- [ ] AP mode times out after 5 minutes
- [ ] Watch restarts automatically
- [ ] Returns to normal operation
- [ ] No data loss

---

## 🌐 Network Scenarios Testing

### Scenario 1: No WiFi Configured

- [ ] Enters AP mode automatically
- [ ] User can add WiFi via web interface
- [ ] Connects after restart
- [ ] Works normally

### Scenario 2: Single Network

- [ ] Connects to configured network
- [ ] Reconnects after power cycle
- [ ] Handles network disconnection
- [ ] Retries connection

### Scenario 3: Multiple Networks

- [ ] Tries primary network first
- [ ] Falls back to secondary
- [ ] Remembers last successful
- [ ] Prioritizes correctly

### Scenario 4: Network Unavailable

- [ ] Tries all stored networks
- [ ] Enters offline mode
- [ ] Offline features work
- [ ] Can enter AP mode manually

### Scenario 5: Weak Signal

- [ ] Connects despite weak signal
- [ ] Maintains connection
- [ ] Reconnects if dropped
- [ ] Shows signal strength

---

## 🎯 Integration Testing

### Complete User Journey 1: First Setup

1. [ ] Flash firmware
2. [ ] Watch boots to AP mode
3. [ ] Connect phone to AP
4. [ ] Open web interface
5. [ ] Scan for networks
6. [ ] Add home WiFi
7. [ ] Restart watch
8. [ ] Watch connects to WiFi
9. [ ] Talk to VOLT
10. [ ] Receive AI response

### Complete User Journey 2: Daily Use

1. [ ] Power on watch
2. [ ] Connects to WiFi automatically
3. [ ] Press button to talk
4. [ ] Ask a question
5. [ ] Receive answer
6. [ ] Double press for joke
7. [ ] Triple press for breathing
8. [ ] Long press for love message
9. [ ] Watch enters sleep
10. [ ] Wake and use again

### Complete User Journey 3: Network Change

1. [ ] Watch connected to home WiFi
2. [ ] Press 5 times for AP mode
3. [ ] Connect phone to AP
4. [ ] Add work WiFi
5. [ ] Restart watch
6. [ ] Watch connects to work WiFi
7. [ ] All features work
8. [ ] Returns home, connects to home WiFi

---

## 🐛 Error Handling Testing

### WiFi Errors

- [ ] Handles wrong password gracefully
- [ ] Handles network not found
- [ ] Handles timeout correctly
- [ ] Shows appropriate error messages
- [ ] Doesn't crash on WiFi errors

### API Errors

- [ ] Handles OpenAI API errors
- [ ] Handles network timeout
- [ ] Handles invalid API key
- [ ] Shows error on display
- [ ] Recovers from errors

### Hardware Errors

- [ ] Handles microphone failure
- [ ] Handles speaker failure
- [ ] Handles display issues
- [ ] Logs errors to serial
- [ ] Doesn't crash system

---

## 📊 Performance Testing

### Response Times

- [ ] WiFi connection: < 20 seconds
- [ ] Network scan: < 10 seconds
- [ ] Web page load: < 2 seconds
- [ ] API response: < 1 second
- [ ] Voice recording: 5 seconds
- [ ] AI response: < 10 seconds
- [ ] TTS playback: < 5 seconds

### Resource Usage

- [ ] Free heap > 100KB
- [ ] CPU usage reasonable
- [ ] No excessive heating
- [ ] Battery drain acceptable
- [ ] WiFi signal stable

---

## ✅ Final Verification

### All Features Working

- [ ] WiFi connection
- [ ] Network scanning
- [ ] Multi-network storage
- [ ] Web interface
- [ ] REST API
- [ ] Voice recognition
- [ ] AI responses
- [ ] Text-to-speech
- [ ] Button patterns
- [ ] Display functions
- [ ] LED indicators
- [ ] Sleep mode
- [ ] AP mode

### Documentation Verified

- [ ] HOW_TO_FLASH.md accurate
- [ ] VOICE_OPTIONS.md helpful
- [ ] WIFI_SETUP_GUIDE.md clear
- [ ] WIFI_API_DOCUMENTATION.md complete
- [ ] All examples work

### Ready for Production

- [ ] All critical tests pass
- [ ] No major bugs found
- [ ] Performance acceptable
- [ ] User experience good
- [ ] Safe for child use

---

## 📝 Test Results

**Date Tested:** ******\_\_\_******

**Tester:** ******\_\_\_******

**Overall Result:** ⬜ PASS ⬜ FAIL ⬜ NEEDS WORK

**Notes:**

---

---

---

**Issues Found:**

---

---

---

**Recommendations:**

---

---

---

---

## 🎉 Testing Complete!

If all tests pass, VOLT v5.00 is ready for Stone to use!

**Remember:**

- Test in a safe environment first
- Monitor initial usage
- Keep firmware updated
- Report any issues found

**Enjoy VOLT v5.00!** ⚡💙
