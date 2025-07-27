// lib/pump_control/pump_control.cpp

#include "pump_control.h"
#include <Arduino.h>

static uint8_t _pumpPin = 255;
static bool _pumpState = false;

void pump_control_init(uint8_t pin) {
  _pumpPin = pin;
  pinMode(_pumpPin, OUTPUT);
  digitalWrite(_pumpPin, LOW);
  _pumpState = false;
}

void pump_control_on(void) {
  if (_pumpPin != 255) {
    digitalWrite(_pumpPin, HIGH);
    _pumpState = true;
  }
}

void pump_control_off(void) {
  if (_pumpPin != 255) {
    digitalWrite(_pumpPin, LOW);
    _pumpState = false;
  }
}

bool pump_control_is_on(void) {
  return _pumpState;
}
