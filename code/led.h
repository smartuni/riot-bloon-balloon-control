#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "xtimer.h"
#include "color.h"

#include "apa102.h"
#include "apa102_params.h"

#define N_LEDS 1  // Anzahl LEDs

extern apa102_t dev;
extern color_rgba_t leds[N_LEDS];

typedef enum {OFF, RED, BLUE, GREEN, YELLOW} my_color;

extern int setLEDColor(uint8_t led, my_color color, uint8_t alpha);
extern void initLEDs(gpio_t data_pin, gpio_t clk_pin);