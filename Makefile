CC=gcc
LD=ld
CFLAGS=-Wall -Wextra -Wpedantic -O0 -g

LDFLAGS=

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

ASMSOURCES=$(wildcard *.s)
ASMOBJECTS=$(ASMSOURCES:.s=.o)

HEX=$(ASMSOURCES:.s=.hex)
DISASM=$(ASMSOURCES:.s=.dis)
EXECUTABLE=exec
ASSEMBLY=ass.s

mc:
	gcc -g montecarlo.c -fopenmp -lm -o ./cmake-build-debug/$(EXECUTABLE)
	gcc -S -fverbose-asm -O0 -fopenmp -lm montecarlo.c -o ./cmake-build-debug/montecarlo.s
	./cmake-build-debug/$(EXECUTABLE)

mc_par:
	gcc -g montecarlo_parallel.c -fopenmp -lm -o ./cmake-build-debug/$(EXECUTABLE)
	gcc -S -fverbose-asm -O0 -fopenmp -lm montecarlo_parallel.c -o ./cmake-build-debug/montecarlo_parallel.s
	./cmake-build-debug/$(EXECUTABLE)

clean:
	rm $(EXECUTABLE) $(ASSEMBLY) $(OBJECTS) $(ASMOBJECTS) $(HEX) $(DISASM)
