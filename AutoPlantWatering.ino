// AutoPlantWatering.ino
// Main sketch for the Automatic Plant Watering System (Updated)

// Avoid using Arduino String for embedded reliability
#include <Arduino.h>
#include "lcd_display.h"
#include "moisture_sensor.h"
#include "pump_control.h"

// Pin definitions
static const uint8_t MOISTURE_PIN = A0;
static const uint8_t PUMP_PIN     = 7;

// Soil‐dry threshold (0–1023). Tweak this after calibration.
static const int DRY_THRESHOLD = 600;

// Sampling interval (ms)
static const unsigned long SAMPLE_INTERVAL = 5000;

unsigned long lastSampleTime = 0;

void setup() {
  Serial.begin(9600);

  // Initialize LCD (I²C 0x27, 16×2)
  lcd_init();
  lcd_clear();
  lcd_print(0, 0, "Plant Watering");
  lcd_print(1, 0, "System Booting");
  delay(2000);
  lcd_clear();

  // Initialize modules
  moisture_sensor_init(MOISTURE_PIN);
  pump_control_init(PUMP_PIN);

  // Show ready status
  lcd_print(0, 0, "Soil Moisture:");
  lcd_print(1, 0, "Waiting...");
}

void loop() {
  unsigned long now = millis();
  if (now - lastSampleTime < SAMPLE_INTERVAL) {
    return;
  }
  lastSampleTime = now;

  // 1. Read raw sensor value (0 = wet, 1023 = dry)
  int raw = moisture_sensor_read();

  // 2. Map to percentage (0% = dry, 100% = wet)
  int moisturePct;
  if (raw <= DRY_THRESHOLD) {
    // wet side
    moisturePct = map(raw, 0, DRY_THRESHOLD, 100, 0);
  } else {
    // dry beyond threshold
    moisturePct = 0;
  }
  moisturePct = constrain(moisturePct, 0, 100);

  // 3. Display on Serial & LCD
  Serial.printf("Soil: %d%% (raw=%d)\n", moisturePct, raw);
  char buf[17];
  snprintf(buf, sizeof(buf), "Moisture: %3d%%", moisturePct);
  lcd_print(0, 0, buf);

  // 4. Watering logic
  if (raw > DRY_THRESHOLD) {
    pump_control_on();
    Serial.println("Pump: ON");
    lcd_print(1, 0, "Watering...    ");
  } else {
    pump_control_off();
    Serial.println("Pump: OFF");
    lcd_print(1, 0, "Conditions OK  ");
  }
}
