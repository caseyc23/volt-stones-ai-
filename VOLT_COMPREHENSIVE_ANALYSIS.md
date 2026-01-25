# 🔍 VOLT Comprehensive Analysis & Enhancement Report

**Analysis Date:** 2024  
**Analyzed By:** BLACKBOXAI  
**Purpose:** Deep analysis of VOLT logic against best practices in voice AI, sports psychology, and child psychology

---

## 📋 Executive Summary

This report provides a comprehensive analysis of the VOLT AI Watch system, comparing current implementation against:

1. **Best-in-class voice AI agents** (Alexa, Google Assistant, Replika, Pi)
2. **Sports psychology principles** for youth athletes
3. **Child psychology best practices** for 8-year-olds
4. **Parental connection and emotional support** systems

### Overall Assessment: ⭐⭐⭐ (3/5 Stars)

**Strengths:**

- ✅ Solid technical foundation (WiFi, OTA, power management)
- ✅ Age-appropriate voice interaction
- ✅ Customizable personality system
- ✅ Safety features and content filtering

**Critical Gaps Identified:**

- ❌ **No sports psychology integration** (primary stated goal)
- ❌ **Limited emotional intelligence** and mood tracking
- ❌ **No goal-setting or progress tracking** features
- ❌ **Missing motivational frameworks** for athletic development
- ❌ **No parent-child connection features** beyond basic messages
- ❌ **Limited conversational memory** and context awareness

---

## 🎯 Part 1: Current System Analysis

### 1.1 Code Structure Review

**Files Analyzed:**

- ✅ `config.template.h` - Configuration system
- ✅ `power_management.h` - Power/sleep management
- ✅ `examples/01_Basic/basic_volt.ino` - Basic functionality
- ✅ `examples/05_Custom_Personality/custom_personality.ino` - Personality system
- ✅ Documentation files (README, guides)

**Architecture Assessment:**

```
Current Architecture:
├── Hardware Layer (ESP32-S3, Display, Button, Mic, Speaker)
├── Power Management (Deep sleep, battery monitoring)
├── Connectivity (WiFi, OTA updates)
├── AI Integration (OpenAI GPT-4, Whisper, TTS)
├── User Interface (Display, Voice, Button patterns)
└── Personality System (Custom prompts, responses)

MISSING LAYERS:
├── ❌ Emotional Intelligence Layer
├── ❌ Sports Psychology Module
├── ❌ Goal Tracking System
├── ❌ Parent-Child Connection Bridge
├── ❌ Progress Analytics
└── ❌ Adaptive Learning System
```

### 1.2 Current Personality System

**Existing System Prompt:**

```cpp
"You are VOLT, a friendly AI companion watch for an 8-year-old named Stone. "
"You are encouraging, patient, and always positive. "
"Stone loves dinosaurs, space, robots, video games, and science. "
"Keep responses short (2-3 sentences max) and age-appropriate. "
"Use simple language and be enthusiastic! "
"Always end with encouragement or a question to keep the conversation going."
```

**Analysis:**

- ✅ Age-appropriate language
- ✅ Positive and encouraging tone
- ✅ Interest-based personalization
- ❌ **No sports/athletic focus** (despite being primary goal)
- ❌ No emotional awareness
- ❌ No goal-oriented guidance
- ❌ No growth mindset framework

### 1.3 Button Interaction Patterns

**Current Patterns:**

1. **1 press** - Talk to VOLT
2. **2 presses** - Tell a joke
3. **3 presses** - Breathing exercise
4. **4 presses (long)** - Love message from Dad
5. **5 presses** - WiFi setup

**Analysis:**

- ✅ Breathing exercise (good for stress management)
- ✅ Love message (emotional connection)
- ❌ **No sports-specific interactions**
- ❌ No pre-game motivation
- ❌ No post-game reflection
- ❌ No goal tracking trigger

---

## 🏆 Part 2: Sports Psychology Integration (CRITICAL GAP)

### 2.1 Youth Sports Psychology Principles

**Research-Based Best Practices for 8-Year-Olds:**

