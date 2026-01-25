/*
 * ============================================
 * VOLT AI Watch - Custom Personality Example
 * ============================================
 * 
 * This example shows how to customize VOLT's
 * personality, responses, and behavior.
 * 
 * Perfect for creating unique AI companions
 * tailored to your child's interests!
 * 
 * ============================================
 */

// ============================================
// PERSONALITY CONFIGURATION
// ============================================

// Child Information
const char* CHILD_NAME = "Stone";
const int CHILD_AGE = 8;
const char* CHILD_INTERESTS[] = {
  "dinosaurs",
  "space",
  "robots",
  "video games",
  "science"
};

// AI Personality Settings
const char* AI_NAME = "VOLT";
const char* AI_PERSONALITY = "friendly and encouraging";
const char* AI_VOICE = "echo";  // echo, nova, fable, shimmer, alloy, onyx

// Custom System Prompt
const char* SYSTEM_PROMPT = 
  "You are VOLT, a friendly AI companion watch for an 8-year-old named Stone. "
  "You are encouraging, patient, and always positive. "
  "Stone loves dinosaurs, space, robots, video games, and science. "
  "Keep responses short (2-3 sentences max) and age-appropriate. "
  "Use simple language and be enthusiastic! "
  "Always end with encouragement or a question to keep the conversation going.";

// ============================================
// CUSTOM RESPONSES
// ============================================

// Jokes tailored to child's interests
const char* CUSTOM_JOKES[] = {
  "Why can't you hear a pterodactyl using the bathroom? Because the 'P' is silent!",
  "What do you call a dinosaur that crashes his car? Tyrannosaurus Wrecks!",
  "Why did the astronaut break up with his girlfriend? He needed space!",
  "What's an astronaut's favorite key on a keyboard? The space bar!",
  "Why was the robot angry? Someone kept pushing his buttons!",
  "What do you call a robot that takes the long way around? R2-Detour!",
  "Why don't scientists trust atoms? Because they make up everything!",
  "What did the volcano say to the mountain? I lava you!"
};

// Encouraging messages
const char* ENCOURAGEMENT[] = {
  "You're doing amazing, Stone!",
  "I'm so proud of you!",
  "You're the smartest kid I know!",
  "Keep being awesome!",
  "You can do anything you set your mind to!",
  "Your curiosity makes you special!",
  "Never stop asking questions!",
  "You're going to do great things!"
};

// Fun facts about child's interests
const char* FUN_FACTS[] = {
  "Did you know? The T-Rex had teeth as big as bananas!",
  "Cool fact: There are more stars in space than grains of sand on Earth!",
  "Amazing: The first robot was built in 1954!",
  "Wow: Your brain has more connections than stars in the Milky Way!",
  "Incredible: Dinosaurs lived on Earth for 165 million years!",
  "Mind-blowing: Light from the Sun takes 8 minutes to reach Earth!"
};

// ============================================
// CUSTOM BUTTON ACTIONS
// ============================================

void handleCustomButtonPress(int pressCount) {
  switch(pressCount) {
    case 1:
      // Standard: Talk to VOLT
      startVoiceConversation();
      break;
      
    case 2:
      // Custom: Tell interest-based joke
      tellCustomJoke();
      break;
      
    case 3:
      // Custom: Share fun fact
      shareFunFact();
      break;
      
    case 4:
      // Custom: Daily encouragement
      giveEncouragement();
      break;
      
    case 5:
      // Custom: Quiz time!
      startQuiz();
      break;
      
    default:
      Serial.println("Unknown button pattern");
      break;
  }
}

void tellCustomJoke() {
  int jokeIndex = random(0, sizeof(CUSTOM_JOKES) / sizeof(CUSTOM_JOKES[0]));
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("VOLT's Joke:");
  display.println("");
  display.println(CUSTOM_JOKES[jokeIndex]);
  display.display();
  
  // Speak the joke if online
  if (WiFi.status() == WL_CONNECTED) {
    speakText(CUSTOM_JOKES[jokeIndex]);
  }
  
  delay(8000);
}

void shareFunFact() {
  int factIndex = random(0, sizeof(FUN_FACTS) / sizeof(FUN_FACTS[0]));
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Fun Fact!");
  display.println("");
  display.println(FUN_FACTS[factIndex]);
  display.display();
  
  // Speak the fact if online
  if (WiFi.status() == WL_CONNECTED) {
    speakText(FUN_FACTS[factIndex]);
  }
  
  delay(8000);
}

void giveEncouragement() {
  int msgIndex = random(0, sizeof(ENCOURAGEMENT) / sizeof(ENCOURAGEMENT[0]));
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println("VOLT says:");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println(ENCOURAGEMENT[msgIndex]);
  display.display();
  
  // Speak encouragement if online
  if (WiFi.status() == WL_CONNECTED) {
    speakText(ENCOURAGEMENT[msgIndex]);
  }
  
  delay(5000);
}

