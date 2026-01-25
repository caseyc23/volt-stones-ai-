# ⚡ VOLT - AI Companion Watch for Kids

**Give your child a caring AI companion that fits on their wrist!**

VOLT is an AI-powered watch that talks with your child, delivers love messages from parents, helps with breathing exercises, tells jokes, and more - all while being safe and parent-controlled.

---

## 🎯 What is VOLT?

VOLT is a **wearable AI companion** designed for children. It combines:

- 💬 **Natural conversation** using OpenAI's GPT-4
- 🎤 **Voice recognition** to understand your child
- 🔊 **Text-to-speech** with 6 different voices
- 💙 **Personalized messages** from parents
- 📶 **WiFi connectivity** for easy setup
- 🔒 **Parent-controlled** and safe for kids

---

## ✨ Features

### For Kids:

- 🗣️ **Talk to VOLT** - Press button and have a conversation
- 😄 **Jokes & Stories** - Double-press for entertainment
- 🧘 **Breathing Exercises** - Triple-press for calm moments
- 💙 **Love Messages** - Long-press to hear from parents
- 🎨 **Personalized** - Knows their name and age

### For Parents:

- 🛠️ **Easy Setup** - 30-minute installation
- 🌐 **Web Interface** - Configure via browser
- 📱 **WiFi Manager** - Store multiple networks
- 🔧 **Customizable** - Adjust personality, messages, voice
- 💰 **Low Cost** - ~$0.01-0.05 per conversation

---

## 🚀 Quick Start (30 Minutes)

### What You Need:

