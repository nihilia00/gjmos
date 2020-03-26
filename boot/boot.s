.section .multiboot
.align 4
.long 0x1BADB002
.long (1 << 0) | (1 << 1)
.long -(0x1BADB002 + ((1 << 0) | (1 << 1)))

.section .bss
.align 16
stack_bottom:
.skip 16384     # 16 KB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    /* interrupts disabled, paging disabled, 32-bit protected mode */
    mov $stack_top, %esp
    /* gdt, paging */
    call kernel_main

    cli
loop:
    hlt
    jmp loop
