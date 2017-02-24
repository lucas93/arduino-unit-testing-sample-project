#ifndef BLINK_LIB_H
#define BLINK_LIB_H

#include <stdint.h>

/**
 * Setup for blinking.
 *
 * @param pin - pin number
 **/
void blink_setup(uint8_t pin=13);


/**
 * Blink a single time for the specified duration.
 *
 * @param duration - duration in miliseconds
 * @param pin      - pin number
 **/
void blink(unsigned long duration, uint8_t pin=13);


#endif // BLINK_LIB_H
