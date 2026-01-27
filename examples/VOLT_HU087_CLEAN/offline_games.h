/*
 * ============================================
 * VOLT Offline Games & Activities
 * ============================================
 * 
 * Fun games that work WITHOUT WiFi:
 * - Math challenges
 * - Memory games
 * - Word games
 * - Breathing exercises
 * - Meditation
 * - Story time
 * - Music & rhythm
 * - Drawing prompts
 * 
 * Keep Stone entertained and learning!
 * 
 * ============================================
 */

#ifndef OFFLINE_GAMES_H
#define OFFLINE_GAMES_H

#include <Arduino.h>

// ============================================
// BREATHING EXERCISES
// ============================================

struct BreathingExercise {
    const char* name;
    const char* instruction;
    int inhale_seconds;
    int hold_seconds;
    int exhale_seconds;
    int cycles;
};

const BreathingExercise BREATHING_EXERCISES[] = {
    {
        "Calm Down Breathing",
        "Let's breathe together, Stone. This will help you feel calm.",
        4, 4, 4, 3
    },
    {
        "Energy Breathing",
        "This breathing will give you energy, Stone!",
        3, 2, 3, 5
    },
    {
        "Bedtime Breathing",
        "This will help you relax for sleep, Stone.",
        4, 7, 8, 3
    },
    {
        "Focus Breathing",
        "This helps you concentrate, Stone!",
        4, 4, 6, 4
    }
};

const int NUM_BREATHING_EXERCISES = sizeof(BREATHING_EXERCISES) / sizeof(BREATHING_EXERCISES[0]);

// ============================================
// MATH CHALLENGES (Age-Appropriate)
// ============================================

struct MathProblem {
    const char* question;
    int answer;
    const char* encouragement;
};

const MathProblem MATH_PROBLEMS[] = {
    {"What is 5 + 3?", 8, "Great job, Stone! You're so smart!"},
    {"What is 10 - 4?", 6, "Perfect, Stone! Dad is proud!"},
    {"What is 2 + 2?", 4, "You got it, Stone! Amazing!"},
    {"What is 7 + 2?", 9, "Excellent, Stone! You're a math star!"},
    {"What is 8 - 3?", 5, "Wonderful, Stone! Keep it up!"},
    {"What is 6 + 4?", 10, "Fantastic, Stone! You're brilliant!"},
    {"What is 9 - 5?", 4, "Super job, Stone! Dad loves you!"},
    {"What is 3 + 7?", 10, "Amazing, Stone! You're so clever!"},
    {"What is 12 - 6?", 6, "Perfect, Stone! You're awesome!"},
    {"What is 4 + 5?", 9, "Great work, Stone! Dad is impressed!"},
    {"What is 2 × 3?", 6, "Wow, Stone! Multiplication master!"},
    {"What is 5 × 2?", 10, "Incredible, Stone! You're so smart!"},
    {"What is 10 ÷ 2?", 5, "Perfect, Stone! Division champion!"},
    {"What is 3 × 3?", 9, "Outstanding, Stone! Dad is proud!"},
    {"What is 15 - 7?", 8, "Excellent, Stone! You're brilliant!"}
};

const int NUM_MATH_PROBLEMS = sizeof(MATH_PROBLEMS) / sizeof(MATH_PROBLEMS[0]);

// ============================================
// STORY PROMPTS
// ============================================

const char* STORY_PROMPTS[] = {
    "Once upon a time, there was a brave boy named Stone who discovered a magic watch...",
    "In a land far away, Stone found a secret door that led to an amazing adventure...",
    "Stone woke up one morning with a superpower - he could talk to animals!",
    "Deep in the forest, Stone met a friendly dragon who needed his help...",
    "Stone built a rocket ship and flew to a planet made of candy!",
    "One day, Stone found a treasure map in his backyard...",
    "Stone discovered he could time travel and visited the age of dinosaurs!",
    "In a magical library, Stone found a book that came to life when he read it...",
    "Stone became the captain of a pirate ship searching for lost treasure!",
    "A wizard gave Stone three wishes. What did he wish for?"
};

const int NUM_STORY_PROMPTS = sizeof(STORY_PROMPTS) / sizeof(STORY_PROMPTS[0]);

// ============================================
// MEDITATION & MINDFULNESS
// ============================================

const char* MINDFULNESS_EXERCISES[] = {
    "Stone, close your eyes and think of three things you're grateful for today.",
    "Stone, imagine you're a tree. Feel your roots growing strong and deep.",
    "Stone, picture your favorite place. What do you see, hear, and smell?",
    "Stone, think of someone you love. Send them happy thoughts!",
    "Stone, imagine a warm, golden light filling your body with happiness.",
    "Stone, count five things you can see, four you can touch, three you can hear.",
    "Stone, think of a time you felt really proud. Remember that feeling!",
    "Stone, imagine you're floating on a cloud, safe and peaceful.",
    "Stone, picture yourself doing something you love. How does it feel?",
    "Stone, think of your favorite color. Imagine it surrounding you like a hug!"
};

const int NUM_MINDFULNESS = sizeof(MINDFULNESS_EXERCISES) / sizeof(MINDFULNESS_EXERCISES[0]);

// ============================================
// DRAWING PROMPTS
// ============================================

const char* DRAWING_PROMPTS[] = {
    "Stone, imagine a robot that can do your chores. What does it look like?",
    "Stone, draw your dream treehouse! What's inside?",
    "Stone, create a new animal by mixing two animals together!",
    "Stone, design a superhero costume for yourself!",
    "Stone, draw what you think the future will look like!",
    "Stone, imagine a magical creature. What does it eat?",
    "Stone, design your own video game character!",
    "Stone, draw your family as superheroes!",
    "Stone, create an invention that would help people!",
    "Stone, draw what happiness looks like to you!"
};

