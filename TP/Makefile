CC = arm-none-eabi-gcc -ffreestanding
CFLAGS = -c -g -O1
TARGET_ARCH = -mcpu=cortex-m4 -mthumb
LDFLAGS = -nostdlib -T ld_ram.lds
AS    = arm-none-eabi-as

main : main.o crt0.o init.o led.o

crt0.o : crt0.s

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

clean:
	rm -f main.o
	rm -f crt0.o
	rm -f init.o
	rm -f led.o
run:
	arm-none-eabi-gdb -x se203.gdb main

.PHONY: clean run
