#include "led.h"

apa102_t dev;
color_rgba_t leds[N_LEDS];

int setLEDColor(uint8_t led, my_color color, uint8_t alpha){
    if(led >= N_LEDS){
        return -1;
    }
    leds[led].alpha = alpha;
    switch(color){
        case OFF: {
            leds[led].color.b = 0;
            leds[led].color.g = 0;
            leds[led].color.r = 0;
            break;
        }
        case RED: {
            leds[led].color.b = 0;
            leds[led].color.g = 0;
            leds[led].color.r = 255;
            break;
        }
        case BLUE: {
            leds[led].color.b = 255;
            leds[led].color.g = 0;
            leds[led].color.r = 0;
            break;
        }
        case GREEN: {
            leds[led].color.b = 0;
            leds[led].color.g = 255;
            leds[led].color.r = 0;
            break;
        }
        case YELLOW: {
            leds[led].color.b = 0;
            leds[led].color.g = 255;
            leds[led].color.r = 255;
            break;
        }
        default: break;
    }
    apa102_load_rgba(&dev, leds);
    return 0;
}

void initLEDs(gpio_t data_pin, gpio_t clk_pin){
    /* initialize all LED color values to black (off) */
    memset(leds, 0, sizeof(color_rgba_t) * N_LEDS);
    // Set all LEDs to maximum brightness
    for(uint8_t i=0; i<N_LEDS; i++){
        leds[i].alpha = 255;
    }
    dev.led_numof = N_LEDS;
    dev.data_pin = data_pin;
    dev.clk_pin = clk_pin;
    gpio_init(dev.data_pin, GPIO_OUT);
    gpio_init(dev.clk_pin, GPIO_OUT);
    gpio_clear(dev.data_pin);
    gpio_clear(dev.clk_pin);
    apa102_load_rgba(&dev, leds);
}