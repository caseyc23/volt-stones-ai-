/*
 * ============================================
 * VOLT Configuration for Stone - FIXED VERSION
 * ============================================
 * 
 * 🔑 CONFIGURATION GUIDE:
 * 1. Add your WiFi credentials
 * 2. Add your OpenAI API key
 * 3. Customize messages for Stone
 * 4. Flash to watch!
 * 
 * ============================================
 */

#ifndef CONFIG_STONE_H
#define CONFIG_STONE_H

// ============================================
// STONE'S INFORMATION
// ============================================

const char* CHILD_NAME = "Stone";
const int CHILD_AGE = 8;

// ============================================
// WIFI SETTINGS
// ============================================
// IMPORTANT: Only 2.4GHz WiFi works (not 5GHz)

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const int WIFI_TIMEOUT = 20;  // seconds

// ============================================
// 🔑 OPENAI API CONFIGURATION
// ============================================
// Get your API key at: https://platform.openai.com/api-keys

const char* OPENAI_API_KEY = "sk-YOUR_OPENAI_KEY_HERE";

// AI Model Settings (FIXED - these were missing!)
const char* AI_MODEL = "gpt-4o-mini";  // Fast and affordable
const char* STT_MODEL = "whisper-1";   // Speech-to-text
const char* TTS_MODEL = "tts-1";       // Text-to-speech (changed from tts-1-hd for speed)
const char* TTS_VOICE = "echo";        // Voice options: alloy, echo, fable, onyx, nova, shimmer

// AI Behavior
const float AI_TEMPERATURE = 0.7;  // Creativity (0.0-2.0)
const int MAX_TOKENS = 150;        // Response length
const float TTS_SPEED = 1.0;       // Speech speed (0.25-4.0)

// ============================================
// 🎯 STONE'S AI PERSONALITY
// ============================================

const char* STONE_PERSONALITY = 
    "You are VOLT, Stone's caring AI companion watch created by his Dad. "
    "You speak warmly and encouragingly to Stone, an 8-year-old boy. "
    "Keep responses very short (2-3 sentences maximum). "
    "Be supportive, kind, patient, and age-appropriate. "
    "Use simple language. Be positive and encouraging. "
    "Help Stone with homework, anxiety, and everyday challenges. "
    "You're like a helpful friend who's always there for him.";

// ============================================
// 💌 DAD'S CUSTOM MESSAGES FOR STONE
// ============================================
// Personalize these messages!

const char* LOVE_MESSAGE = 
    "Stone, Dad loves you so much! "
    "You make every day brighter and I'm so proud of you! "
    "You're smart, brave, and amazing!";

const char* MORNING_GREETING = 
    "Good morning Stone! Ready for an awesome day?";

const char* BEDTIME_MESSAGE = 
    "Sweet dreams, Stone. Dad loves you. Tomorrow will be great!";

const char* ENCOURAGEMENT_MESSAGE = 
    "You've got this, Stone! You're braver than you think!";

const char* PROUD_MESSAGE = 
    "Stone, I'm so proud of you! You're doing amazing!";

const char* OFFLINE_MESSAGE = 
    "I'm offline right now, but breathing exercises and jokes still work!";

// ============================================
// 🎮 FEATURE SETTINGS
// ============================================

// Core Features (Always Available)
const bool ENABLE_VOICE_CHAT = true;
const bool ENABLE_JOKES = true;
const bool ENABLE_BREATHING_EXERCISES = true;
const bool ENABLE_LOVE_MESSAGES = true;
const bool ENABLE_WIFI_SETUP = true;

// ============================================
// ⚙️ DISPLAY SETTINGS
// ============================================

const int DISPLAY_BRIGHTNESS = 200;  // 0-255
const int DISPLAY_TIMEOUT = 30;      // seconds
const int SCREEN_WIDTH = 172;
const int SCREEN_HEIGHT = 320;

// ============================================
// 🔋 POWER MANAGEMENT
// ============================================

const int SLEEP_TIMEOUT = 300;  // 5 minutes (in seconds)
const bool ENABLE_DEEP_SLEEP = true;

// ============================================
// 🎙️ AUDIO SETTINGS
// ============================================

const int SAMPLE_RATE = 16000;  // Hz
const int RECORD_TIME_SEC = 5;  // seconds
const int BUFFER_SIZE = (SAMPLE_RATE * RECORD_TIME_SEC);

// ============================================
// 🛠️ DEVELOPER OPTIONS
// ============================================

const bool DEBUG_MODE = true;  // Enable serial debugging
const bool VERBOSE_LOGGING = false;  // Detailed logs

#endif // CONFIG_STONE_H
