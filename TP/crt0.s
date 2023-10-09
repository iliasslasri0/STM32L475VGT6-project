.syntax unified
.global _start
.thumb

_start:
	ldr sp, =_strt_stack
	bl init_bss
	b main
