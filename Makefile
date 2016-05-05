
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline


signaler: signaler.o

.PHONY: clean debug

clean:
	-rm *.o
	-rm signaler

debug: CFLAGS+=-g
debug: signaler
