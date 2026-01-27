# VOLT Firmware Testing Checklist

## Comprehensive Testing Guide for Stone's Watch

This checklist ensures every feature works perfectly before giving the watch to Stone.

---

## 🎯 Testing Overview

### Testing Phases:

1. **Pre-Flash Testing** (Arduino IDE)
2. **Initial Boot Testing** (First power-on)
3. **Hardware Testing** (Display, buttons, audio)
4. **WiFi Testing** (Connection, stability)
5. **AI Features Testing** (Voice, chat, TTS)
6. **Button Patterns Testing** (All 5 patterns)
7. **Power Management Testing** (Battery, sleep)
8. **Edge Cases Testing** (Failures, recovery)
9. **Real-World Testing** (Stone's usage)

**Estimated Time:** 2-3 hours for complete testing

---

## 📋 Phase 1: Pre-Flash Testing

### ✅ Compilation Test

**Location:** Arduino IDE (before connecting watch)

- [ ] Arduino IDE 2.x installed
- [ ] ESP32 board support installed (v2.0.11+)
- [ ] TFT_eSPI library installed and configured
- [ ] ArduinoJson library installed
- [ ] Board set to "ESP32S3 Dev Module"
- [ ] All board settings match COMPILATION_GUIDE.md
- [ ] Firmware compiles with 0 errors
- [ ] Firmware compiles with 0 warnings (or only library warnings)
- [ ] Program storage < 80% (should be ~26%)
- [ ] Dynamic memory < 80% (should be ~13%)

**Expected Result:**

```
Done compiling
Sketch uses ~850KB (26%) of program storage space.
Global variables use ~45KB (13%) of dynamic memory.
```

### ✅ Configuration Test

- [ ] WiFi SSID configured in config_stone_FINAL.h
- [ ] WiFi password configured in config_stone_FINAL.h
- [ ] OpenAI API key configured in config_stone_FINAL.h
- [ ] Child name is "Stone"
- [ ] Child age is 8
- [ ] No compile-time warnings about missing config

**Expected Result:** No configuration warnings during compilation

---

## 📋 Phase 2: Initial Boot Testing

### ✅ First Power-On

**Setup:** Watch connected via USB, Serial Monitor open (115200 baud)

- [ ] Watch powers on
- [ ] LED blinks during boot
- [ ] Serial Monitor shows boot messages
- [ ] No error messages in Serial Monitor
- [ ] Boot completes in < 10 seconds

**Expected Serial Output:**

```
=== VOLT for Stone - Starting ===
Power: Initialized
Display: Initialized
WiFi: Connecting to [YourWiFi]...
WiFi: Connected!
WiFi: IP address: 192.168.x.x
AI: Initialized successfully
=== VOLT Ready for Stone ===
```

### ✅ Display Boot Test

- [ ] Display turns on
- [ ] Backlight activates
- [ ] "VOLT" logo appears
- [ ] Text is readable
- [ ] Colors are correct (cyan/white on black)
- [ ] No screen artifacts or glitches
- [ ] Battery percentage displays

**Expected Display:**

```
     VOLT

  Ready to talk!

  Battery: XX%

  Press button to start
```

---

## 📋 Phase 3: Hardware Testing

### ✅ Display Test

- [ ] Screen brightness is adequate
- [ ] Text is sharp and clear
- [ ] Colors are vibrant
- [ ] No dead pixels
- [ ] No screen flickering
- [ ] Backlight stays on during activity
- [ ] Backlight dims after timeout (30 seconds)

**Test Method:** Observe display during idle and active states

### ✅ Button Test

- [ ] Button is responsive
- [ ] Single press detected
- [ ] Double press detected
- [ ] Triple press detected
- [ ] Long press (2 seconds) detected
- [ ] 5 presses detected
- [ ] No false triggers
- [ ] Debouncing works (no double-counting)

**Test Method:** Press button in different patterns, watch Serial Monitor

**Expected Serial Output:**

```
Button: Single press detected
Button: Double press detected
Button: Triple press detected
Button: Long press detected (2000ms)
Button: 5 presses detected
```

### ✅ LED Test

- [ ] LED turns on during button press
- [ ] LED turns off after release
- [ ] LED brightness is visible
- [ ] LED doesn't stay on permanently

**Test Method:** Press button and observe LED

### ✅ Audio Output Test (Speaker)

**Prerequisites:** WiFi connected, TTS test

- [ ] Speaker produces sound
- [ ] Volume is audible
- [ ] No distortion at normal volume
- [ ] No crackling or popping
- [ ] Speech is clear and understandable
- [ ] Speaker amplifier enables/disables correctly

**Test Method:** Trigger a joke (2 button presses) and listen

### ✅ Audio Input Test (Microphone)

**Prerequisites:** WiFi connected, voice test

- [ ] Microphone picks up voice
- [ ] Recording starts on button press
- [ ] Recording stops after 5 seconds
- [ ] Audio quality is acceptable
- [ ] Background noise is minimal
- [ ] Voice is recognizable in transcription

**Test Method:** Press button once, speak clearly, check transcription

---

## 📋 Phase 4: WiFi Testing

### ✅ Initial Connection

- [ ] WiFi connects on boot
- [ ] Connection completes in < 20 seconds
- [ ] IP address assigned
- [ ] Signal strength adequate (RSSI > -70)
- [ ] Connection is stable

**Expected Serial Output:**

```
WiFi: Connecting to [YourWiFi]...
WiFi: Connected!
WiFi: IP address: 192.168.x.x
WiFi: Signal strength: -XX dBm
```

### ✅ Auto-Reconnect Test

**Test Method:** Temporarily disable WiFi router, then re-enable

- [ ] Watch detects WiFi loss
- [ ] Watch attempts reconnection
- [ ] Watch reconnects automatically
- [ ] Features resume after reconnection
- [ ] No manual intervention needed

**Expected Serial Output:**

```
WiFi: Connection lost
WiFi: Attempting reconnection...
WiFi: Reconnected!
```

### ✅ AP Mode Test (WiFi Setup)

**Test Method:** Press button 5 times

- [ ] AP mode activates
- [ ] SSID "VOLT-Setup" appears
- [ ] Password "volt2024" works
- [ ] Can connect from phone/computer
- [ ] IP 192.168.4.1 accessible
- [ ] Configuration page loads (if implemented)
- [ ] AP mode exits after timeout or button press

**Expected Display:**

```
  WiFi Setup Mode

  Connect to:
  VOLT-Setup

  Password: volt2024
  Go to: 192.168.4.1
```

### ✅ Offline Mode Test

**Test Method:** Disconnect WiFi, test offline features

- [ ] Watch continues to function
- [ ] Display shows "Offline mode"
- [ ] Offline jokes work (2 presses)
- [ ] Breathing exercise works (3 presses)
- [ ] Love message works (long press)
- [ ] Voice chat shows appropriate error
- [ ] No crashes or freezes

**Expected Behavior:** Offline features work, online features show friendly error

---

## 📋 Phase 5: AI Features Testing

### ✅ Voice Recording Test

**Test Method:** Press button once, speak for 5 seconds

- [ ] "Listening..." appears on display
- [ ] LED lights up during recording
- [ ] Recording lasts exactly 5 seconds
- [ ] Recording stops automatically
- [ ] Audio buffer doesn't overflow
- [ ] No crashes during recording

**Expected Display:**

```
  Listening...

  [Progress indicator]
```

**Expected Serial Output:**

```
AI: Recording started
AI: Recording... (5 seconds)
AI: Recording complete
AI: Audio buffer: XXXXX bytes
```

### ✅ Speech-to-Text Test (Whisper API)

**Test Method:** Record voice, check transcription

**Test Phrases:**

1. "Hi VOLT, how are you?"
2. "Tell me about dinosaurs"
3. "I need help with my homework"
4. "I'm feeling nervous"

**For Each Phrase:**

- [ ] Recording completes
- [ ] "Thinking..." appears on display
- [ ] Transcription request sent to API
- [ ] Transcription received
- [ ] Transcription is accurate
- [ ] No API errors

**Expected Serial Output:**

```
AI: Transcribing audio...
AI: Transcription: "Hi VOLT, how are you?"
AI: Transcription successful
```

### ✅ GPT-4 Chat Test

**Test Method:** Complete voice interaction

**Test Conversations:**

**Test 1: Simple Greeting**

- Input: "Hi VOLT, how are you?"
- [ ] Response is friendly and age-appropriate
- [ ] Response mentions Stone by name
- [ ] Response is 2-3 sentences max
- [ ] Response time < 10 seconds

**Test 2: Homework Help**

- Input: "Can you help me with math?"
- [ ] Response offers to help
- [ ] Response is encouraging
- [ ] Response is appropriate for 8-year-old

**Test 3: Anxiety Support**

- Input: "I'm feeling nervous"
- [ ] Response is supportive
- [ ] Response offers coping strategies
- [ ] Response is calming and reassuring

**Test 4: General Knowledge**

- Input: "Tell me about dinosaurs"
- [ ] Response is informative
- [ ] Response is age-appropriate
- [ ] Response is engaging

**Expected Serial Output:**

```
AI: Sending chat request...
AI: Response received
AI: Response: "[GPT-4 response text]"
```

### ✅ Text-to-Speech Test

**Test Method:** Complete voice interaction, listen to response

- [ ] TTS request sent successfully
- [ ] Audio stream received
- [ ] Audio plays through speaker
- [ ] Voice is natural and clear
- [ ] Speech speed is appropriate (1.08x)
- [ ] Volume is comfortable
- [ ] No audio glitches or cutoffs
- [ ] Speaker disables after playback

**Expected Serial Output:**

```
AI: Speaking: "[Response text]"
AI: TTS request sent
AI: Streaming audio...
AI: Speech complete
```

### ✅ Complete AI Interaction Test

**Test Method:** Full voice conversation cycle

1. Press button once
2. Speak: "Hi VOLT, tell me a fun fact"
3. Wait for response
4. Listen to TTS output

**Checklist:**

- [ ] Recording works
- [ ] Transcription accurate
- [ ] GPT-4 response appropriate
- [ ] TTS playback clear
- [ ] Total interaction time < 15 seconds
- [ ] Returns to idle screen after
- [ ] No errors or crashes

---

## 📋 Phase 6: Button Patterns Testing

### ✅ Pattern 1: Single Press (Voice Chat)

**Test Method:** Press button once

- [ ] "Listening..." appears
- [ ] LED lights up
- [ ] Microphone records for 5 seconds
- [ ] "Thinking..." appears
- [ ] Transcription occurs
- [ ] GPT-4 responds
- [ ] TTS plays response
- [ ] Returns to idle screen

**Expected Flow:** Record → Transcribe → Chat → Speak → Idle

### ✅ Pattern 2: Double Press (Joke)

**Test Method:** Press button twice quickly

- [ ] "Telling a joke..." appears
- [ ] Joke is age-appropriate
- [ ] Joke is funny for 8-year-old
- [ ] TTS speaks the joke clearly
- [ ] Returns to idle screen

**Test Multiple Times:**

- [ ] Different jokes each time (if online)
- [ ] Offline jokes work without WiFi
- [ ] No repeated jokes immediately

**Expected Serial Output:**

```
Button: Double press detected
AI: Telling a joke...
AI: Joke: "[Joke text]"
```

### ✅ Pattern 3: Triple Press (Breathing Exercise)

**Test Method:** Press button three times quickly

- [ ] "Breathing Exercise" appears
- [ ] Instructions are clear
- [ ] "Breathe in..." displays
- [ ] "Hold..." displays
- [ ] "Breathe out..." displays
- [ ] Timing is appropriate (4-7-8 pattern)
- [ ] Visual cues help (color changes)
- [ ] Completes full cycle
- [ ] Returns to idle screen

**Expected Display Sequence:**

```
Breathing Exercise
↓
Breathe in... (4 seconds)
↓
Hold... (7 seconds)
↓
Breathe out... (8 seconds)
↓
Great job!
```

### ✅ Pattern 4: Long Press (Dad's Love Message)

**Test Method:** Hold button for 2+ seconds

- [ ] Long press detected at 2 seconds
- [ ] "Dad's Message" appears
- [ ] Love message plays via TTS
- [ ] Message is heartfelt and personal
- [ ] Stone's name is mentioned
- [ ] Message is encouraging
- [ ] Returns to idle screen

**Expected Serial Output:**

```
Button: Long press detected (2000ms)
AI: Playing love message...
AI: Message: "Stone, Dad loves you so much!..."
```

### ✅ Pattern 5: Five Presses (WiFi Setup)

**Test Method:** Press button 5 times quickly

- [ ] 5 presses detected
- [ ] "WiFi Setup Mode" appears
- [ ] AP mode activates
- [ ] Instructions display
- [ ] SSID and password shown
- [ ] IP address shown
- [ ] Can exit with button press
- [ ] Can exit after timeout (5 minutes)

**Expected Display:**

```
WiFi Setup Mode

Connect to:
VOLT-Setup

Password: volt2024
Go to: 192.168.4.1
```

---

## 📋 Phase 7: Power Management Testing

### ✅ Battery Monitoring

- [ ] Battery percentage displays on idle screen
- [ ] Battery percentage updates periodically
- [ ] Percentage is reasonably accurate
- [ ] Low battery warning at 20%
- [ ] Low battery warning is visible
- [ ] No false low battery warnings

**Expected Display (Idle Screen):**

```
Battery: XX%
```

**Expected Serial Output (Low Battery):**

```
Power: Low battery warning (XX%)
```

### ✅ Deep Sleep Test

**Test Method:** Leave watch idle for 5+ minutes

- [ ] Idle timer starts after last activity
- [ ] Display dims after 30 seconds
- [ ] Deep sleep activates after 5 minutes
- [ ] Display turns off
- [ ] LED turns off
- [ ] Speaker amplifier disables
- [ ] Power consumption drops significantly

**Expected Serial Output:**

```
Power: Idle for 300 seconds
Power: Entering deep sleep...
```

### ✅ Wake-Up Test

**Test Method:** After deep sleep, press button

- [ ] Button press wakes device
- [ ] Boot sequence runs
- [ ] Display turns on
- [ ] WiFi reconnects
- [ ] All features work normally
- [ ] Wake-up time < 3 seconds

**Expected Serial Output:**

```
=== VOLT for Stone - Waking Up ===
Power: Wake from deep sleep
WiFi: Reconnecting...
=== VOLT Ready ===
```

### ✅ Watchdog Timer Test

**Test Method:** Monitor for automatic recovery

- [ ] Watchdog timer is active
- [ ] System resets if frozen (should not happen)
- [ ] No unexpected resets during normal use
- [ ] Watchdog prevents permanent hangs

**Expected Behavior:** No watchdog resets during normal operation

### ✅ Battery Life Test

**Test Method:** Full charge, normal use, measure time

**Day 1:**

- [ ] Charge to 100%
- [ ] Use normally (10-15 interactions)
- [ ] Check battery at end of day
- [ ] Should be > 50%

**Day 2:**

- [ ] Continue from Day 1 battery level
- [ ] Use normally (10-15 interactions)
- [ ] Check battery at end of day
- [ ] Should be > 10%

**Day 3:**

- [ ] Continue from Day 2 battery level
- [ ] Use lightly (5-10 interactions)
- [ ] Battery should last through day

**Target:** 2-3 days on single charge with normal use

---

## 📋 Phase 8: Edge Cases Testing

### ✅ No WiFi Scenarios

**Test Method:** Disable WiFi, test all features

- [ ] Offline mode activates
- [ ] Display shows "Offline mode"
- [ ] Jokes work (offline library)
- [ ] Breathing exercise works
- [ ] Love message works
- [ ] Voice chat shows friendly error
- [ ] No crashes or freezes
- [ ] Reconnects when WiFi available

**Expected Behavior:** Graceful degradation, no crashes

### ✅ API Failure Scenarios

**Test Method:** Invalid API key or network issues

**Test 1: Invalid API Key**

- [ ] Error detected
- [ ] Friendly error message shown
- [ ] No crash or freeze
- [ ] Can retry
- [ ] Serial Monitor shows error details

**Test 2: API Timeout**

- [ ] Timeout detected after 30 seconds
- [ ] Friendly error message shown
- [ ] Returns to idle screen
- [ ] Can try again

**Test 3: API Rate Limit**

- [ ] Rate limit error detected
- [ ] Appropriate message shown
- [ ] Suggests waiting
- [ ] No crash

**Expected Serial Output:**

```
AI: API error: [Error details]
AI: Showing error message to user
```

### ✅ Low Battery Scenarios

**Test Method:** Drain battery to < 20%

- [ ] Low battery warning appears
- [ ] Warning is clear and visible
- [ ] Suggests charging
- [ ] All features still work
- [ ] No unexpected shutdowns
- [ ] Graceful shutdown at critical level

**Expected Display:**

```
⚠️ Low Battery!
Please charge soon
Battery: XX%
```

### ✅ Memory Stress Test

**Test Method:** Rapid repeated interactions

- [ ] 10 voice chats in a row
- [ ] No memory leaks
- [ ] No slowdowns
- [ ] No crashes
- [ ] Heap memory stable
- [ ] Stack doesn't overflow

**Expected Serial Output:**

```
Free heap: XXXXX bytes (should stay consistent)
```

### ✅ Button Spam Test

**Test Method:** Rapidly press button many times

- [ ] Debouncing works correctly
- [ ] No false pattern detection
- [ ] No crashes
- [ ] System remains responsive
- [ ] Returns to normal after spam stops

**Expected Behavior:** Graceful handling, no crashes

### ✅ Long Running Test

**Test Method:** Leave powered on for 24+ hours

- [ ] No crashes
- [ ] No memory leaks
- [ ] WiFi stays connected
- [ ] All features work after 24 hours
- [ ] No performance degradation

**Expected Behavior:** Stable operation for extended periods

---

## 📋 Phase 9: Real-World Testing

### ✅ Stone's First Use

**Supervised Testing with Stone:**

- [ ] Stone can press button easily
- [ ] Stone understands button patterns
- [ ] Stone's voice is recognized
- [ ] Responses are age-appropriate
- [ ] Stone finds it helpful
- [ ] Stone enjoys using it
- [ ] No confusion or frustration

**Observe:**

- How Stone holds the watch
- How Stone speaks to VOLT
- Stone's reactions to responses
- Any difficulties or confusion

### ✅ Daily Use Test (Week 1)

**Day 1:**

- [ ] Morning use works
- [ ] School day use works
- [ ] Evening use works
- [ ] Battery lasts all day

**Day 2-3:**

- [ ] Consistent performance
- [ ] No new issues
- [ ] Stone uses independently

**Day 4-7:**

- [ ] Long-term stability
- [ ] Battery life consistent
- [ ] Stone's usage patterns emerge

**Monitor:**

- Battery life in real use
- Most used features
- Any issues or bugs
- Stone's feedback

### ✅ Anxiety Support Test

**Real Scenario Testing:**

- [ ] Stone uses breathing exercise when anxious
- [ ] Breathing exercise helps calm Stone
- [ ] Stone asks VOLT for help
- [ ] VOLT's responses are supportive
- [ ] Stone feels better after interaction

**Observe:**

- Effectiveness of breathing exercise
- Quality of AI support responses
- Stone's emotional response
- Overall helpfulness

### ✅ Parent Feedback

**Dad's Assessment:**

- [ ] Easy to maintain
- [ ] Reliable and stable
- [ ] Helps Stone as intended
- [ ] Worth the effort
- [ ] Would recommend to others

---

## 📊 Testing Summary Template

### Test Results:

| Phase            | Tests   | Passed   | Failed   | Notes |
| ---------------- | ------- | -------- | -------- | ----- |
| Pre-Flash        | 10      | \_\_     | \_\_     |       |
| Initial Boot     | 5       | \_\_     | \_\_     |       |
| Hardware         | 20      | \_\_     | \_\_     |       |
| WiFi             | 15      | \_\_     | \_\_     |       |
| AI Features      | 25      | \_\_     | \_\_     |       |
| Button Patterns  | 25      | \_\_     | \_\_     |       |
| Power Management | 15      | \_\_     | \_\_     |       |
| Edge Cases       | 20      | \_\_     | \_\_     |       |
| Real-World       | 15      | \_\_     | \_\_     |       |
| **TOTAL**        | **150** | **\_\_** | **\_\_** |       |

### Pass Criteria:

- **Critical Tests:** 100% pass (boot, safety, core features)
- **Important Tests:** 95%+ pass (AI, buttons, power)
- **Nice-to-Have:** 90%+ pass (edge cases, optimization)

### Overall Status:

- [ ] ✅ **PASS** - Ready for Stone
- [ ] ⚠️ **CONDITIONAL PASS** - Minor issues, usable with workarounds
- [ ] ❌ **FAIL** - Critical issues, needs fixes

---

## 🐛 Bug Tracking Template

### Issues Found:

| #   | Severity | Description | Steps to Reproduce | Status |
| --- | -------- | ----------- | ------------------ | ------ |
| 1   | Critical |             |                    |        |
| 2   | High     |             |                    |        |
| 3   | Medium   |             |                    |        |
| 4   | Low      |             |                    |        |

### Severity Levels:

- **Critical:** Prevents basic functionality, must fix
- **High:** Major feature broken, should fix
- **Medium:** Minor issue, nice to fix
- **Low:** Cosmetic or rare issue, optional fix

---

## ✅ Final Sign-Off

### Before Giving to Stone:

- [ ] All critical tests passed
- [ ] All high-priority tests passed
- [ ] No critical or high-severity bugs
- [ ] Battery life meets expectations (2-3 days)
- [ ] All 5 button patterns work perfectly
- [ ] AI features work reliably
- [ ] Offline mode works
- [ ] Dad is confident in the watch
- [ ] Stone is excited to use it

### Sign-Off:

**Tested by:** ******\_\_\_******  
**Date:** ******\_\_\_******  
**Result:** ✅ PASS / ⚠️ CONDITIONAL / ❌ FAIL  
**Notes:** ******\_\_\_******

---

**Made with ❤️ by Dad for Stone**

_Thorough testing ensures Stone gets a reliable, helpful companion!_
