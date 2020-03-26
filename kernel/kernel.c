#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <float.h>
#include <iso646.h>

#include <console.h>

void kernel_main() {
    coninit();
    con_print("Hello from kernel!\n");

    for(;;);
}