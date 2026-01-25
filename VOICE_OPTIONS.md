# 🎤 VOLT Voice Options

## Current Voice: **ECHO** 🔊

VOLT currently uses **ECHO** - a warm, conversational male voice that's perfect for being a supportive buddy to Stone.

---

## 🎭 All Available Voices

### 1. **ECHO** ⭐ (Current)

- **Type:** Male, warm, conversational
- **Best for:** Being a supportive friend, everyday conversations
- **Personality:** Natural, friendly, encouraging
- **Age feel:** Young adult/older brother vibe
- **Perfect for:** Stone's current age (8 years old)

### 2. **NOVA**

- **Type:** Female, bright, energetic
- **Best for:** High-energy encouragement, girls, upbeat conversations
- **Personality:** Enthusiastic, positive, lively
- **Age feel:** Young, energetic
- **Good for:** Kids who respond well to female voices

### 3. **FABLE**

- **Type:** Male, warm, storytelling
- **Best for:** Bedtime stories, calm conversations, teaching moments
- **Personality:** Wise, gentle, narrative
- **Age feel:** Mature, storyteller
- **Good for:** Calming anxious kids, story time

### 4. **SHIMMER**

- **Type:** Female, soft, gentle
- **Best for:** Anxious kids, bedtime, calming situations
- **Personality:** Soothing, nurturing, calm
- **Age feel:** Gentle, motherly
- **Good for:** Kids who need extra comfort

### 5. **ALLOY**

- **Type:** Neutral, smooth
- **Best for:** General purpose, any situation
- **Personality:** Balanced, clear, professional
- **Age feel:** Neutral
- **Good for:** When you want a neutral option

### 6. **ONYX**

- **Type:** Male, deep, authoritative
- **Best for:** Older kids, serious conversations
- **Personality:** Strong, confident, mature
- **Age feel:** Adult, authoritative
- **Good for:** Older children (10+)

---

## 🔄 How to Change VOLT's Voice

### Option 1: Edit Before Flashing (Easiest)

1. **Open** `voice.h` in VSCode
2. **Find this line** (around line 23):
   ```cpp
   const char* TTS_VOICE = "echo";
   ```
3. **Change to your preferred voice:**
   ```cpp
   const char* TTS_VOICE = "nova";     // For bright female
   const char* TTS_VOICE = "fable";    // For storytelling male
   const char* TTS_VOICE = "shimmer";  // For gentle female
   const char* TTS_VOICE = "alloy";    // For neutral
   const char* TTS_VOICE = "onyx";     // For deep male
   ```
4. **Save** the file (Ctrl+S)
5. **Flash** to watch as normal

### Option 2: Via API (After Flashing)

You can change the voice remotely by editing the voice.h file and re-flashing, or by modifying the TTS request in the firmware.

---

## 🎯 Voice Recommendations by Situation

### For Stone (8-year-old boy):

- **Primary:** ECHO ⭐ (current) - Perfect supportive buddy
- **Alternative:** FABLE - Good for calming/stories
- **High energy:** NOVA - If he responds well to upbeat

### For Girls:

- **Primary:** NOVA - Bright, energetic female
- **Alternative:** SHIMMER - Gentle, nurturing
- **Neutral:** ALLOY - Works for anyone

### For Anxious Kids:

- **Primary:** SHIMMER - Soft, calming
- **Alternative:** FABLE - Gentle storyteller
- **Backup:** ECHO - Warm and supportive

### For Older Kids (10+):

- **Primary:** ONYX - Mature, confident
- **Alternative:** ECHO - Still friendly but mature
- **Neutral:** ALLOY - Professional

### For Bedtime:

- **Primary:** FABLE - Storytelling voice
- **Alternative:** SHIMMER - Gentle, soothing
- **Backup:** ECHO (slower speed)

---

## ⚙️ Voice Speed Settings

You can also adjust how fast VOLT talks:

In `voice.h`, find:

```cpp
const float TTS_SPEED = 1.08;  // Current: Slightly energetic
```

**Speed Options:**

- `0.75` - Slow (good for bedtime, anxious kids)
- `0.90` - Slightly slow (clear, easy to understand)
- `1.00` - Normal speed
- `1.08` - Current (slightly energetic) ⭐
- `1.25` - Fast (high energy, older kids)
- `1.50` - Very fast (not recommended for young kids)

---

## 🎨 Voice Personality Tips

### Making ECHO Sound Natural:

The firmware already formats text for natural delivery:

- ✅ Uses contractions ("you're" not "you are")
- ✅ Short sentences (under 15 words)
- ✅ Exclamation points for enthusiasm
- ✅ Ellipsis (...) for natural pauses
- ✅ Direct address ("Hey Stone!")
- ✅ Sound effects ("ZZZAP!", "Beep boop!")

### Voice + Speed Combinations:

**Energetic Buddy:**

- Voice: ECHO or NOVA
- Speed: 1.08 - 1.15
- Perfect for: Daytime, encouragement

**Calm Companion:**

- Voice: SHIMMER or FABLE
- Speed: 0.85 - 0.95
- Perfect for: Bedtime, anxiety

**Balanced Friend:**

- Voice: ECHO or ALLOY
- Speed: 1.00
- Perfect for: General use

---

## 🚀 Quick Change Guide

**To change voice RIGHT NOW before flashing:**

1. Open `volt v5.00 flash` folder in VSCode
2. Open `voice.h` file
3. Change line 23 from:
   ```cpp
   const char* TTS_VOICE = "echo";
   ```
   To your choice:
   ```cpp
   const char* TTS_VOICE = "nova";  // or fable, shimmer, alloy, onyx
   ```
4. Save (Ctrl+S)
5. Flash to watch (click → in bottom bar)

**Done!** VOLT will now use the new voice.

---

## 🎧 Voice Samples

You can hear samples of all voices at:
**https://platform.openai.com/docs/guides/text-to-speech**

Listen to each voice saying the same text to compare!

---

## 💡 Pro Tips

1. **Try different voices** - Kids respond differently to different voices
2. **Match the mood** - Use SHIMMER for bedtime, ECHO for daytime
3. **Speed matters** - Slower = calmer, faster = more energetic
4. **You can change anytime** - Just edit voice.h and re-flash
5. **Test with Stone** - Let him hear different voices and pick his favorite!

---

## 📊 Voice Comparison Chart

| Voice       | Gender  | Energy | Best Age | Best Use             |
| ----------- | ------- | ------ | -------- | -------------------- |
| **ECHO** ⭐ | Male    | Medium | 6-12     | Daily buddy          |
| NOVA        | Female  | High   | 6-12     | Energetic support    |
| FABLE       | Male    | Low    | 5-10     | Stories, calm        |
| SHIMMER     | Female  | Low    | 5-10     | Comfort, bedtime     |
| ALLOY       | Neutral | Medium | All      | General purpose      |
| ONYX        | Male    | Medium | 10+      | Mature conversations |

---

## ❓ Which Voice Should You Use?

### Stick with ECHO if:

- ✅ Stone likes male voices
- ✅ You want a supportive buddy vibe
- ✅ Current voice is working well
- ✅ You want warm, conversational tone

### Try NOVA if:

- 🔄 Stone responds better to female voices
- 🔄 You want more energetic encouragement
- 🔄 Stone likes upbeat, bright personalities

### Try FABLE if:

- 🔄 Stone gets anxious easily
- 🔄 You want a calming, storytelling voice
- 🔄 Bedtime use is important

### Try SHIMMER if:

- 🔄 Stone needs extra comfort
- 🔄 Female voice + gentle tone is preferred
- 🔄 Anxiety/worry is a concern

---

**Current Setup:** ECHO voice at 1.08x speed - Perfect for Stone! 🎯

**Want to change?** Edit `voice.h` before flashing!
