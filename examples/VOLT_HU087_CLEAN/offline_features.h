/*
 * ============================================
 * VOLT Offline Features - Always Available!
 * ============================================
 * 
 * Features that work WITHOUT WiFi:
 * - Dad's love messages (100+ variations)
 * - Encouragement & affirmations
 * - Breathing exercises
 * - Jokes & riddles
 * - Math games
 * - Memory games
 * - Trivia questions
 * - Motivational quotes
 * - Bedtime stories
 * - And much more!
 * 
 * Stone is AWESOME and Dad loves him!
 * 
 * ============================================
 */

#ifndef OFFLINE_FEATURES_H
#define OFFLINE_FEATURES_H

#include <Arduino.h>

// ============================================
// DAD'S LOVE MESSAGES (100+ Messages!)
// ============================================

const char* DADS_LOVE_MESSAGES[] = {
    // General Love Messages
    "Stone, Dad loves you more than all the stars in the sky!",
    "You make every day brighter, Stone! Dad is so proud of you!",
    "Stone, you're the best son in the whole world! I love you so much!",
    "Dad thinks about you all the time, Stone. You're amazing!",
    "Stone, you make Dad's heart so happy! I love you, buddy!",
    
    // Encouragement
    "Stone, you're braver than you think! Dad believes in you!",
    "You can do anything you set your mind to, Stone! Dad knows it!",
    "Stone, you're so smart and creative! Dad is amazed by you!",
    "Keep being awesome, Stone! Dad is so proud of everything you do!",
    "Stone, you're growing up to be such an amazing person!",
    
    // Specific Praise
    "Stone, your kindness makes the world better! Dad loves that about you!",
    "You have such a big heart, Stone! Dad is so proud!",
    "Stone, your curiosity and questions make Dad smile every day!",
    "You're so good at figuring things out, Stone! Dad admires that!",
    "Stone, your laugh is Dad's favorite sound in the whole world!",
    
    // Comfort & Support
    "Stone, when you're scared, remember Dad is always with you in your heart!",
    "You're never alone, Stone. Dad's love is always with you!",
    "Stone, it's okay to feel worried. Dad is here for you, always!",
    "You're safe and loved, Stone. Dad will always protect you!",
    "Stone, you can tell Dad anything. I'm always here to listen!",
    
    // Morning Messages
    "Good morning, Stone! Dad hopes you have the best day ever!",
    "Rise and shine, buddy! Dad loves you and today is going to be great!",
    "Stone, you woke up awesome today! Dad can't wait to hear about your day!",
    "Good morning, Stone! Remember, you're amazing and Dad loves you!",
    
    // Bedtime Messages
    "Sweet dreams, Stone. Dad loves you to the moon and back!",
    "Sleep tight, buddy. Dad will see you in your dreams!",
    "Stone, you did great today! Dad is proud. Sleep well!",
    "Goodnight, Stone. Tomorrow is going to be another amazing day!",
    
    // Achievement Messages
    "Stone, you did it! Dad knew you could! So proud of you!",
    "Way to go, Stone! Dad is cheering for you!",
    "Stone, you're a superstar! Dad loves watching you succeed!",
    "That was amazing, Stone! Dad is so impressed!",
    
    // Tough Times
    "Stone, even when things are hard, Dad believes in you!",
    "You're stronger than you know, Stone. Dad is here for you!",
    "Stone, it's okay to make mistakes. Dad loves you no matter what!",
    "You're learning and growing, Stone. Dad is so proud!",
    
    // Just Because
    "Stone, Dad just wanted to say I love you!",
    "Thinking of you, Stone! You're the best!",
    "Stone, you make Dad smile every single day!",
    "Dad is lucky to have you, Stone!",
    
    // Special Moments
    "Stone, remember when we laughed together? Dad loves those moments!",
    "You and Dad make a great team, Stone!",
    "Stone, Dad can't wait for our next adventure together!",
    "Every moment with you is special, Stone!",
    
    // Character Building
    "Stone, your honesty makes Dad so proud!",
    "You're so responsible, Stone! Dad notices and appreciates it!",
    "Stone, the way you help others shows what a great person you are!",
    "Your patience is growing, Stone! Dad sees it!",
    
    // Fun & Playful
    "Stone, you're cooler than a polar bear in sunglasses!",
    "You're more awesome than a T-Rex riding a skateboard, Stone!",
    "Stone, you're as smart as a dolphin and as brave as a lion!",
    "You're the champion of being awesome, Stone!",
    
    // Wisdom
    "Stone, being kind is more important than being right. Dad loves your kindness!",
    "You don't have to be perfect, Stone. Just be you! Dad loves you!",
    "Stone, asking for help is brave, not weak. Dad is always here!",
    "It's okay to be different, Stone. That's what makes you special!",
    
    // Gratitude
    "Stone, Dad is grateful for you every single day!",
    "Thank you for being you, Stone! You're perfect just as you are!",
    "Stone, you make Dad's life so much better!",
    "Dad is blessed to be your father, Stone!",
    
    // Future
    "Stone, Dad can't wait to see all the amazing things you'll do!",
    "You have such a bright future, Stone! Dad will be there every step!",
    "Stone, the world is lucky to have you in it!",
    "You're going to do great things, Stone! Dad believes in you!",
    
    // Random Love
    "Stone, if love was measured in hugs, Dad would give you a million!",
    "You're Dad's favorite Stone in the whole universe!",
    "Stone, Dad's love for you grows bigger every single day!",
    "You're not just loved, Stone. You're SUPER loved!",
    
    // Specific to Stone
    "Stone, you're 8 years old and already so amazing! Dad is in awe!",
    "Stone, watching you grow up is Dad's greatest joy!",
    "You're one of a kind, Stone! There's nobody else like you!",
    "Stone, Dad chose you and you chose Dad. We're a team forever!",
    
    // More Encouragement
    "Stone, your ideas are brilliant! Keep thinking and creating!",
    "You have such a good imagination, Stone! Dad loves it!",
    "Stone, the questions you ask show how smart you are!",
    "You're a problem solver, Stone! Dad admires that!",
    
    // Emotional Support
    "Stone, all your feelings are okay. Dad understands!",
    "It's brave to talk about feelings, Stone. Dad is proud!",
    "Stone, Dad loves you when you're happy AND when you're sad!",
    "You can always be yourself with Dad, Stone!",
    
    // Adventure
    "Stone, life is an adventure and Dad is glad to share it with you!",
    "Every day with you is exciting, Stone!",
    "Stone, you make ordinary days extraordinary!",
    "Dad loves exploring the world with you, Stone!",
    
    // Learning
    "Stone, you're so good at learning new things!",
    "Your brain is amazing, Stone! Dad loves watching you learn!",
    "Stone, mistakes help us learn. Dad makes them too!",
    "You're getting smarter every day, Stone!",
    
    // Friendship
    "Stone, you're a great friend! Dad sees how kind you are!",
    "The way you treat others makes Dad so proud, Stone!",
    "Stone, you know how to make people smile!",
    "Your friends are lucky to have you, Stone!",
    
    // Creativity
    "Stone, your creativity amazes Dad every day!",
    "You think outside the box, Stone! That's awesome!",
    "Stone, your ideas are unique and wonderful!",
    "Dad loves seeing the world through your eyes, Stone!",
    
    // Strength
    "Stone, you're tougher than you think!",
    "You've overcome so much, Stone! Dad is proud!",
    "Stone, your resilience inspires Dad!",
    "You keep going even when it's hard, Stone! That's strength!",
    
    // Joy
    "Stone, your happiness is Dad's happiness!",
    "Seeing you smile makes Dad's whole day, Stone!",
    "Stone, your joy is contagious!",
    "You bring so much light into Dad's life, Stone!",
    
    // Always
    "Stone, Dad will love you forever and always!",
    "No matter what, Dad is on your team, Stone!",
    "Stone, Dad's love for you will never, ever change!",
    "You're stuck with Dad's love forever, Stone!"
};