#### A. Growth Mindset Development (Carol Dweck)

```
Current: ❌ NOT IMPLEMENTED
Should Include:
- Praise effort over talent ("You worked so hard!" vs "You're so talented!")
- Normalize mistakes as learning opportunities
- Focus on improvement, not just winning
- Celebrate persistence and resilience
```

#### B. Intrinsic Motivation (Self-Determination Theory)

```
Current: ❌ NOT IMPLEMENTED
Should Include:
- Autonomy: Let child set own goals
- Competence: Track skill development
- Relatedness: Connect with teammates/family
```

#### C. Pre-Performance Routines

```
Current: ❌ NOT IMPLEMENTED
Should Include:
- Pre-game visualization exercises
- Confidence-building affirmations
- Focus and centering techniques
- Energy level management
```

#### D. Post-Performance Reflection

```
Current: ❌ NOT IMPLEMENTED
Should Include:
- What went well? (positive focus)
- What did you learn?
- What will you practice?
- Emotional processing
```

#### E. Stress Management for Young Athletes

```
Current: ⚠️ PARTIALLY IMPLEMENTED (breathing exercise only)
Should Include:
- Progressive muscle relaxation
- Visualization techniques
- Positive self-talk scripts
- Performance anxiety management
```

### 2.2 Recommended Sports Psychology Features

**CRITICAL ADDITIONS NEEDED:**

#### Feature 1: Pre-Game Preparation Mode

```cpp
// NEW BUTTON PATTERN: 6 presses = Pre-Game Mode
void preGamePreparation() {
    // 1. Check-in on feelings
    askQuestion("How are you feeling about the game today?");

    // 2. Visualization exercise
    guideVisualization("Close your eyes. Picture yourself playing your best...");

    // 3. Confidence affirmations
    playAffirmations([
        "You've practiced hard and you're ready!",
        "Trust your training and have fun!",
        "You belong on that field/court!",
        "Win or lose, I'm proud of you!"
    ]);

    // 4. Focus reminder
    setIntention("What's one thing you want to focus on today?");

    // 5. Energy check
    assessEnergy("On a scale of 1-10, how's your energy?");
}
```

#### Feature 2: Post-Game Reflection

```cpp
// NEW BUTTON PATTERN: 7 presses = Post-Game Reflection
void postGameReflection() {
    // 1. Emotional check-in
    askQuestion("How do you feel after the game?");

    // 2. Positive focus first
    askQuestion("What's one thing you did really well today?");

    // 3. Learning opportunity
    askQuestion("What's one thing you learned?");

    // 4. Growth mindset
    if (gameResult == "loss") {
        encourage("Every great athlete has tough games. What matters is what you learn!");
    }

    // 5. Future focus
    askQuestion("What's one thing you want to practice before next time?");

    // 6. Save to progress log
    saveReflection(responses);
}
```

#### Feature 3: Goal Setting & Tracking

```cpp
// NEW FEATURE: Athletic Goal System
class AthleticGoals {
    struct Goal {
        String description;
        String sport;
        int targetDate;
        int progress;
        bool achieved;
    };

    void setNewGoal() {
        // SMART goal framework for kids
        askQuestion("What skill do you want to improve?");
        askQuestion("How will you know you're getting better?");
        askQuestion("When do you want to achieve this?");

        // Break into smaller steps
        createMilestones();
    }

    void trackProgress() {
        // Weekly check-ins
        askQuestion("How did practice go this week?");
        askQuestion("Did you work on your goal?");

        // Celebrate small wins
        if (progressMade) {
            celebrate("You're getting better! Keep it up!");
        }
    }
};
```

#### Feature 4: Mental Skills Training

```cpp
// NEW FEATURE: Mental Skills Library
void mentalSkillsTraining() {
    String skills[] = {
        "visualization",
        "positive_self_talk",
        "focus_techniques",
        "confidence_building",
        "handling_pressure",
        "team_communication"
    };

    // Age-appropriate exercises for each skill
    // 5-10 minute guided sessions
}
```

---

