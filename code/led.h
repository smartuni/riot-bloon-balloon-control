#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "xtimer.h"
#include "color.h"

#include "apa102.h"
#include "apa102_params.h"

#ifndef LED_BRIGHTNESS
#define N_LEDS 2  // Anzahl LEDs
#endif

#ifndef LED_BRIGHTNESS
#define LED_BRIGHTNESS 128
#endif

extern apa102_t dev;
extern color_rgba_t leds[N_LEDS];

typedef enum {OFF, WHITE, RED, BLUE, GREEN, YELLOW, ORANGE, PURPLE} my_color;

extern int setLEDColor(uint8_t led, my_color color);
extern void initLEDs(gpio_t data_pin, gpio_t clk_pin);