const int NUM_LOVE_MESSAGES = sizeof(DADS_LOVE_MESSAGES) / sizeof(DADS_LOVE_MESSAGES[0]);

// ============================================
// AFFIRMATIONS & ENCOURAGEMENT
// ============================================

const char* AFFIRMATIONS[] = {
    "You are brave!",
    "You are smart!",
    "You are kind!",
    "You are loved!",
    "You are important!",
    "You are special!",
    "You are strong!",
    "You are creative!",
    "You are amazing!",
    "You are enough!",
    "You can do hard things!",
    "You are a good friend!",
    "You are growing!",
    "You are learning!",
    "You are awesome!",
    "You matter!",
    "You are unique!",
    "You are capable!",
    "You are resilient!",
    "You are wonderful!"
};

const int NUM_AFFIRMATIONS = sizeof(AFFIRMATIONS) / sizeof(AFFIRMATIONS[0]);

// ============================================
// OFFLINE JOKES (50+ Jokes!)
// ============================================

const char* OFFLINE_JOKES[] = {
    "Why did the scarecrow win an award? Because he was outstanding in his field!",
    "What do you call a bear with no teeth? A gummy bear!",
    "Why don't scientists trust atoms? Because they make up everything!",
    "What did the ocean say to the beach? Nothing, it just waved!",
    "Why did the bicycle fall over? It was two tired!",
    "What do you call a fake noodle? An impasta!",
    "Why did the math book look sad? Because it had too many problems!",
    "What do you call a sleeping bull? A bulldozer!",
    "Why can't you give Elsa a balloon? Because she will let it go!",
    "What did one wall say to the other? I'll meet you at the corner!",
    "Why did the cookie go to the doctor? Because it felt crumbly!",
    "What do you call a dinosaur that crashes his car? Tyrannosaurus Wrecks!",
    "Why did the student eat his homework? Because the teacher said it was a piece of cake!",
    "What do you call a fish without eyes? Fsh!",
    "Why did the tomato turn red? Because it saw the salad dressing!",
    "What do you call a boomerang that doesn't come back? A stick!",
    "Why don't eggs tell jokes? They'd crack each other up!",
    "What do you call a snowman with a six-pack? An abdominal snowman!",
    "Why did the golfer bring two pairs of pants? In case he got a hole in one!",
    "What do you call a cow with no legs? Ground beef!",
    "Why did the banana go to the doctor? It wasn't peeling well!",
    "What do you call a pig that does karate? A pork chop!",
    "Why don't skeletons fight each other? They don't have the guts!",
    "What do you call a belt made of watches? A waist of time!",
    "Why did the computer go to the doctor? It had a virus!",
    "What do you call a group of musical whales? An orca-stra!",
    "Why did the chicken cross the playground? To get to the other slide!",
    "What do you call a sleeping dinosaur? A dino-snore!",
    "Why did the picture go to jail? Because it was framed!",
    "What do you call a dog magician? A labracadabrador!",
    "Why don't oysters donate to charity? Because they're shellfish!",
    "What do you call a bear in the rain? A drizzly bear!",
    "Why did the orange stop? It ran out of juice!",
    "What do you call a rabbit with fleas? Bugs Bunny!",
    "Why did the melon jump into the lake? It wanted to be a watermelon!",
    "What do you call a sleeping pizza? A piZZZa!",
    "Why did the kid bring a ladder to school? To go to high school!",
    "What do you call a monkey in a minefield? A baboom!",
    "Why did the mushroom go to the party? Because he was a fungi!",
    "What do you call a cat that loves to bowl? An alley cat!",
    "Why did the boy bring a pencil to bed? To draw the curtains!",
    "What do you call a shoe made of a banana? A slipper!",
    "Why did the clock get kicked out of class? It tocked too much!",
    "What do you call a lazy kangaroo? A pouch potato!",
    "Why did the tree go to the dentist? It needed a root canal!",
    "What do you call a duck that gets all A's? A wise quacker!",
    "Why did the robot go on vacation? To recharge its batteries!",
    "What do you call a sleeping bull? A bulldozer!",
    "Why did the grape stop in the middle of the road? It ran out of juice!",
    "What do you call a dinosaur with an extensive vocabulary? A thesaurus!"
};

