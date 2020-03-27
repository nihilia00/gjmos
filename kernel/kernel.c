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
    con_print("The tab\t is work\ning!\n");

    for(int i = 0; i < 50; i++) {
        con_print("Hello from kernel!\n");
    }
    con_print("my new string after scro\tlling\n");

    con_print("Checking\t horizontal tab!\n");

    for(;;);
}