connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

main.o : main.c
	arm-none-eabi-gcc -c -g -O1 -mcpu=cortex-m4 -mthumb main.c -o main.o

main : main.o
	arm-none-eabi-gcc -nostdlib -T ld_ram.lds main.o -o main
