// lib/moisture_sensor/moisture_sensor.h

#ifndef MOISTURE_SENSOR_H
#define MOISTURE_SENSOR_H

#include <stdint.h>

/**
 * @brief Initialize the soil moisture sensor pin.
 *
 * @param pin Arduino analog pin connected to the sensor (e.g. A0).
 */
void moisture_sensor_init(uint8_t pin);

/**
 * @brief Read raw ADC value from the soil moisture sensor.
 *
 * @return 12‑bit ADC reading (0–1023), higher value = drier soil.
 */
int moisture_sensor_read(void);

#endif // MOISTURE_SENSOR_H
