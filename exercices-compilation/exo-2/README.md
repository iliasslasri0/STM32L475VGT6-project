
# Compilation


### 1) - 

The command to perform the compilation : 
```
arm-none-eabi-gcc -c -OX  exo-2-1.c -o OX-optim.o
```

The first is -Os : the goal of this optimization is to have the smallest size of the file/sections; so we expect this file to be the lighter :  
```
crdn-06% size Os-optim.o 
   text	   data	    bss	    dec	    hex	filename
    163	      4	      5	    172	     ac	Os-optim.o

```

We see a remarkable size augmentation in text ( where the code is stored ), the compiler didn't perform any optimization or modification in the code : 

```
crdn-06% size O0-optim.o
   text	   data	    bss	    dec	    hex	filename
    249	      4	      5	    258	    102	O0-optim.o

```

The lack of modification can be seen in the assembly code, as we can see that ( using arm-none-eabi-objdump -d .. ) the code lenght increased.


Optimazing using -O1, we can see ( using ) that the code lenght occupies 0x68, less than the -O0 file, that his code occupies 0xb0, and more than the -Os file where tje code occupies 0x64. ( we can see the same thing in the text size below)

```
crdn-06% size O1-optim.o       ~/Desktop/SE203/iliass-lasri/exercices-compilation/exo-2
   text	   data	    bss	    dec	    hex	filename
    170	      4	      5	    179	     b3	O1-optim.o
```


Optimazing using -O2, has no effect greater than -O1, if we want 

```
crdn-06% size O2-optim.o       ~/Desktop/SE203/iliass-lasri/exercices-compilation/exo-2
   text	   data	    bss	    dec	    hex	filename
    170	      4	      5	    179	     b3	O2-optim.o
crdn-06% arm-none-eabi-objdump -d O2-optim.o

O2-optim.o:     file format elf32-littlearm


Disassembly of section .text.startup:

00000000 <main>:
   0:	e3a0300c 	mov	r3, #12
   4:	e92d4030 	push	{r4, r5, lr}
   8:	e59f504c 	ldr	r5, [pc, #76]	@ 5c <main+0x5c>
   c:	e5d54004 	ldrb	r4, [r5, #4]
  10:	e2844001 	add	r4, r4, #1
  14:	e20440ff 	and	r4, r4, #255	@ 0xff
  18:	e24dd00c 	sub	sp, sp, #12
  1c:	e5c54004 	strb	r4, [r5, #4]
  20:	e59f0038 	ldr	r0, [pc, #56]	@ 60 <main+0x60>
  24:	e284400c 	add	r4, r4, #12
  28:	e5853000 	str	r3, [r5]
  2c:	ebfffffe 	bl	0 <puts>
  30:	e58d4000 	str	r4, [sp]
  34:	e59f1028 	ldr	r1, [pc, #40]	@ 64 <main+0x64>
  38:	e5d53004 	ldrb	r3, [r5, #4]
  3c:	e5952000 	ldr	r2, [r5]
  40:	e5911000 	ldr	r1, [r1]
  44:	e59f001c 	ldr	r0, [pc, #28]	@ 68 <main+0x68>
  48:	ebfffffe 	bl	0 <printf>
  4c:	e3a00000 	mov	r0, #0
  50:	e28dd00c 	add	sp, sp, #12
  54:	e8bd4030 	pop	{r4, r5, lr}
  58:	e12fff1e 	bx	lr
	...
  68:	00000010 	.word	0x00000010
```

But there is a difference in the assembly code as the code (yes they have the same size) & the operations, are "not that" different, the compiler just performed some permutations of instructions, there is also differences in the immediate values.


As a small conclusion, optimization flags affect code generation and not data sections, we didn't see any changes in the sizes of .data and .bss sections when we change optimization levels. 

### 2) -Remplacez const char mesg[] par static const char mesg[]. Expliquez les différences dans les sections de données par rapport à la question précédente (elles dépendent ici aussi des optimisations).

