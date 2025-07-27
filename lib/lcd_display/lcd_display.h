// lib/lcd_display/lcd_display.h

#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>

/**
 * @brief Initialize the I2C LCD display (default 16x2, addr 0x27).
 */
void lcd_init();

/**
 * @brief Clear the LCD screen.
 */
void lcd_clear();

/**
 * @brief Print a string at a specific row and column.
 * 
 * @param row Row number (0 or 1 for 16x2 LCD).
 * @param col Column number (0–15).
 * @param text Text string to display.
 */
void lcd_print(uint8_t row, uint8_t col, const String& text);

#endif // LCD_DISPLAY_H
