#include <stddef.h>
#include <stdint.h>

static const int TAB_SPACES = 4;
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

static void memset(void *memory, size_t nbytes, unsigned char value) {
    unsigned char *memory_bytes = memory;

    for(size_t i = 0; i < nbytes; i++) {
        memory_bytes[i] = value;
    }
}

static void memcpy(void *from, void *to, size_t nbytes) {
    unsigned char *from_bytes = from;
    unsigned char *to_bytes = to;

    for(size_t i = 0; i < nbytes; i++) {
        to_bytes[i] = from_bytes[i];
    }
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

static void scroll_up() {
    uint16_t *pcurrent_row, *pprevious_row, *plast_row;
    size_t row_bytes = VGA_WIDTH * 2;

    // move rows up
    for(size_t i = 1; i < VGA_HEIGHT; i++) {
        pcurrent_row = vram_buffer + (i * VGA_WIDTH);
        pprevious_row = vram_buffer + ((i - 1) * VGA_WIDTH);

        memcpy(pcurrent_row, pprevious_row, row_bytes);
    }

    // clear last row
    plast_row = vram_buffer + ((VGA_HEIGHT - 1) * VGA_WIDTH);
    memset(plast_row, row_bytes, 0);
    current_col = 0;
    current_row--;
}

void coninit() {
    current_color = 7;
    vram_buffer = (uint16_t *) 0xB8000;
    clear_screen();
}

void con_putchar(char ch) {
    if(ch == '\n') {
        current_row++;
        current_col = 0;
    } else if(ch == '\t') {
        current_col += TAB_SPACES;
    } else {
        vram_buffer[current_row * VGA_WIDTH + current_col]
            = make_vga_entry(ch);
        current_col++;
    }

    if(current_col == VGA_WIDTH) {
        current_col = 0;
        current_row++;
    }

    if(current_row == VGA_HEIGHT) {
        scroll_up();
    }
}

void con_print(const char *s) {
    size_t len = strlen(s);

    for(size_t i = 0; i < len; i++) {
        con_putchar(s[i]);
    }
}