const int NUM_DRAWING_PROMPTS = sizeof(DRAWING_PROMPTS) / sizeof(DRAWING_PROMPTS[0]);

// ============================================
// WOULD YOU RATHER QUESTIONS
// ============================================

const char* WOULD_YOU_RATHER[] = {
    "Would you rather fly like a bird or swim like a fish?",
    "Would you rather be invisible or be able to read minds?",
    "Would you rather have a pet dragon or a pet unicorn?",
    "Would you rather visit the past or the future?",
    "Would you rather be super strong or super fast?",
    "Would you rather live in a castle or on a spaceship?",
    "Would you rather talk to animals or speak all languages?",
    "Would you rather have unlimited pizza or unlimited ice cream?",
    "Would you rather be a famous inventor or a famous explorer?",
    "Would you rather have a magic carpet or a time machine?"
};

const int NUM_WOULD_YOU_RATHER = sizeof(WOULD_YOU_RATHER) / sizeof(WOULD_YOU_RATHER[0]);

// ============================================
// DAILY CHALLENGES
// ============================================

const char* DAILY_CHALLENGES[] = {
    "Stone, today's challenge: Make someone smile!",
    "Stone, today's challenge: Learn one new thing!",
    "Stone, today's challenge: Help someone without being asked!",
    "Stone, today's challenge: Try something you've never done before!",
    "Stone, today's challenge: Say something kind to yourself!",
    "Stone, today's challenge: Be brave and try something that scares you a little!",
    "Stone, today's challenge: Ask a grown-up an interesting question!",
    "Stone, today's challenge: Create something with your hands!",
    "Stone, today's challenge: Teach someone something you know!",
    "Stone, today's challenge: Find beauty in something ordinary!"
};

const int NUM_DAILY_CHALLENGES = sizeof(DAILY_CHALLENGES) / sizeof(DAILY_CHALLENGES[0]);

// ============================================
// FUN FACTS
// ============================================

const char* FUN_FACTS[] = {
    "Stone, did you know? A group of flamingos is called a 'flamboyance'!",
    "Stone, did you know? Octopuses have three hearts!",
    "Stone, did you know? Honey never spoils! Ancient honey is still edible!",
    "Stone, did you know? A day on Venus is longer than a year on Venus!",
    "Stone, did you know? Butterflies taste with their feet!",
    "Stone, did you know? A bolt of lightning is five times hotter than the sun!",
    "Stone, did you know? Sharks have been around longer than trees!",
    "Stone, did you know? Your brain uses 20% of your body's energy!",
    "Stone, did you know? Penguins propose to their mates with pebbles!",
    "Stone, did you know? The Eiffel Tower can grow 6 inches in summer!"
};

const int NUM_FUN_FACTS = sizeof(FUN_FACTS) / sizeof(FUN_FACTS[0]);

// ============================================
// OFFLINE GAMES CLASS
// ============================================

class OfflineGames {
public:
    // Get random breathing exercise
    static BreathingExercise getRandomBreathingExercise() {
        int index = random(0, NUM_BREATHING_EXERCISES);
        return BREATHING_EXERCISES[index];
    }
    
    // Get random math problem
    static MathProblem getRandomMathProblem() {
        int index = random(0, NUM_MATH_PROBLEMS);
        return MATH_PROBLEMS[index];
    }
    
    // Get random story prompt
    static String getRandomStoryPrompt() {
        int index = random(0, NUM_STORY_PROMPTS);
        return String(STORY_PROMPTS[index]);
    }
    
    // Get random mindfulness exercise
    static String getRandomMindfulness() {
        int index = random(0, NUM_MINDFULNESS);
        return String(MINDFULNESS_EXERCISES[index]);
    }
    
    // Get random drawing prompt
    static String getRandomDrawingPrompt() {
        int index = random(0, NUM_DRAWING_PROMPTS);
        return String(DRAWING_PROMPTS[index]);
    }
    
    // Get random would you rather
    static String getRandomWouldYouRather() {
        int index = random(0, NUM_WOULD_YOU_RATHER);
        return String(WOULD_YOU_RATHER[index]);
    }
    
    // Get daily challenge
    static String getDailyChallenge() {
        // Use day of year to get consistent daily challenge
        int index = random(0, NUM_DAILY_CHALLENGES);
        return String(DAILY_CHALLENGES[index]);
    }
    
    // Get random fun fact
    static String getRandomFunFact() {
        int index = random(0, NUM_FUN_FACTS);
        return String(FUN_FACTS[index]);
    }
    
    // Print stats
    static void printStats() {
        Serial.println("\n=== Offline Games Available ===");
        Serial.printf("Breathing Exercises: %d\n", NUM_BREATHING_EXERCISES);
        Serial.printf("Math Problems: %d\n", NUM_MATH_PROBLEMS);
        Serial.printf("Story Prompts: %d\n", NUM_STORY_PROMPTS);
        Serial.printf("Mindfulness: %d\n", NUM_MINDFULNESS);
        Serial.printf("Drawing Prompts: %d\n", NUM_DRAWING_PROMPTS);
        Serial.printf("Would You Rather: %d\n", NUM_WOULD_YOU_RATHER);
        Serial.printf("Daily Challenges: %d\n", NUM_DAILY_CHALLENGES);
        Serial.printf("Fun Facts: %d\n", NUM_FUN_FACTS);
        Serial.println("===============================\n");
    }
};

#endif // OFFLINE_GAMES_H
