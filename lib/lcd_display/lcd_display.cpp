// lib/lcd_display/lcd_display.cpp

#include "lcd_display.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Default I2C address for most 16x2 LCD modules with backpack
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

static LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void lcd_init() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void lcd_clear() {
  lcd.clear();
}

void lcd_print(uint8_t row, uint8_t col, const String& text) {
  if (row >= LCD_ROWS || col >= LCD_COLS) return;
  lcd.setCursor(col, row);
  lcd.print(text);
}
