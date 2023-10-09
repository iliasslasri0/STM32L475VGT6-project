CC := arm-none-eabi-gcc
CFALGS := -Wall -Werror -g -0g -mthumb -c
LDFLAGS := -L/opt/mylibs
LIBS := -lm

SRCS := main.c t1.c t2.c
OBJS := $(SRCS:.c=.o) stubs.o

hello: $(OBJS)

stubs.o:
	$(CC) $(CFLAGS) -o $@ libs/stubs.c

clean:
	rm -f $(OBJS)

.PHONY: clean