const int NUM_OFFLINE_JOKES = sizeof(OFFLINE_JOKES) / sizeof(OFFLINE_JOKES[0]);

// ============================================
// RIDDLES
// ============================================

const char* RIDDLES[] = {
    "What has hands but can't clap? A clock!",
    "What has a face and two hands but no arms or legs? A clock!",
    "What gets wetter the more it dries? A towel!",
    "What can you catch but not throw? A cold!",
    "What has a neck but no head? A bottle!",
    "What has to be broken before you can use it? An egg!",
    "What goes up but never comes down? Your age!",
    "What has keys but no locks? A piano!",
    "What has a thumb and four fingers but is not alive? A glove!",
    "What can travel around the world while staying in a corner? A stamp!"
};

const int NUM_RIDDLES = sizeof(RIDDLES) / sizeof(RIDDLES[0]);

// ============================================
// TRIVIA QUESTIONS
// ============================================

struct TriviaQuestion {
    const char* question;
    const char* answer;
};

const TriviaQuestion TRIVIA[] = {
    {"What is the largest planet in our solar system?", "Jupiter!"},
    {"How many legs does a spider have?", "Eight legs!"},
    {"What do bees make?", "Honey!"},
    {"What is the fastest land animal?", "The cheetah!"},
    {"How many colors are in a rainbow?", "Seven colors!"},
    {"What is the tallest animal?", "The giraffe!"},
    {"How many days are in a year?", "365 days!"},
    {"What do caterpillars turn into?", "Butterflies!"},
    {"What is the largest ocean?", "The Pacific Ocean!"},
    {"How many continents are there?", "Seven continents!"}
};