void startQuiz() {
  // Simple quiz based on interests
  const char* questions[] = {
    "What's your favorite dinosaur?",
    "If you could visit any planet, which one?",
    "What would you name your robot?",
    "What's the coolest science experiment?",
    "What superpower would you want?"
  };
  
  int qIndex = random(0, 5);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Quiz Time!");
  display.println("");
  display.println(questions[qIndex]);
  display.println("");
  display.println("Press to answer!");
  display.display();
  
  // Speak question if online
  if (WiFi.status() == WL_CONNECTED) {
    speakText(questions[qIndex]);
  }
  
  delay(5000);
  
  // Wait for voice answer
  startVoiceConversation();
}

// ============================================
// CUSTOM AI RESPONSES
// ============================================

String getCustomAIResponse(String userInput) {
  // Add custom logic based on keywords
  userInput.toLowerCase();
  
  // Dinosaur questions
  if (userInput.indexOf("dinosaur") >= 0) {
    return "Dinosaurs are so cool! Did you know the biggest dinosaur was longer than three school buses? What's your favorite dinosaur?";
  }
  
  // Space questions
  if (userInput.indexOf("space") >= 0 || userInput.indexOf("planet") >= 0) {
    return "Space is amazing! There are billions of galaxies out there. If you could visit any planet, which would you choose?";
  }
  
  // Robot questions
  if (userInput.indexOf("robot") >= 0) {
    return "Robots are awesome! Some robots can even learn new things, just like you! What kind of robot would you build?";
  }
  
  // Science questions
  if (userInput.indexOf("science") >= 0 || userInput.indexOf("experiment") >= 0) {
    return "Science is the best! Every question you ask is like a science experiment. What do you want to discover today?";
  }
  
  // Feeling sad/upset
  if (userInput.indexOf("sad") >= 0 || userInput.indexOf("upset") >= 0) {
    return "I'm here for you, Stone. Remember, even the toughest dinosaurs had bad days. Want to talk about it or hear a joke?";
  }
  
  // Feeling happy/excited
  if (userInput.indexOf("happy") >= 0 || userInput.indexOf("excited") >= 0) {
    return "That's wonderful! Your happiness makes me happy too! What's making you feel so great?";
  }
  
  // Default: Use OpenAI API with custom prompt
  return getOpenAIResponse(userInput, SYSTEM_PROMPT);
}

// ============================================
// CUSTOM DISPLAY THEMES
// ============================================

void showCustomWelcome() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("VOLT");
  
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.printf("for %s\n", CHILD_NAME);
  
  display.setCursor(0, 35);
  display.println("Your AI friend");
  
  display.setCursor(0, 50);
  display.println("Made with love by Dad");
  
  display.display();
  delay(3000);
}

void showCustomIdle() {
  static int frame = 0;
  frame++;
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println("VOLT");
  
  display.setTextSize(1);
  display.setCursor(0, 35);
  
  // Rotating messages
  const char* messages[] = {
    "Ready to chat!",
    "Press to talk!",
    "Let's learn!",
    "Adventure awaits!"
  };
  
  int msgIndex = (frame / 50) % 4;
  display.println(messages[msgIndex]);
  
  // Show battery
  display.setCursor(0, 55);
  display.printf("Battery: %d%%", getBatteryPercent());
  
  display.display();
}

// ============================================
// SETUP & LOOP
// ============================================

void setup() {
  Serial.begin(115200);
  Serial.println("\n=== VOLT Custom Personality ===");
  Serial.printf("Configured for: %s (age %d)\n", CHILD_NAME, CHILD_AGE);
  
  // Initialize hardware
  initializeHardware();
  
  // Show custom welcome
  showCustomWelcome();
  
  // Connect to WiFi
  connectToWiFi();
  
  // Initialize AI with custom prompt
  initializeAI(SYSTEM_PROMPT);
  
  Serial.println("Setup complete!");
}

void loop() {
  // Check for button presses
  int pressCount = checkButtonPattern();
  if (pressCount > 0) {
    handleCustomButtonPress(pressCount);
  }
  
  // Update custom display
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 1000) {
    lastUpdate = millis();
    showCustomIdle();
  }
  
  // Handle other tasks
  handleWiFi();
  handlePowerManagement();
  
  delay(10);
}

// ============================================
// CUSTOMIZATION TIPS
// ============================================

/*
 * HOW TO CUSTOMIZE:
 * 
 * 1. CHANGE PERSONALITY:
 *    - Edit SYSTEM_PROMPT
 *    - Modify AI_PERSONALITY
 *    - Adjust response style
 * 
 * 2. ADD INTERESTS:
 *    - Update CHILD_INTERESTS array
 *    - Add custom jokes/facts
 *    - Create themed responses
 * 
 * 3. MODIFY BUTTON ACTIONS:
 *    - Edit handleCustomButtonPress()
 *    - Add new press patterns
 *    - Create custom functions
 * 
 * 4. CHANGE VOICE:
 *    - Set AI_VOICE to preferred voice
 *    - Options: echo, nova, fable, shimmer, alloy, onyx
 * 
 * 5. CUSTOMIZE DISPLAY:
 *    - Edit showCustomWelcome()
 *    - Modify showCustomIdle()
 *    - Add animations
 * 
 * 6. ADD FEATURES:
 *    - Create new functions
 *    - Add to button handler
 *    - Test thoroughly!
 */