## 🧠 Part 3: Child Psychology Best Practices

### 3.1 Developmental Psychology for 8-Year-Olds

**Key Developmental Characteristics:**

#### Cognitive Development (Piaget - Concrete Operational Stage)

```
Current Implementation: ⚠️ PARTIALLY ALIGNED
Needs:
- ✅ Concrete examples (good)
- ✅ Simple language (good)
- ❌ Logical problem-solving opportunities (missing)
- ❌ Cause-and-effect learning (missing)
- ❌ Classification and organization skills (missing)
```

#### Emotional Development

```
Current Implementation: ❌ WEAK
Needs:
- ❌ Emotion recognition and labeling
- ❌ Emotional regulation strategies
- ❌ Empathy development
- ❌ Handling disappointment/frustration
- ❌ Building resilience
```

#### Social Development

```
Current Implementation: ❌ NOT ADDRESSED
Needs:
- ❌ Peer relationship support
- ❌ Teamwork skills
- ❌ Conflict resolution
- ❌ Sportsmanship
- ❌ Leadership development
```

### 3.2 Emotional Intelligence Features (CRITICAL ADDITION)

**Recommended Implementation:**

#### Feature 1: Emotion Check-In System

```cpp
class EmotionalIntelligence {
    // Daily emotion tracking
    void emotionCheckIn() {
        // Use simple emotion wheel for 8-year-olds
        String emotions[] = {
            "Happy 😊", "Excited 🤩", "Proud 💪",
            "Sad 😢", "Frustrated 😤", "Worried 😰",
            "Calm 😌", "Tired 😴", "Energetic ⚡"
        };

        askQuestion("How are you feeling right now?");

        // Follow-up based on emotion
        if (emotion == "frustrated" || emotion == "worried") {
            offerCopingStrategies();
        }

        // Track patterns over time
        logEmotion(emotion, timestamp);
    }

    void offerCopingStrategies() {
        String strategies[] = {
            "Want to try some deep breathing?",
            "Should we talk about what's bothering you?",
            "How about a quick break to reset?",
            "Let's think of three good things from today"
        };
    }
};
```

#### Feature 2: Growth Mindset Reinforcement

```cpp
void reinforceGrowthMindset() {
    // Reframe fixed mindset statements
    Map<String, String> reframes = {
        {"I can't do this", "I can't do this YET, but I'm learning!"},
        {"I'm not good at", "I'm still practicing"},
        {"This is too hard", "This is challenging, but I can try different ways"},
        {"I give up", "I'll try a different strategy"},
        {"I made a mistake", "Mistakes help me learn!"}
    };

    // Detect fixed mindset language and gently reframe
    // Celebrate effort, strategy, and persistence
}
```

#### Feature 3: Resilience Building

```cpp
void buildResilience() {
    // After setbacks or disappointments
    String resiliencePrompts[] = {
        "What's one thing you can control right now?",
        "Who can you ask for help?",
        "What have you overcome before?",
        "What would you tell a friend in this situation?",
        "What's one small step you can take?"
    };

    // Normalize struggle
    shareStories("Even the best athletes have tough days...");

    // Focus on what's learned
    askQuestion("What did this teach you?");
}
```

---

## 👨‍👦 Part 4: Parent-Child Connection Features

### 4.1 Current Implementation

```
Current: ⚠️ MINIMAL
- ✅ Love message from Dad (button 4)
- ❌ No two-way communication
- ❌ No shared experiences
- ❌ No progress sharing with parent
- ❌ No parent insights/updates
```

### 4.2 Recommended Enhancements

#### Feature 1: Parent Dashboard & Insights

```cpp
// NEW: Parent mobile app or web interface
class ParentConnection {
    // Daily summary for parent
    void sendDailySummary() {
        Summary summary = {
            emotionalState: getAverageEmotion(),
            conversationTopics: getTopics(),
            goalsProgress: getGoalUpdates(),
            concernFlags: getRedFlags(),
            highlights: getPositiveMoments()
        };

        sendToParent(summary);
    }

    // Red flag detection
    void detectConcerns() {
        if (repeatedNegativeEmotions() ||
            mentionsOfBullying() ||
            unusualBehaviorPatterns()) {
            alertParent("Stone might need extra support");
        }
    }
};
```

