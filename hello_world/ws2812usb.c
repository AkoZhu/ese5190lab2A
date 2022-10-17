/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.h"






int main() {
    stdio_init_all();
    printf("WS2812 Smoke Test, using pin %d", WS2812_PIN);

    gpio_init(PICO_DEFAULT_WS2812_POWER_PIN);
    gpio_set_dir(PICO_DEFAULT_WS2812_POWER_PIN, 1);

    gpio_put(PICO_DEFAULT_WS2812_POWER_PIN, 1);

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);



    uint32_t blue = 0x0000ff;
    uint32_t red = 0xff0000;
    uint32_t green = 0x00ff00;

    while (true) {
        sleep_ms(1000);
        printf("Input 'r', 'g', or 'b' to choose your color: \n");

        char c = getchar_timeout_us(4*1000*1000);

        if(c == PICO_ERROR_TIMEOUT) {printf("Error input!\n");}
        printf("%d\n",c);
        if(c == 'r'){
            set_neopixel_color(red);
        }else if(c == 'g'){
            set_neopixel_color(green);     
        }else if (c == 'b'){
            set_neopixel_color(blue);
        }else {
            printf("Please input a valid character. ");
        }
        sleep_ms(1000);
        // set_neopixel_color(0xff0000);
        // printf("Red");
        // set_neopixel_color(0x00ff00);
        // printf("Green");
        // set_neopixel_color(0x0000ff);
        // printf("Blue");

        // set_neopixel_color(0, 0, 0xff);
    }
    return 0;
}
