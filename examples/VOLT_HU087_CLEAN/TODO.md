# VOLT Firmware - Bug Fixes & Improvements TODO

## 🐛 Critical Bugs Found & Fixes Needed

### 1. **Missing Configuration Constants** ⚠️ CRITICAL
**Issue**: `config_stone.h` references constants that don't exist in `volt_ai.h`
- `AI_MODEL` - not defined (should be `CHAT_MODEL_OPENAI`)
- `STT_MODEL` - not defined (should be `STT_MODEL_OPENAI`)
- `TTS_MODEL` - not defined (should be `TTS_MODEL_OPENAI`)
- `TTS_VOICE` - not defined (should be `TTS_VOICE_OPENAI`)

**Fix**: Add these constants to `config_stone.h` or update references in `volt_ai.h`

### 2. **WiFi Status Check Bug** ⚠️ CRITICAL
**Issue**: Code uses `WiFi.isConnected()` which doesn't exist in ESP32 WiFi library
**Location**: Multiple places in `volt_stone.ino`
**Fix**: Change to `WiFi.status() == WL_CONNECTED`

### 3. **I2S Port Type Mismatch** ⚠️ HIGH
**Issue**: `MIC_I2S_NUM` and `SPK_I2S_NUM` defined as `I2S_NUM_0` and `I2S_NUM_1` but used incorrectly
**Location**: `pins_hu087.h` and `volt_ai.h`
**Fix**: Ensure consistent typing and casting

### 4. **Audio Buffer Memory Leak Risk** ⚠️ MEDIUM
**Issue**: Audio buffer allocated but may not be freed properly on errors
**Location**: `volt_ai.h` - `begin()` method
**Fix**: Add proper error handling and cleanup

### 5. **HTTP Multipart Form Data Bug** ⚠️ CRITICAL
**Issue**: Whisper API transcription uses incorrect multipart form data implementation
**Location**: `volt_ai.h` - `transcribe()` method
**Fix**: Implement proper multipart/form-data with WAV header

### 6. **Missing WAV Header for Audio** ⚠️ CRITICAL
**Issue**: Raw PCM audio sent to Whisper API without WAV header
**Location**: `volt_ai.h` - `transcribe()` method
**Fix**: Add WAV header generation before sending audio

### 7. **TTS Response Format Issue** ⚠️ HIGH
**Issue**: TTS API response format "pcm" may not be supported, should use "mp3" or "opus"
**Location**: `volt_ai.h` - `speak()` method
**Fix**: Change to supported format and add proper decoding

### 8. **Display Backlight Control Missing** ⚠️ MEDIUM
**Issue**: Backlight pin defined but never controlled
**Location**: `pins_hu087.h` defines `LCD_BL` but it's not used
**Fix**: Add backlight control in display initialization

### 9. **Deep Sleep Wake-up Configuration** ⚠️ MEDIUM
**Issue**: Only button wake-up configured, no timer wake-up for periodic checks
**Location**: `power_mgmt.h` - `enterDeepSleep()`
**Fix**: Add timer wake-up option

### 10. **String Memory Issues** ⚠️ MEDIUM
**Issue**: Large strings created on stack may cause crashes
**Location**: Multiple places using `String` class
**Fix**: Use `const char*` where possible, reserve String capacity

---

## ✅ Fixes to Implement

### Phase 1: Critical Fixes (Must Do Before First Flash)

- [ ] Fix missing AI model constants
- [ ] Fix WiFi status checks
- [ ] Fix Whisper API multipart form data
- [ ] Add WAV header generation
- [ ] Fix TTS response format
- [ ] Fix I2S port type issues
- [ ] Add display backlight control
- [ ] Add proper error handling throughout

### Phase 2: Important Improvements (Should Do)

- [ ] Optimize memory usage
- [ ] Add better error messages
- [ ] Improve audio quality
- [ ] Add connection retry logic
- [ ] Optimize battery estimation
- [ ] Add watchdog timer
- [ ] Improve deep sleep handling

### Phase 3: Nice to Have (Optional)

- [ ] Add offline voice feedback
- [ ] Cache common responses
- [ ] Add progress indicators
- [ ] Improve button debouncing
- [ ] Add configuration validation

---

## 📋 Testing Checklist (After Fixes)

### Compilation Tests:
- [ ] Code compiles without errors
- [ ] Code compiles without warnings
- [ ] All libraries found
- [ ] Sketch size < 1.5MB

### Hardware Tests:
- [ ] Display initializes correctly
- [ ] Backlight turns on
- [ ] Button responds
- [ ] LED blinks
- [ ] WiFi connects
- [ ] Microphone records
- [ ] Speaker plays audio

### Feature Tests:
- [ ] Voice chat works (1 press)
- [ ] Jokes work (2 presses)
- [ ] Breathing exercise works (3 presses)
- [ ] Love message works (4 presses)
- [ ] WiFi setup works (5 presses)
- [ ] Deep sleep works
- [ ] Wake from sleep works
- [ ] Battery percentage shows

### API Tests:
- [ ] Whisper transcription works
- [ ] GPT-4 chat works
- [ ] TTS speech works
- [ ] Error handling works
- [ ] Offline mode works

---

## 🎯 Priority Order

1. **IMMEDIATE** (Before first flash):
   - Fix all CRITICAL bugs
   - Add missing constants
   - Fix API implementations

2. **SOON** (After first successful test):
   - Optimize memory
   - Improve error handling
   - Add better feedback

3. **LATER** (After Stone uses it):
   - Add Phase 1 features (GPS, SOS)
   - Optimize battery life
   - Add more features

---

## 📝 Notes

- All fixes maintain backward compatibility
- No breaking changes to user experience
- Focus on stability and reliability
- Keep code simple and maintainable