- ✅ **ESP32-S3 Watch** (VOLT hardware)
- ✅ **Computer** (Windows/Mac/Linux)
- ✅ **USB Cable** (data cable, not charge-only)
- ✅ **WiFi Network** (2.4GHz)
- ✅ **OpenAI API Key** ([Get one here](https://platform.openai.com/api-keys))

### 4 Simple Steps:

#### 1️⃣ Install Software (15 minutes)

- Download and install [VSCode](https://code.visualstudio.com/)
- Install **PlatformIO** extension in VSCode (Ctrl+Shift+X → search "PlatformIO IDE")
- Download and install [CP210x USB drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
- **Restart your computer**

#### 2️⃣ Customize for Your Child (10 minutes)

**Choose ONE method:**

**Method A: Web Configurator** (Easiest) ⭐

1. Open `configurator.html` in your browser
2. Fill in the form with your child's info
3. Click "Generate config.h"
4. Download the file
5. Place it in the firmware folder

**Method B: Setup Wizard** (Command Line)

1. Run `python setup_wizard.py`
2. Answer the questions
3. File is automatically created

**Method C: Manual** (Advanced)

1. Open `config.template.h`
2. Save as `config.h`
3. Fill in your information
4. Save the file

#### 3️⃣ Flash to Watch (5 minutes)

1. Open firmware folder in VSCode (File → Open Folder)
2. Connect watch via USB
3. Click **Upload button (→)** at bottom of VSCode
4. Wait for completion (1-2 minutes)

#### 4️⃣ Enjoy! ⚡

- Watch reboots automatically
- Connects to WiFi
- Ready for your child to use!

---

## 📦 What's Included

```
volt-ai-watch/
├── 📄 README.md                    ← You are here!
├── 📄 COMPLETE_FLASHING_PLATFORM_GUIDE.md
├── 📄 FIX_VOLT_CONNECTION.md
├── 📄 VOLT_CONNECTION_TROUBLESHOOTING.md
├── 📄 HOW_TO_FLASH.md
├── 📄 HARDWARE_TESTING_CHECKLIST.md
├── 📄 VOICE_OPTIONS.md
│
├── 🛠️ config.template.h           ← Template to customize
├── 🛠️ setup_wizard.py             ← Python configurator
├── 🛠️ configurator.html           ← Web configurator
│
└── 📁 firmware/                   ← (Download separately)
    ├── platformio.ini
    ├── volt_firmware.ino
    └── ... (other firmware files)
```

---

## 🎨 Customization Options

### Child Information

- Name and age
- Personalized greetings
- Age-appropriate responses

### Voice Selection

Choose from 6 voices:

- **Echo** ⭐ - Male, warm, conversational (default)
- **Nova** - Female, bright, energetic
- **Fable** - Male, warm, storytelling
- **Shimmer** - Female, soft, gentle
- **Alloy** - Neutral, smooth
- **Onyx** - Male, deep, authoritative

### Custom Messages

- Love messages from parents
- Morning greetings
- Bedtime messages
- Offline messages

### WiFi Networks

- Store up to 5 networks
- Automatic fallback
- Priority-based connection

---

## 🎮 How to Use

### Button Controls:

| Presses             | Action                    |
| ------------------- | ------------------------- |
| **1 press**         | Talk to VOLT              |
| **2 presses**       | Tell a joke               |
| **3 presses**       | Breathing exercise        |
| **Long press**      | Love message from parents |
| **5 quick presses** | WiFi setup mode           |

### First Time Setup:

After flashing, VOLT automatically enters WiFi setup mode:

1. On your phone, connect to WiFi: `VOLT-Setup-XXXX`
2. Password: `volt2024`
3. Open browser to: `http://192.168.4.1`
4. Scan and add your WiFi network
5. Restart watch
6. Done!

---

## 💰 Cost Breakdown

### One-Time Costs:

- **ESP32-S3 Watch Hardware**: $30-50 (varies by supplier)
- **USB Cable**: $5-10 (if you don't have one)

### Ongoing Costs:

- **OpenAI API Usage**: ~$0.01-0.05 per conversation
  - Example: 100 conversations/month = $1-5/month
  - You only pay for what you use
  - Set spending limits in OpenAI dashboard

### Free:

- ✅ Software (VSCode, PlatformIO)
- ✅ Firmware (open source)
- ✅ Updates and improvements

---

## 🔒 Safety & Privacy

### Built-in Safety Features:

- ✅ **Content filtering** enabled by default
- ✅ **Age-appropriate** responses
- ✅ **Parent-controlled** settings
- ✅ **No data collection** - conversations not stored
- ✅ **Local processing** where possible
- ✅ **Secure WiFi** connection

### What Parents Control:

- ✅ All messages and personality
- ✅ WiFi networks
- ✅ API key and usage limits
- ✅ Voice and speed
- ✅ Button behaviors
- ✅ Content filters

---

## 🆘 Troubleshooting

### Watch Won't Connect?

- See [FIX_VOLT_CONNECTION.md](FIX_VOLT_CONNECTION.md)
- Install CP210x drivers
- Try different USB port/cable
- Hold BOOT button during upload

### WiFi Won't Connect?

- Ensure 2.4GHz WiFi (not 5GHz)
- Check password (case-sensitive)
- Move closer to router
- Use WiFi setup mode (5 quick presses)

### No Sound?

- Check volume settings
- Verify OpenAI API key
- Check WiFi connection
- Test with offline features (jokes, breathing)

### More Help:

- 📖 [Complete Troubleshooting Guide](VOLT_CONNECTION_TROUBLESHOOTING.md)
- 📖 [Hardware Testing Checklist](HARDWARE_TESTING_CHECKLIST.md)
- 📖 [How to Flash Guide](HOW_TO_FLASH.md)

---

## 📚 Documentation

### Getting Started:

- **[README.md](README.md)** - Overview (you are here!)
- **[HOW_TO_FLASH.md](HOW_TO_FLASH.md)** - Flashing instructions
- **[COMPLETE_FLASHING_PLATFORM_GUIDE.md](COMPLETE_FLASHING_PLATFORM_GUIDE.md)** - Complete platform guide

### Configuration:

- **[config.template.h](config.template.h)** - Configuration template
- **[VOICE_OPTIONS.md](VOICE_OPTIONS.md)** - Voice selection guide
- **[setup_wizard.py](setup_wizard.py)** - Python configurator
- **[configurator.html](configurator.html)** - Web configurator

### Troubleshooting:

- **[FIX_VOLT_CONNECTION.md](FIX_VOLT_CONNECTION.md)** - Connection fixes
- **[VOLT_CONNECTION_TROUBLESHOOTING.md](VOLT_CONNECTION_TROUBLESHOOTING.md)** - Complete troubleshooting
- **[HARDWARE_TESTING_CHECKLIST.md](HARDWARE_TESTING_CHECKLIST.md)** - Testing guide

---

## 🌟 Success Stories

> _"My 8-year-old son loves talking to VOLT! It's like having a caring friend on his wrist."_ - Dad who created VOLT for Stone

> _"The breathing exercises help my daughter calm down before bed."_ - Parent

> _"Setup was easier than I expected. The web configurator made it simple!"_ - First-time user

---

## 🤝 Contributing

Want to improve VOLT? Contributions welcome!

- 🐛 Report bugs via GitHub Issues
- 💡 Suggest features
- 📝 Improve documentation
- 🔧 Submit code improvements

---

## 📜 License

**MIT License** - Free to use, modify, and share!

You can:

- ✅ Use for personal projects
- ✅ Modify the code
- ✅ Share with others
- ✅ Use commercially

Just keep the license notice and give credit.

---

## 🙏 Credits

### Created By:

- **Original Creator**: A dad who wanted to give his son an AI companion

### Powered By:

- **OpenAI** - GPT-4, Whisper, TTS
- **ESP32-S3** - Hardware platform
- **PlatformIO** - Development platform
- **VSCode** - Code editor

### Special Thanks:

- All parents who want to stay connected with their kids
- The open-source community
- Everyone who contributes and improves VOLT

---

## 📞 Support

### Need Help?

1. Check the documentation files
2. Review troubleshooting guides
3. Search existing GitHub Issues
4. Create a new Issue if needed

### Want to Share?

- Share your VOLT setup on social media
- Help other parents get started
- Contribute improvements
- Spread the love! 💙

---

## 🎯 Next Steps

Ready to get started?

1. ✅ **Download firmware** from the repository
2. ✅ **Install software** (VSCode, PlatformIO, drivers)
3. ✅ **Get OpenAI API key** from platform.openai.com
4. ✅ **Customize config** using web configurator
5. ✅ **Flash to watch** and enjoy!

---

## 💙 Philosophy

VOLT was created with love by a dad for his son. The goal is simple:

> **Help parents stay connected with their children through technology that cares.**

Every feature is designed with:

- ❤️ **Love** - Strengthening parent-child bonds
- 🛡️ **Safety** - Age-appropriate and parent-controlled
- 🎯 **Simplicity** - Easy to use for everyone
- 🌟 **Joy** - Making kids smile every day

---

**Version:** 5.00 - WiFi Manager & API Edition  
**Status:** ✅ Ready to Use  
**Made with:** 💙 Love

---

## 🎉 Ready to Begin?

**Everything you need is included. Let's give your child an AI companion!**

Start with: [HOW_TO_FLASH.md](HOW_TO_FLASH.md)

**Happy flashing!** ⚡💙

---

_VOLT - Because every child deserves to feel loved and supported, even when parents can't be there in person._