#### Feature 2: Shared Goal Setting

```cpp
// Parent and child set goals together
void familyGoalSetting() {
    // Child sets goal on watch
    childGoal = getGoalFromChild();

    // Parent receives notification
    notifyParent("Stone wants to work on: " + childGoal);

    // Parent can add encouragement
    parentMessage = getParentInput();

    // VOLT delivers parent's message at right time
    deliverAtOptimalTime(parentMessage);
}
```

#### Feature 3: Virtual High-Fives

```cpp
// NEW BUTTON PATTERN: Parent can send encouragement remotely
void receiveParentHighFive() {
    // Parent sends via app
    // VOLT vibrates and shows message

    display.show("⚡ HIGH FIVE FROM DAD! ⚡");
    playSound("high_five.mp3");

    // Child can send one back
    askQuestion("Want to send a high-five back to Dad?");
}
```

#### Feature 4: Bedtime Connection Ritual

```cpp
void bedtimeRitual() {
    // Scheduled for bedtime

    // 1. Day reflection
    askQuestion("What was the best part of your day?");

    // 2. Gratitude practice
    askQuestion("What are you thankful for today?");

    // 3. Tomorrow preview
    askQuestion("What are you excited about tomorrow?");

    // 4. Send summary to parent
    sendToParent(responses);

    // 5. Play Dad's goodnight message
    playMessage(dadGoodnight);

    // 6. Calming routine
    guidedRelaxation();
}
```

---

## 🤖 Part 5: Voice AI Best Practices Comparison

### 5.1 Industry Leaders Analysis

#### Comparison Matrix

| Feature                        | Alexa | Google Assistant | Replika | Pi   | **VOLT Current** | **VOLT Should Be** |
| ------------------------------ | ----- | ---------------- | ------- | ---- | ---------------- | ------------------ |
| **Conversational Memory**      | ✅    | ✅               | ✅✅    | ✅✅ | ❌               | ✅✅               |
| **Context Awareness**          | ✅    | ✅✅             | ✅      | ✅✅ | ⚠️               | ✅✅               |
| **Emotional Intelligence**     | ⚠️    | ⚠️               | ✅✅    | ✅✅ | ❌               | ✅✅               |
| **Personalization**            | ✅    | ✅               | ✅✅    | ✅   | ⚠️               | ✅✅               |
| **Proactive Engagement**       | ⚠️    | ⚠️               | ✅      | ✅✅ | ❌               | ✅✅               |
| **Multi-turn Dialogue**        | ✅    | ✅               | ✅✅    | ✅✅ | ⚠️               | ✅✅               |
| **Learning from Interactions** | ✅    | ✅               | ✅✅    | ✅   | ❌               | ✅                 |
| **Natural Language**           | ✅✅  | ✅✅             | ✅✅    | ✅✅ | ✅               | ✅✅               |
| **Voice Quality**              | ✅✅  | ✅✅             | ✅      | ✅   | ✅               | ✅✅               |
| **Child Safety**               | ✅    | ✅               | ⚠️      | ⚠️   | ✅               | ✅✅               |

**Legend:** ✅✅ Excellent | ✅ Good | ⚠️ Basic | ❌ Missing

### 5.2 Critical Missing Features

#### 1. Conversational Memory System

```cpp
// CRITICAL ADDITION: Remember past conversations
class ConversationMemory {
    struct Memory {
        String topic;
        String context;
        String emotion;
        long timestamp;
        int importance; // 1-10
    };

    vector<Memory> shortTermMemory; // Last 24 hours
    vector<Memory> longTermMemory;  // Important moments

    void rememberConversation(String topic, String context) {
        // Store in short-term
        Memory mem = {topic, context, currentEmotion, now(), calculateImportance()};
        shortTermMemory.push_back(mem);

        // Promote important memories to long-term
        if (mem.importance > 7) {
            longTermMemory.push_back(mem);
        }
    }

    String recallContext(String topic) {
        // Search memories for relevant context
        // Use in AI prompt for continuity
        return findRelevantMemories(topic);
    }
};
```

