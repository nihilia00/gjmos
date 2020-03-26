#include <stddef.h>
#include <stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static size_t current_row = 0;
static size_t current_col = 0;
static uint8_t current_color;
static uint16_t *vram_buffer;

static size_t strlen(const char *s) {
    size_t count = 0;
    
    while(*s) {
        count++;
        s++;
    }
    return count;
}

static inline uint16_t make_vga_entry(unsigned char ch) {
    return (uint16_t) ch | (uint16_t) current_color << 8;
}

static void clear_screen() {
    for(size_t y = 0; y < VGA_HEIGHT; y++) {
        for(size_t x = 0; x < VGA_WIDTH; x++) {
            vram_buffer[y * VGA_WIDTH + x] = make_vga_entry(' ');
        }
    }
}

void coninit() {
    current_color = 7;
    vram_buffer = (uint16_t *) 0xB8000;
    clear_screen();
}

void con_putchar(char ch) {
    vram_buffer[current_row * VGA_WIDTH + current_col]
        = make_vga_entry(ch);

    current_col++;
    if(current_col == VGA_WIDTH) {
        current_col = 0;

        current_row++;
        if(current_row == VGA_HEIGHT) {
            // TODO: add scroll
            current_row = 0;
        }
    }
}

void con_print(const char *s) {
    size_t len = strlen(s);

    for(size_t i = 0; i < len; i++) {
        con_putchar(s[i]);
    }
}
