#ifndef ST7789_PIO_H
#define ST7789_PIO_H

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "st7789_lcd.pio.h"

// #define SCREEN_WIDTH 320
// #define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 240   // <--- Mude para 320
#define SCREEN_HEIGHT 320
#define ST7789_ROTATION_0 0x00
#define ST7789_ROTATION_90 0x60
#define ST7789_ROTATION_180 0xC0
#define ST7789_ROTATION_270 0xA0
#define ST7789_ROTATION_TEST 0xE0
#define ST7789_ROTATION ST7789_ROTATION_180

#define PIN_DIN 19
#define PIN_CLK 18
#define PIN_CS 17
#define PIN_DC 4
#define PIN_RESET 20
#define PIN_BL 9

extern PIO pio;
extern uint sm;

extern uint8_t * buf1;
extern uint8_t * buf2;

static const uint8_t st7789_init_seq[] = {
        1, 20, 0x01,                        // Software reset
        1, 10, 0x11,                        // Exit sleep mode
        2, 2, 0x3a, 0x55,                   // Set colour mode to 16 bit
        2, 0, 0x36, ST7789_ROTATION,        // Set MADCTL: row then column, refresh is bottom to top ????
        5, 0, 0x2a, 0x00, 0x00, SCREEN_WIDTH >> 8, SCREEN_WIDTH & 0xff,   // CASET: column addresses
        5, 0, 0x2b, 0x00, 0x00, SCREEN_HEIGHT >> 8, SCREEN_HEIGHT & 0xff, // RASET: row addresses
        1, 2, 0x21,                         // Inversion on, then 10 ms delay (supposedly a hack?)
        1, 2, 0x13,                         // Normal display on, then 10 ms delay
        1, 2, 0x29,                         // Main screen turn on, then wait 500 ms
        0                                   // Terminate list
};

void lcd_set_window(PIO pio, uint sm, uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);
void lcd_init(PIO pio, uint sm, const uint8_t *init_seq);
static void lcd_write_cmd(PIO pio, uint sm, const uint8_t *cmd, size_t count);
static void st7789_start_pixels(PIO pio, uint sm);
static void lcd_set_dc_cs(bool dc, bool cs);
#endif // ST7789_PIO_H