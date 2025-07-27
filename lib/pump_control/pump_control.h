// lib/pump_control/pump_control.h

#ifndef PUMP_CONTROL_H
#define PUMP_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initialize the pump control pin.
 * 
 * @param pin Arduino digital pin connected to relay module controlling the pump.
 */
void pump_control_init(uint8_t pin);

/**
 * @brief Turn the pump on (activate relay).
 */
void pump_control_on(void);

/**
 * @brief Turn the pump off (deactivate relay).
 */
void pump_control_off(void);

/**
 * @brief Get current pump state.
 * 
 * @return true if pump is on, false otherwise.
 */
bool pump_control_is_on(void);

#endif // PUMP_CONTROL_H
