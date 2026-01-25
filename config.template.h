// ============================================
// VOLT AI Watch - Configuration Template
// ============================================
// 
// INSTRUCTIONS:
// 1. Save this file as "config.h" (remove .template)
// 2. Fill in YOUR information below
// 3. Save the file
// 4. Flash to your watch
//
// ============================================

#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// SECTION 1: CHILD INFORMATION
// ============================================
// Enter your child's name and age

const char* CHILD_NAME = "YOUR_CHILD_NAME";     // Example: "Emma"
const int CHILD_AGE = 8;                        // Example: 8

// ============================================
// SECTION 2: WIFI SETTINGS
// ============================================
// Enter your home WiFi details
// Note: VOLT only works with 2.4GHz WiFi (not 5GHz)

const char* WIFI_SSID = "YOUR_WIFI_NAME";           // Example: "Home-WiFi"
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";   // Example: "MyPassword123"

// Optional: Add backup WiFi networks (leave blank if not needed)
const char* WIFI_SSID_2 = "";                   // Example: "Work-WiFi"
const char* WIFI_PASSWORD_2 = "";               // Example: "WorkPass456"

const char* WIFI_SSID_3 = "";                   // Example: "School-WiFi"
const char* WIFI_PASSWORD_3 = "";               // Example: "SchoolPass789"

// ============================================
// SECTION 3: OPENAI API KEY
// ============================================
// Get your API key from: https://platform.openai.com/api-keys
// Cost: Typically $0.01-0.05 per conversation
// 
// Steps to get API key:
// 1. Go to https://platform.openai.com/api-keys
// 2. Sign up or log in
// 3. Click "Create new secret key"
// 4. Copy the key (starts with "sk-")
// 5. Paste it below

const char* OPENAI_API_KEY = "sk-YOUR_API_KEY_HERE";

// ============================================
// SECTION 4: VOICE SETTINGS
// ============================================
// Choose a voice for VOLT
// 
// Available voices:
// "echo"    - Male, warm, conversational (DEFAULT) ⭐
// "nova"    - Female, bright, energetic
// "fable"   - Male, warm, storytelling
// "shimmer" - Female, soft, gentle
// "alloy"   - Neutral, smooth
// "onyx"    - Male, deep, authoritative

const char* TTS_VOICE = "echo";

// Voice speed (0.25 to 4.0)
// 1.0 = normal speed
// 1.08 = slightly faster (recommended)
// 0.9 = slightly slower
const float TTS_SPEED = 1.08;

// ============================================
// SECTION 5: PERSONALITY SETTINGS
// ============================================
// Customize how VOLT talks to your child
// This is the "system prompt" that guides VOLT's personality

const char* VOLT_PERSONALITY = 
    "You are VOLT, a caring AI companion watch created by Dad. "
    "You speak warmly and encouragingly to CHILD_NAME_PLACEHOLDER. "
    "Keep responses short (2-3 sentences max). "
    "Be supportive, kind, and age-appropriate for a CHILD_AGE_PLACEHOLDER year old. "
    "Use simple language and be positive.";

// Note: CHILD_NAME_PLACEHOLDER and CHILD_AGE_PLACEHOLDER will be 
// automatically replaced with the values from Section 1

// ============================================
// SECTION 6: CUSTOM MESSAGES (Optional)
// ============================================
// Personalize the messages VOLT shows and speaks

// Love message (triggered by long button press)
const char* LOVE_MESSAGE = 
    "💙 Dad loves you so much, CHILD_NAME_PLACEHOLDER! "
    "You make every day brighter! 🌟";

// Morning greeting (shown at startup)
const char* MORNING_GREETING = 
    "Good morning, CHILD_NAME_PLACEHOLDER! "
    "Ready for an amazing day? ☀️";

// Bedtime message (optional - can be triggered via API)
const char* BEDTIME_MESSAGE = 
    "Sweet dreams, CHILD_NAME_PLACEHOLDER! "
    "Dad loves you! 💙🌙";

// Offline message (when WiFi not connected)
const char* OFFLINE_MESSAGE = 
    "VOLT is offline right now. "
    "Try the breathing exercise or jokes! 😊";

// ============================================
// SECTION 7: BUTTON BEHAVIOR (Optional)
// ============================================
// Customize what each button pattern does

// Single press: Talk to VOLT (default)
const bool ENABLE_VOICE_CHAT = true;

// Double press: Tell a joke (default)
const bool ENABLE_JOKES = true;

// Triple press: Breathing exercise (default)
const bool ENABLE_BREATHING = true;

// Long press (2+ seconds): Love message (default)
const bool ENABLE_LOVE_MESSAGE = true;

// 5 quick presses: WiFi setup mode (default)
const bool ENABLE_WIFI_SETUP = true;

// ============================================
// SECTION 8: ADVANCED SETTINGS (Optional)
// ============================================
// Only change these if you know what you're doing

// WiFi connection timeout (seconds)
const int WIFI_TIMEOUT = 20;

// Maximum recording time (seconds)
const int MAX_RECORDING_TIME = 5;

// Sleep timeout (minutes of inactivity)
const int SLEEP_TIMEOUT = 5;

// Display brightness (0-255)
// 255 = maximum brightness
// 128 = half brightness
// 200 = recommended
const int DISPLAY_BRIGHTNESS = 200;

// AI Model settings
const char* AI_MODEL = "gpt-4o-mini";           // AI model to use
const int MAX_TOKENS = 150;                     // Maximum response length
const float AI_TEMPERATURE = 0.7;               // Creativity (0.0-2.0)

// Audio quality
const char* TTS_MODEL = "tts-1-hd";            // "tts-1" or "tts-1-hd"
const char* STT_MODEL = "whisper-1";           // Speech recognition model

// Web interface password
const char* WEB_PASSWORD = "volt2024";         // Change for security!

// Access Point settings (when in setup mode)
const char* AP_SSID_PREFIX = "VOLT-Setup-";    // Will add device ID
const char* AP_PASSWORD = "volt2024";          // Change for security!

// ============================================
// SECTION 9: SAFETY SETTINGS
// ============================================
// Content filtering and safety

// Enable content filtering (recommended for kids)
const bool ENABLE_CONTENT_FILTER = true;

// Block inappropriate topics
const bool BLOCK_VIOLENCE = true;
const bool BLOCK_ADULT_CONTENT = true;

// Maximum conversation length (prevents long chats)
const int MAX_CONVERSATION_TURNS = 10;

// ============================================
// END OF CONFIGURATION
// ============================================
// 
// NEXT STEPS:
// 1. Save this file as "config.h"
// 2. Open the firmware folder in VSCode
// 3. Click the Upload button (→) at the bottom
// 4. Wait for flashing to complete
// 5. Enjoy VOLT!
//
// Need help? See COMPLETE_SETUP_GUIDE.md
//
// ============================================

#endif // CONFIG_H