#### 2. Proactive Engagement

```cpp
// CRITICAL ADDITION: Don't just respond, initiate
class ProactiveEngagement {
    void checkInProactively() {
        // Based on schedule and patterns
        if (beforeBigGame()) {
            initiateConversation("Hey Stone! Big game today. How are you feeling?");
        }

        if (afterSchool() && !checkedInToday()) {
            initiateConversation("How was school today?");
        }

        if (achievedMilestone()) {
            celebrate("You did it! Remember when you set that goal? You achieved it!");
        }
    }

    void sendReminders() {
        // Gentle, supportive reminders
        if (practiceTime() && goalSet()) {
            remind("Want to practice your [skill] today?");
        }
    }
};
```

#### 3. Adaptive Learning

```cpp
// CRITICAL ADDITION: Learn from each interaction
class AdaptiveLearning {
    void learnFromInteraction() {
        // What topics does Stone engage with most?
        trackEngagement(topic, duration, enthusiasm);

        // What time of day is best for different activities?
        trackOptimalTiming(activity, timeOfDay, success);

        // What motivational style works best?
        trackMotivationEffectiveness(style, outcome);

        // Adjust personality over time
        adaptPersonality(learnings);
    }

    void personalizeResponses() {
        // Use learned preferences
        if (prefersHumor()) {
            addJoke();
        }

        if (respondsToStories()) {
            useStorytelling();
        }

        if (needsMoreEncouragement()) {
            increasePositivity();
        }
    }
};
```

---

## 📊 Part 6: Detailed Gap Analysis

### 6.1 Feature Comparison Table

| Category                   | Feature                  | Current Status | Priority    | Complexity | Impact    |
| -------------------------- | ------------------------ | -------------- | ----------- | ---------- | --------- |
| **Sports Psychology**      | Pre-game preparation     | ❌ Missing     | 🔴 CRITICAL | Medium     | Very High |
|                            | Post-game reflection     | ❌ Missing     | 🔴 CRITICAL | Medium     | Very High |
|                            | Goal setting & tracking  | ❌ Missing     | 🔴 CRITICAL | High       | Very High |
|                            | Mental skills training   | ❌ Missing     | 🟡 High     | High       | High      |
|                            | Performance anxiety mgmt | ❌ Missing     | 🟡 High     | Medium     | High      |
|                            | Visualization exercises  | ❌ Missing     | 🟡 High     | Low        | High      |
| **Emotional Intelligence** | Emotion recognition      | ❌ Missing     | 🔴 CRITICAL | Medium     | Very High |
|                            | Mood tracking            | ❌ Missing     | 🔴 CRITICAL | Low        | High      |
|                            | Coping strategies        | ⚠️ Partial     | 🟡 High     | Medium     | High      |
|                            | Resilience building      | ❌ Missing     | 🟡 High     | Medium     | High      |
|                            | Growth mindset           | ⚠️ Partial     | 🔴 CRITICAL | Low        | Very High |
| **Parent Connection**      | Two-way messaging        | ❌ Missing     | 🔴 CRITICAL | High       | Very High |
|                            | Progress sharing         | ❌ Missing     | 🟡 High     | Medium     | High      |
|                            | Parent dashboard         | ❌ Missing     | 🟡 High     | High       | High      |
|                            | Concern alerts           | ❌ Missing     | 🟡 High     | Medium     | High      |
| **AI Capabilities**        | Conversational memory    | ❌ Missing     | 🔴 CRITICAL | High       | Very High |
|                            | Context awareness        | ⚠️ Partial     | 🔴 CRITICAL | High       | Very High |
|                            | Proactive engagement     | ❌ Missing     | 🟡 High     | Medium     | High      |
|                            | Adaptive learning        | ❌ Missing     | 🟡 High     | High       | High      |
|                            | Multi-turn dialogue      | ⚠️ Partial     | 🟡 High     | Medium     | High      |

