CC = arm-none-eabi-gcc -ffreestanding
INCLUDE1 = -ICMSIS/Device/ST/STM32L4xx/Include
INCLUDE2 = -ICMSIS/Include
WARNINGS = -Wall -Werror -Wextra
CFLAGS  = -c -g -O1 -ffreestanding $(WARNINGS) $(INCLUDE1) $(INCLUDE2)
TARGET_ARCH = -mcpu=cortex-m4 -mthumb $(FPU)
LDFLAGS = -nostdlib -T ld_ram.lds
AS    = arm-none-eabi-as
FPU = -mfloat-abi=hard -mfpu=fpv4-sp-d16

main : main.o crt0.o init.o led.o clocks.o uart.o

crt0.o : crt0.s

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

clean:
	rm -f main.o
	rm -f crt0.o
	rm -f init.o
	rm -f led.o
	rm -f uart.o
run:
	arm-none-eabi-gdb -x se203.gdb main

.PHONY: clean run
