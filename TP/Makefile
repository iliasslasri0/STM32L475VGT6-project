CC = arm-none-eabi-gcc -ffreestanding
CFLAGS = -c -g -O1
TARGET_ARCH = -mcpu=cortex-m4 -mthumb
LDFLAGS = -nostdlib -T ld_ram.lds
AS    = arm-none-eabi-as

main : main.o crt0.o init.o

crt0.o : crt0.s

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

clean:
	rm -f main.o
	rm -f crt0.o
	rm -f init.o

.PHONY: clean
