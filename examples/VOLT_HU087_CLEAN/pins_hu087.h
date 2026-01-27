/*
 * ============================================
 * HU-087 Hardware Pin Definitions
 * ============================================
 * 
 * XiaoZhi HU-087 ESP32-S3 Watch Kit
 * Verified pin assignments
 * 
 * ============================================
 */

#ifndef PINS_HU087_H
#define PINS_HU087_H

// ============================================
// MICROPHONE (INMP441 I2S MEMS)
// ============================================

#define MIC_WS          4       // Word Select (LRCLK)
#define MIC_SCK         5       // Bit Clock (BCLK)
#define MIC_SD          6       // Data In (DOUT from microphone)
#define MIC_I2S_NUM     I2S_NUM_0

// ============================================
// SPEAKER (MAX98357A I2S Class-D Amplifier)
// ============================================

#define SPK_DOUT        7       // Data Out (DIN to amplifier)
#define SPK_BCLK        15      // Bit Clock
#define SPK_LRCK        16      // Left/Right Clock (Word Select)
#define SPK_SD_MODE     17      // Shutdown control (HIGH = enabled)
#define SPK_I2S_NUM     I2S_NUM_1

// ============================================
// DISPLAY (ST7789 1.47" IPS LCD - SPI)
// ============================================

#define LCD_SCLK        21      // SPI Clock
#define LCD_MOSI        47      // SPI Data (MOSI)
#define LCD_CS          41      // Chip Select
#define LCD_DC          40      // Data/Command
#define LCD_RST         45      // Reset
#define LCD_BL          42      // Backlight (active LOW on HU-087)

// Display dimensions
#define SCREEN_WIDTH    172
#define SCREEN_HEIGHT   320

// ============================================
// BUTTONS & LED
// ============================================

#define BTN_BOOT        0       // Boot button (main interaction button)
#define LED_BUILTIN     48      // Built-in white LED

// ============================================
// BATTERY (ADC if available)
// ============================================

// Uncomment if your HU-087 variant has battery ADC
// #define BATTERY_ADC     34

#endif // PINS_HU087_H
