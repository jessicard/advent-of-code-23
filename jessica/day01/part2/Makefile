# Set CC to gcc to use gcc as our C compiler
CC = gcc

# Compilation options:
# -g: include debugging info symbols
# -Wall: enable all warnings
# -Wpedantic -std=c17: enforces the C17 language standard

CFLAGS = -g -Wall -Wpedantic -std=c17

prog: prog.o

# Remove build artifacts
.PHONY: clean
clean:
	rm -f *.o a.out prog

.PHONY: all
all: clean prog
