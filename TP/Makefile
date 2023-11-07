CC = arm-none-eabi-gcc
AS = arm-none-eabi-as


CFLAGS    = -g -O1 -ffreestanding
CFLAGS   += -Wall -Werror -Wextra
CPPFLAGS  = -ICMSIS/Include
CPPFLAGS += -ICMSIS/Device/ST/STM32L4xx/Include

ASFLAGS = -g

TARGET_ARCH  = -mcpu=cortex-m4 -mthumb $(FPU)
TARGET_ARCH += -mfloat-abi=hard -mfpu=fpv4-sp-d16

LDFLAGS = -nostdlib -T ld_ram.lds

OBJS = main.o crt0.o init.o led.o uart.o matrix.o image.o irq.o buttons.o

main : $(OBJS) clocks.o

%.o : %.raw
	arm-none-eabi-objcopy -B arm -I binary -O elf32-littlearm $< $@

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

clean:
	rm -f $(OBJS)
run:
	arm-none-eabi-gdb -x se203.gdb main

.PHONY: clean run connect
