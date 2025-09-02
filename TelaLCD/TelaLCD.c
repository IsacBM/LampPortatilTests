#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "st7789_lcd_pio.h"
#include "imagem.h"

int main() {
    stdio_init_all();

    // Inicializa pinos de controle
    gpio_init(PIN_DC); gpio_set_dir(PIN_DC, true);
    gpio_init(PIN_CS); gpio_set_dir(PIN_CS, true);
    gpio_init(PIN_RESET); gpio_set_dir(PIN_RESET, true);
    gpio_init(PIN_BL); gpio_set_dir(PIN_BL, true);

    // Reset físico do display
    gpio_put(PIN_RESET, 0); sleep_ms(50);
    gpio_put(PIN_RESET, 1); sleep_ms(50);

    // Liga backlight
    gpio_put(PIN_BL, 1);

    // Carrega programa PIO
    uint offset = pio_add_program(pio, &st7789_lcd_program);
    st7789_lcd_program_init(pio, sm, offset, PIN_DIN, PIN_CLK, 10.0f);

    // Inicializa display
    lcd_init(pio, sm, st7789_init_seq);

    // Define janela p''ra tela inteira''
    lcd_set_window(pio, sm, 0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1);

    // Envia pixels da imagem 
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) { // Cores corrigidas
        uint16_t color = minha_imagem[i];
        st7789_lcd_put(pio, sm, color & 0xFF);   // LSB
        st7789_lcd_put(pio, sm, color >> 8);     // MSB
    }

    while (true) {
        tight_loop_contents(); // loop eterno
    }
}
