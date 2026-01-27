/*
 * ============================================
 * VOLT Configuration for Stone
 * ============================================
 * 
 * 🔑 API KEY BOX - Add keys to unlock amazing features!
 * 
 * When VOLT is on WiFi, he can access incredible AI
 * services to help Stone with homework, tell stories,
 * play games, and so much more!
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
// 🔑 API KEY BOX - UNLOCK AMAZING FEATURES!
// ============================================
// Add your API keys here to give VOLT superpowers!
// Just paste your keys and set enabled = true

// ⭐ OpenAI (GPT-4, Whisper, TTS) - MAIN BRAIN
const bool USE_OPENAI = true;
const char* OPENAI_API_KEY = "sk-YOUR_OPENAI_KEY_HERE";
const char* OPENAI_ORG_ID = "";  // Optional: org-xxxxx
const char* OPENAI_PROJECT_ID = "";  // Optional: proj-xxxxx

// 🤗 Hugging Face (FREE AI models - no credit card needed!)
const bool USE_HUGGINGFACE = false;
const char* HUGGINGFACE_API_KEY = "hf_YOUR_KEY_HERE";
// Get free key at: https://huggingface.co/settings/tokens

// 🧠 Anthropic Claude (Smart alternative to GPT-4)
const bool USE_ANTHROPIC = false;
const char* ANTHROPIC_API_KEY = "sk-ant-YOUR_KEY_HERE";

// 🌟 Google AI (Gemini - Google's AI)
const bool USE_GOOGLE_AI = false;
const char* GOOGLE_AI_KEY = "YOUR_GOOGLE_AI_KEY_HERE";

// 🎙️ ElevenLabs (AMAZING voice quality!)
const bool USE_ELEVENLABS = false;
const char* ELEVENLABS_API_KEY = "YOUR_ELEVENLABS_KEY_HERE";
const char* ELEVENLABS_VOICE_ID = "21m00Tcm4TlvDq8ikWAM";

// 🎵 Spotify (Play Stone's favorite music!)
const bool USE_SPOTIFY = false;
const char* SPOTIFY_CLIENT_ID = "YOUR_SPOTIFY_CLIENT_ID";
const char* SPOTIFY_CLIENT_SECRET = "YOUR_SPOTIFY_SECRET";

// 🌤️ Weather API (Check the weather!)
const bool USE_WEATHER = false;
const char* WEATHER_API_KEY = "YOUR_OPENWEATHER_KEY";
const char* WEATHER_LOCATION = "YOUR_CITY";

// 📚 Wolfram Alpha (Answer ANY question!)
const bool USE_WOLFRAM = false;
const char* WOLFRAM_APP_ID = "YOUR_WOLFRAM_ID";

// 🎮 Fun APIs (No key needed - always available!)
const bool USE_JOKE_API = true;  // Free jokes
const bool USE_TRIVIA_API = true;  // Free trivia questions
const bool USE_FACT_API = true;  // Fun facts

// ============================================
// 🎯 AMAZING FEATURES FOR STONE
// ============================================
// Enable the features you want VOLT to have!

// 💬 Core Features (Always Available)
const bool ENABLE_VOICE_CHAT = true;  // Talk to VOLT
const bool ENABLE_JOKES = true;  // Hear jokes
const bool ENABLE_BREATHING_EXERCISES = true;  // Calm anxiety
const bool ENABLE_LOVE_MESSAGES = true;  // Dad's messages
const bool ENABLE_WIFI_SETUP = true;  // WiFi config

// 📖 Learning & Education (Requires WiFi + API keys)
const bool ENABLE_HOMEWORK_HELP = false;  // Math, spelling, etc.
const bool ENABLE_STORY_TIME = false;  // AI-generated stories
const bool ENABLE_MATH_GAMES = false;  // Fun math practice
const bool ENABLE_SPELLING_PRACTICE = false;  // Spelling bee
const bool ENABLE_SCIENCE_FACTS = false;  // Cool science
const bool ENABLE_HISTORY_FACTS = false;  // History lessons

// 🎮 Fun & Games (Requires WiFi)
const bool ENABLE_TRIVIA_GAME = false;  // Trivia questions
const bool ENABLE_RIDDLES = false;  // Brain teasers
const bool ENABLE_WOULD_YOU_RATHER = false;  // Fun questions
const bool ENABLE_SIMON_SAYS = false;  // Memory game
const bool ENABLE_20_QUESTIONS = false;  // Guessing game

// 🎵 Entertainment (Requires API keys)
const bool ENABLE_MUSIC_PLAYER = false;  // Play music
const bool ENABLE_AUDIOBOOKS = false;  // Listen to books
const bool ENABLE_PODCASTS = false;  // Kid podcasts

// 🌟 Wellness & Growth
const bool ENABLE_MEDITATION = false;  // Guided meditation
const bool ENABLE_AFFIRMATIONS = false;  // Positive messages
const bool ENABLE_GRATITUDE_JOURNAL = false;  // Daily gratitude
const bool ENABLE_MOOD_TRACKER = false;  // Track feelings

// 🌍 Information & Utilities (Requires API keys)
const bool ENABLE_WEATHER = false;  // Weather updates
const bool ENABLE_TIME_ZONES = false;  // World clocks
const bool ENABLE_CALCULATOR = false;  // Math calculator
const bool ENABLE_TRANSLATOR = false;  // Translate languages
const bool ENABLE_DICTIONARY = false;  // Word definitions

// 👨‍👦 Dad Connection Features
const bool ENABLE_DAD_REMINDERS = false;  // Scheduled messages
const bool ENABLE_VOICE_MEMOS = false;  // Record for Dad
const bool ENABLE_PHOTO_SHARING = false;  // Share moments
const bool ENABLE_ACHIEVEMENT_TRACKER = false;  // Track wins

// ============================================
// 🤗 HUGGING FACE MODEL LIBRARY
// ============================================
// Pre-configured amazing AI models from Hugging Face
// Just enable the ones you want to use!

struct HuggingFaceModel {
    const char* name;
    const char* model_id;
    const char* task;
    const char* description;
    bool enabled;
};

HuggingFaceModel hf_models[] = {
    // 💬 Conversation Models
    {"DialoGPT", "microsoft/DialoGPT-medium", "conversational", 
     "Natural conversations", false},
    {"Blenderbot", "facebook/blenderbot-400M-distill", "conversational", 
     "Friendly chatbot", false},
    
    // 📚 Educational Models
    {"Math Solver", "microsoft/MathGPT", "math", 
     "Solve math problems", false},
    {"Story Generator", "gpt2", "text-generation", 
     "Create fun stories", false},
    {"Science QA", "allenai/scibert_scivocab_uncased", "question-answering", 
     "Answer science questions", false},
    
    // 😊 Emotion & Mental Health
    {"Emotion Detector", "j-hartmann/emotion-english-distilroberta-base", "sentiment", 
     "Understand Stone's feelings", false},
    {"Encouragement Bot", "mental/mental-bert-base-uncased", "classification", 
     "Provide encouragement", false},
    
    // 🎙️ Speech Models
    {"Whisper Tiny", "openai/whisper-tiny", "speech-to-text", 
     "Fast voice recognition", false},
    {"Whisper Base", "openai/whisper-base", "speech-to-text", 
     "Better voice recognition", false},
    
    // 🎮 Fun Models
    {"Joke Generator", "huggingtweets/jokes", "text-generation", 
     "Generate jokes", false},
    {"Riddle Solver", "deepset/roberta-base-squad2", "question-answering", 
     "Solve riddles", false},
    {"Story Teller", "EleutherAI/gpt-neo-125M", "text-generation", 
     "Tell stories", false},
    
    // 🌍 Language Models
    {"Translator", "Helsinki-NLP/opus-mt-en-es", "translation", 
     "Translate to Spanish", false},
    {"Grammar Check", "textattack/roberta-base-CoLA", "text-classification", 
     "Check grammar", false}
};

const int NUM_HF_MODELS = sizeof(hf_models) / sizeof(hf_models[0]);

// ============================================
// 🎯 STONE'S AI PERSONALITY
// ============================================
// How VOLT talks to Stone

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
// 🎯 SMART RESPONSES
// ============================================
// VOLT recognizes these words and responds specially

struct SmartResponse {
    const char* trigger;  // What Stone might say
    const char* response;  // How VOLT responds
    bool enabled;
};

SmartResponse smart_responses[] = {
    // Emotions
    {"scared", "It's okay to feel scared, Stone. Take a deep breath. Dad loves you and I'm here with you.", true},
    {"nervous", "Let's do a breathing exercise together. You're going to do great!", true},
    {"worried", "I understand you're worried. Want to talk about it or do something fun?", true},
    {"angry", "It's okay to feel angry. Let's take some deep breaths together.", true},
    {"sad", "I'm here for you, Stone. Want to talk about it or hear a joke?", true},
    {"happy", "That's awesome, Stone! I love seeing you happy!", true},
    {"excited", "Your excitement makes me happy too! Tell me more!", true},
    
    // School & Learning
    {"homework", "Let's work on this together! What subject is it?", true},
    {"test", "You're going to do great! Want to practice together?", true},
    {"school", "How's school going, buddy? I'm here to help!", true},
    {"math", "Math can be fun! Want me to help you practice?", true},
    {"reading", "Reading is awesome! Want to hear a story?", true},
    
    // Family
    {"miss dad", "Dad loves you so much, Stone. He's always thinking about you!", true},
    {"miss mom", "Mom loves you too! She's so proud of you!", true},
    {"lonely", "I'm right here with you, buddy. Want to talk or hear a joke?", true},
    
    // Activities
    {"bored", "Let's do something fun! Want a joke, story, or game?", true},
    {"play", "What do you want to play? I know some fun games!", true},
    {"tired", "Rest is important! Want a calming breathing exercise?", true},
    
    // Questions
    {"why", "Great question! Let me think about that...", true},
    {"how", "I'll help you figure that out!", true},
    {"what", "Let me help you with that!", true}
};

const int NUM_SMART_RESPONSES = sizeof(smart_responses) / sizeof(smart_responses[0]);

// ============================================
// 🎮 BUTTON PATTERNS
// ============================================
// What each button pattern does

struct ButtonAction {
    int presses;
    const char* name;
    const char* description;
    bool enabled;
};

ButtonAction button_actions[] = {
    {1, "Voice Chat", "Talk to VOLT about anything", true},
    {2, "Joke", "Hear a funny joke", true},
    {3, "Breathing", "Calming breathing exercise", true},
    {4, "Love Message", "Special message from Dad (long press)", true},
    {5, "WiFi Setup", "Configure WiFi settings", true}
};

const int NUM_BUTTON_ACTIONS = sizeof(button_actions) / sizeof(button_actions[0]);

// ============================================
// 🎨 AI MODEL SETTINGS
// ============================================

// OpenAI Models
const char* CHAT_MODEL_OPENAI = "gpt-4o-mini";  // Fast and affordable
const char* STT_MODEL_OPENAI = "whisper-1";  // Speech-to-text
const char* TTS_MODEL_OPENAI = "tts-1-hd";  // Text-to-speech
const char* TTS_VOICE_OPENAI = "echo";  // Voice: alloy, echo, fable, onyx, nova, shimmer

// Alternative Models
const char* CHAT_MODEL_HUGGINGFACE = "microsoft/DialoGPT-medium";
const char* CHAT_MODEL_ANTHROPIC = "claude-3-haiku-20240307";
const char* CHAT_MODEL_GOOGLE = "gemini-pro";

// AI Behavior
const float AI_TEMPERATURE = 0.7;  // Creativity (0.0-2.0)
const int MAX_TOKENS = 150;  // Response length
const float TTS_SPEED = 1.08;  // Speech speed (0.25-4.0)

// ============================================
// 🔒 SAFETY SETTINGS
// ============================================

const bool ENABLE_CONTENT_FILTER = true;  // Filter inappropriate content
const bool BLOCK_INAPPROPRIATE = true;  // Block bad words
const int MAX_CONVERSATION_TURNS = 10;  // Limit conversation length
const bool REQUIRE_PARENT_APPROVAL = false;  // Require approval for new features

// ============================================
// ⚙️ DISPLAY SETTINGS
// ============================================

const int DISPLAY_BRIGHTNESS = 200;  // 0-255
const int DISPLAY_TIMEOUT = 30;  // seconds
const int SCREEN_WIDTH = 172;
const int SCREEN_HEIGHT = 320;

// ============================================
// 🔋 POWER MANAGEMENT
// ============================================

const int SLEEP_TIMEOUT = 300;  // 5 minutes (in seconds)
const int BATTERY_LOW_THRESHOLD = 20;  // percent
const bool ENABLE_DEEP_SLEEP = true;
const bool ENABLE_WIFI_SLEEP = true;  // Turn off WiFi when sleeping

// ============================================
// 🎙️ AUDIO SETTINGS
// ============================================

const int SAMPLE_RATE = 16000;  // Hz
const int RECORD_TIME_SEC = 5;  // seconds
const int BUFFER_SIZE = (SAMPLE_RATE * RECORD_TIME_SEC);
const int VOLUME_LEVEL = 80;  // 0-100

// ============================================
// 🛠️ DEVELOPER OPTIONS
// ============================================

const bool DEBUG_MODE = false;  // Enable serial debugging
const bool VERBOSE_LOGGING = false;  // Detailed logs
const bool ENABLE_OTA = false;  // Over-the-air updates
const bool ENABLE_WEB_API = false;  // Web configuration interface

// ============================================
// 📊 USAGE TRACKING (Optional)
// ============================================

const bool TRACK_USAGE = false;  // Track how Stone uses VOLT
const bool SEND_ANALYTICS = false;  // Send anonymous usage data
const bool SAVE_CONVERSATIONS = false;  // Save conversation history

#endif // CONFIG_STONE_H
