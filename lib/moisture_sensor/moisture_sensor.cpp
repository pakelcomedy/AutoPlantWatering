// lib/moisture_sensor/moisture_sensor.cpp

#include "moisture_sensor.h"
#include <Arduino.h>

static uint8_t _moisturePin = 255;

void moisture_sensor_init(uint8_t pin) {
  _moisturePin = pin;
  pinMode(_moisturePin, INPUT);
}

int moisture_sensor_read(void) {
  if (_moisturePin == 255) {
    // Not initialized
    return -1;
  }
  // Read analog value (0 = very wet, 1023 = very dry)
  return analogRead(_moisturePin);
}
