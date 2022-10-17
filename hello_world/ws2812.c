#include "ws2812.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t rgbTgrb(uint32_t rgb){
    uint32_t r = rgb & 0xff0000;
    uint32_t g = rgb & 0x00ff00;
    uint32_t b = rgb & 0x0000ff;
    return 
        (r >> 8 | g << 8 | b);
}

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}


void set_neopixel_color(uint32_t color) {
    put_pixel(rgbTgrb(color));
}