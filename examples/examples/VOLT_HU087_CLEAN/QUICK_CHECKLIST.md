# ✅ VOLT Quick Flash Checklist
## Print This and Check Off Each Step!

---

## 📋 BEFORE YOU START

### **What You Need:**
- [ ] Stone's HU-087 watch (charged 50%+)
- [ ] USB-C cable (data-capable)
- [ ] Windows computer
- [ ] Internet connection
- [ ] 45 minutes of time

### **Information to Gather:**
- [ ] WiFi name (SSID): ___________________________
- [ ] WiFi password: ___________________________
- [ ] OpenAI API key: ___________________________

---

## 🌐 DOWNLOADS (Window 2 - Web Browser)

### **Step 1: Arduino IDE**
- [ ] Go to: https://www.arduino.cc/en/software
- [ ] Download Windows MSI installer (~150 MB)
- [ ] Install Arduino IDE
- [ ] Close installer (don't open yet)

### **Step 2: OpenAI API Key**
- [ ] Go to: https://platform.openai.com/api-keys
- [ ] Sign up / Log in
- [ ] Create new API key named "VOLT for Stone"
- [ ] Copy key (starts with sk-proj-)
- [ ] Save key in Notepad
- [ ] Add $5-10 credit to account

### **Step 3: WiFi Info**
- [ ] Find WiFi name (must be 2.4GHz, not 5GHz)
- [ ] Get WiFi password
- [ ] Write both down

### **Step 4: USB Drivers (if needed)**
- [ ] Go to: https://sparks.gogo.co.nz/ch340.html
- [ ] Download CH341SER.EXE
- [ ] Install drivers
- [ ] Restart if prompted

---

## 💻 ARDUINO SETUP (Window 3 - Arduino IDE)

### **Step 5: Open Arduino IDE**
- [ ] Launch Arduino IDE
- [ ] Wait for it to fully load

### **Step 6: Install ESP32 Support**
- [ ] File → Preferences
- [ ] Add URL: https://espressif.github.io/arduino-esp32/package_esp32_index.json
- [ ] Click OK
- [ ] Tools → Board → Boards Manager
- [ ] Search: esp32
- [ ] Install "esp32 by Espressif Systems" (v2.0.11+)
- [ ] Wait 5-10 minutes
- [ ] Close Boards Manager

### **Step 7: Install Libraries**
- [ ] Tools → Manage Libraries
- [ ] Search: TFT_eSPI
- [ ] Install "TFT_eSPI by Bodmer"
- [ ] Search: ArduinoJson
- [ ] Install "ArduinoJson by Benoit Blanchon" (v6.x)
- [ ] Close Library Manager

### **Step 8: Configure TFT_eSPI**
- [ ] Open: C:\Users\[You]\Documents\Arduino\libraries\TFT_eSPI
- [ ] Edit: User_Setup_Select.h in Notepad
- [ ] Line 22: Add // before #include <User_Setup.h>
- [ ] Line 53: Remove // before #include <User_Setups/Setup25_TTGO_T_Display.h>
- [ ] Save file
- [ ] Close Notepad

### **Step 9: Open VOLT Firmware**
- [ ] File → Open
- [ ] Navigate to: C:\Users\Holle\Desktop\volt v5.00 flash\examples\examples\VOLT_HU087_CLEAN
- [ ] Open: volt_stone_FINAL.ino
- [ ] Verify 6 tabs open at top

### **Step 10: Configure WiFi & API**
- [ ] Click config_stone_FINAL.h tab
- [ ] Line 23: Change WIFI_SSID to your WiFi name
- [ ] Line 24: Change WIFI_PASSWORD to your password
- [ ] Line 33: Change OPENAI_API_KEY to your key
- [ ] Save (Ctrl+S)

### **Step 11: Connect Watch**
- [ ] Plug USB-C into watch
- [ ] Plug USB into computer
- [ ] Watch shows charging
- [ ] Tools → Port → Select COM port

### **Step 12: Board Settings**
- [ ] Tools → Board → ESP32 Arduino → ESP32S3 Dev Module
- [ ] USB CDC On Boot: Enabled
- [ ] CPU Frequency: 240MHz (WiFi)
- [ ] Flash Mode: QIO 80MHz
- [ ] Flash Size: 16MB (128Mb)
- [ ] Partition Scheme: 16M Flash (3MB APP/9.9MB FATFS)
- [ ] PSRAM: OPI PSRAM
- [ ] Upload Speed: 921600
- [ ] USB Mode: Hardware CDC and JTAG
- [ ] Port: [Your COM port]

### **Step 13: Verify Code**
- [ ] Click ✓ (checkmark) button
- [ ] Wait 1-2 minutes
- [ ] Should say "Done compiling"
- [ ] If errors, check libraries and TFT_eSPI config

### **Step 14: Flash to Watch**
- [ ] Click → (arrow) button
- [ ] DO NOT DISCONNECT WATCH
- [ ] Wait 2-3 minutes
- [ ] Should say "Done uploading"
- [ ] If hangs, hold BOOT button while uploading

### **Step 15: Verify It Works**
- [ ] Tools → Serial Monitor
- [ ] Set baud: 115200
- [ ] See boot messages
- [ ] Watch display shows "VOLT"
- [ ] Press button → LED lights up
- [ ] Display shows "Listening..."

---

## ✅ FINAL TESTS

### **Basic Tests:**
- [ ] Watch boots successfully
- [ ] Display clear and readable
- [ ] WiFi connects (shows "Ready to talk!")
- [ ] Button responds
- [ ] LED lights up
- [ ] Battery shows percentage

### **Voice Tests:**
- [ ] Press button once
- [ ] Say something
- [ ] VOLT responds with voice
- [ ] Speech is clear

### **All Button Patterns:**
- [ ] 1 press → Voice conversation
- [ ] 2 presses → Joke
- [ ] 3 presses → Breathing exercise
- [ ] Long press → Dad's message
- [ ] 5 presses → WiFi setup

---

## 🎉 SUCCESS!

### **If All Checked:**
- [ ] Disconnect USB cable
- [ ] Give watch to Stone
- [ ] Show him how to use it
- [ ] Watch him smile!
- [ ] You're an amazing dad! 🏆

---

## 🆘 IF PROBLEMS

### **Port Not Found:**
- Try different USB cable
- Try different USB port
- Install CH340 drivers
- Restart computer

### **Compilation Error:**
- Check all 6 files in folder
- Verify libraries installed
- Check TFT_eSPI config

### **Connecting Hangs:**
- Hold BOOT button while uploading
- Lower upload speed to 115200
- Try different cable

### **Display Blank:**
- Check TFT_eSPI configuration
- Reflash firmware

### **WiFi Won't Connect:**
- Check credentials (case-sensitive)
- Must be 2.4GHz (not 5GHz)
- Move closer to router

### **Voice Doesn't Work:**
- Check API key correct
- Verify WiFi connected
- Check API has credits

---

## 📞 FULL GUIDES

**For detailed help, see:**
- 3_WINDOW_FLASH_GUIDE.md (complete guide)
- EASY_FLASH_GUIDE.md (alternative methods)
- TESTING_CHECKLIST.md (150+ tests)

---

**Made with ❤️ by Dad for Stone**

*Print this checklist and check off each step as you go!*