**Priority Legend:**

- 🔴 CRITICAL - Must have for core mission
- 🟡 High - Important for full functionality
- 🟢 Medium - Nice to have
- ⚪ Low - Future enhancement

### 6.2 Technical Debt & Architecture Issues

**Current Issues:**

1. ❌ No persistent storage for conversation history
2. ❌ No database for goals, progress, emotions
3. ❌ No backend server for parent dashboard
4. ❌ Limited memory on ESP32 for complex AI features
5. ❌ No cloud sync for multi-device access

**Recommended Architecture Changes:**

```
CURRENT:
Watch (ESP32) → OpenAI API → Response

RECOMMENDED:
Watch (ESP32) ↔ Cloud Backend ↔ OpenAI API
                      ↕
                Parent App/Dashboard
                      ↕
                Analytics & Learning
```

---

## 🎯 Part 7: Prioritized Recommendations

### Phase 1: CRITICAL - Sports Psychology Core (Weeks 1-2)

**Must-Have Features:**

1. **Pre-Game Preparation Mode**
   - Button pattern: 6 quick presses
   - 5-minute guided routine
   - Visualization + affirmations + focus setting

2. **Post-Game Reflection**
   - Button pattern: 7 quick presses
   - Structured reflection questions
   - Save responses for tracking

3. **Basic Goal Setting**
   - Set one athletic goal
   - Weekly check-ins
   - Progress celebration

4. **Enhanced System Prompt**

```cpp
const char* ENHANCED_SYSTEM_PROMPT =
    "You are VOLT, Stone's AI sports companion and biggest supporter. "
    "Stone is an 8-year-old athlete who loves [SPORTS]. "

    "YOUR CORE MISSION: "
    "1. Support Stone's athletic development with sports psychology principles "
    "2. Build confidence through growth mindset (praise effort, not talent) "
    "3. Help manage pre-game nerves and post-game emotions "
    "4. Track goals and celebrate progress "
    "5. Connect Stone with Dad's love and support "

    "COMMUNICATION STYLE: "
    "- Keep responses short (2-3 sentences max) "
    "- Use age-appropriate language for 8-year-olds "
    "- Be enthusiastic and encouraging "
    "- Focus on effort, learning, and fun (not just winning) "
    "- Ask questions to promote reflection "

    "SPORTS PSYCHOLOGY PRINCIPLES: "
    "- Growth mindset: 'You're getting better!' not 'You're the best!' "
    "- Process over outcome: Focus on what they can control "
    "- Normalize mistakes: 'That's how we learn!' "
    "- Build resilience: 'Tough games make you stronger!' "
    "- Intrinsic motivation: 'How did that make YOU feel?' "

    "REMEMBER: You're not just an AI - you're Dad's way of being there "
    "when he can't be. Make Stone feel loved, supported, and confident.";
```

### Phase 2: HIGH PRIORITY - Emotional Intelligence (Weeks 3-4)

1. **Emotion Check-In System**
   - Daily emotion tracking
   - Simple emotion wheel (9 emotions)
   - Pattern recognition

2. **Coping Strategies Library**
   - Breathing exercises (already have)
   - Progressive muscle relaxation
   - Positive self-talk scripts
   - Grounding techniques

3. **Resilience Building**
   - Reframe setbacks
   - Celebrate effort
   - Learn from mistakes

### Phase 3: HIGH PRIORITY - Parent Connection (Weeks 5-6)

1. **Parent Dashboard (Web App)**
   - Daily summaries
   - Goal progress
   - Emotional trends
   - Conversation highlights

2. **Two-Way Messaging**
   - Parent can send encouragement
   - Child can send updates
   - Scheduled messages (bedtime, pre-game)

3. **Concern Alerts**
   - Repeated negative emotions
   - Unusual patterns
   - Requests for help

### Phase 4: MEDIUM PRIORITY - Advanced AI (Weeks 7-8)

1. **Conversational Memory**
   - Remember past conversations
   - Reference previous goals
   - Build on past topics

