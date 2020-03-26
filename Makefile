os:
	as boot/boot.s -o boot/boot.o -32
	gcc -c -Iinclude -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
		kernel/console.c -o kernel/console.o -m32
	gcc -c -Iinclude -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
		kernel/kernel.c -o kernel/kernel.o -m32
	gcc -T linker.ld -o gjmos.bin -ffreestanding -O2 -nostdlib \
		boot/boot.o kernel/kernel.o kernel/console.o -m32
	qemu-system-i386 -kernel gjmos.bin -m 16M

clean:
	rm boot/boot.o
	rm kernel/console.o
	rm kernel/kernel.o
	rm gjmos.bin