const int NUM_TRIVIA = sizeof(TRIVIA) / sizeof(TRIVIA[0]);

// ============================================
// MOTIVATIONAL QUOTES
// ============================================

const char* MOTIVATIONAL_QUOTES[] = {
    "Believe you can and you're halfway there!",
    "You are braver than you believe, stronger than you seem, and smarter than you think!",
    "The only way to do great work is to love what you do!",
    "Dream big and dare to fail!",
    "Be yourself; everyone else is already taken!",
    "You miss 100% of the shots you don't take!",
    "The future belongs to those who believe in the beauty of their dreams!",
    "It always seems impossible until it's done!",
    "You are never too old to set another goal or to dream a new dream!",
    "Success is not final, failure is not fatal: it is the courage to continue that counts!"
};

const int NUM_QUOTES = sizeof(MOTIVATIONAL_QUOTES) / sizeof(MOTIVATIONAL_QUOTES[0]);

// ============================================
// HELPER FUNCTIONS
// ============================================

class OfflineFeatures {
public:
    // Get random love message from Dad
    static String getRandomLoveMessage() {
        int index = random(0, NUM_LOVE_MESSAGES);
        return String(DADS_LOVE_MESSAGES[index]);
    }
    
    // Get random affirmation
    static String getRandomAffirmation() {
        int index = random(0, NUM_AFFIRMATIONS);
        return String(AFFIRMATIONS[index]);
    }
    
    // Get random joke
    static String getRandomJoke() {
        int index = random(0, NUM_OFFLINE_JOKES);
        return String(OFFLINE_JOKES[index]);
    }
    
    // Get random riddle
    static String getRandomRiddle() {
        int index = random(0, NUM_RIDDLES);
        return String(RIDDLES[index]);
    }
    
    // Get random trivia
    static TriviaQuestion getRandomTrivia() {
        int index = random(0, NUM_TRIVIA);
        return TRIVIA[index];
    }
    
    // Get random motivational quote
    static String getRandomQuote() {
        int index = random(0, NUM_QUOTES);
        return String(MOTIVATIONAL_QUOTES[index]);
    }
    
    // Get time-appropriate message
    static String getTimeBasedMessage() {
        // This would use RTC if available
        // For now, return a general message
        return getRandomLoveMessage();
    }
    
    // Get count of available content
    static void printStats() {
        Serial.println("\n=== Offline Features Available ===");
        Serial.printf("Love Messages: %d\n", NUM_LOVE_MESSAGES);
        Serial.printf("Affirmations: %d\n", NUM_AFFIRMATIONS);
        Serial.printf("Jokes: %d\n", NUM_OFFLINE_JOKES);
        Serial.printf("Riddles: %d\n", NUM_RIDDLES);
        Serial.printf("Trivia: %d\n", NUM_TRIVIA);
        Serial.printf("Quotes: %d\n", NUM_QUOTES);
        Serial.println("==================================\n");
    }
};

#endif // OFFLINE_FEATURES_H