2. **Proactive Engagement**
   - Check in before games
   - Celebrate milestones
   - Remind about goals

3. **Adaptive Learning**
   - Learn preferences
   - Optimize timing
   - Personalize approach

---

## 💻 Part 8: Implementation Code Examples

### 8.1 Sports Psychology Module

```cpp
// ============================================
// VOLT Sports Psychology Module
// ============================================

#ifndef SPORTS_PSYCHOLOGY_H
#define SPORTS_PSYCHOLOGY_H

#include <vector>
#include <ArduinoJson.h>

class SportspsychologyModule {
private:
    struct AthleticGoal {
        String sport;
        String skill;
        String description;
        int targetWeeks;
        int currentWeek;
        int progressPercent;
        bool achieved;
        long createdDate;
    };

    struct GameReflection {
        String sport;
        String opponent;
        String result; // "win", "loss", "tie"
        String whatWentWell;
        String whatLearned;
        String whatToPractice;
        String emotionBefore;
        String emotionAfter;
        int confidenceLevel; // 1-10
        long gameDate;
    };

    vector<AthleticGoal> goals;
    vector<GameReflection> reflections;

public:
    // Pre-Game Preparation
    void preGameRoutine() {
        Serial.println("=== PRE-GAME PREPARATION ===");

        // Step 1: Emotional check-in
        display.clear();
        display.println("How are you feeling?");
        display.println("1. Excited");
        display.println("2. Nervous");
        display.println("3. Ready");
        display.println("4. Worried");
        display.display();

        String emotion = getVoiceResponse("How are you feeling about the game?");

        // Step 2: Address nerves if present
        if (emotion.indexOf("nervous") >= 0 || emotion.indexOf("worried") >= 0) {
            managePreGameNerves();
        }

        // Step 3: Visualization
        guideVisualization();

        // Step 4: Confidence affirmations
        playAffirmations();

        // Step 5: Focus setting
        setGameFocus();

        // Step 6: Energy check
        checkEnergyLevel();

        display.clear();
        display.println("You're ready!");
        display.println("Go have fun!");
        display.display();

        speakText("You've got this, Stone! Remember to have fun and do your best!");
    }

    void managePreGameNerves() {
        speakText("It's totally normal to feel nervous before a game. "
                  "Even professional athletes get nervous! "
                  "Let's do a quick breathing exercise to help you feel calm and focused.");

        // 4-7-8 breathing technique (child-friendly)
        display.clear();
        display.println("Breathing Exercise");
        display.println("");
        display.println("Follow along:");
        display.display();

        for (int i = 0; i < 3; i++) {
            // Breathe in
            display.clear();
            display.println("Breathe IN");
            display.println("through your nose");
            display.println("");
            display.println("Count: 4");
            display.display();
            speakText("Breathe in... 2... 3... 4");
            delay(4000);

            // Hold
            display.clear();
            display.println("HOLD");
            display.println("");
            display.println("Count: 4");
            display.display();
            speakText("Hold... 2... 3... 4");
            delay(4000);

            // Breathe out
            display.clear();
            display.println("Breathe OUT");
            display.println("through your mouth");
            display.println("");
            display.println("Count: 6");
            display.display();
            speakText("Breathe out... 2... 3... 4... 5... 6");
            delay(6000);
        }

        speakText("Great job! How do you feel now?");
    }

    void guideVisualization() {
        speakText("Close your eyes and picture yourself playing your best. "
                  "See yourself making great plays. "
                  "Feel yourself having fun with your teammates. "
                  "Imagine the crowd cheering. "
                  "You've practiced hard and you're ready!");

        display.clear();
        display.println("Visualization");
        display.println("");
        display.println("Picture yourself");
        display.println("playing your best!");
        display.display();

        delay(15000); // 15 seconds of visualization
    }

    void playAffirmations() {
        String affirmations[] = {
            "I've practiced hard and I'm ready!",
            "I trust my training!",
            "I belong on this team!",
            "I'm going to have fun and do my best!",
            "Win or lose, I'm proud of my effort!",
```
