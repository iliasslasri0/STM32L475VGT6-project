.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:
mov r0, #0xdead
mov r1, #0xbeef

mov r2,#0x10000000
mov r3, 64

loop: str r0, [r2]
      str r1, [r2,#2]
      add r2, #4
      subs r3, #1
      bne loop

end: b end
