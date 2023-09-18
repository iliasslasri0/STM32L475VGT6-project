syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:
mov r0, #0x10000300
mov r1, #0x10000000
mov r3, #128
loop:
    ldr r2, [r1]
    str r2, [r0]
    add r0, #4
    add r1, #4
    subs r3, #1
    bne loop

end: b end

