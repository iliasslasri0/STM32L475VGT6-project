.syntax unified
.arch armv7-m
.cpu cortex-m4
.global _start
.thumb
.thumb_func


_start:
	ldr sp, =_strt_stack
	bl init_bss
	b main
