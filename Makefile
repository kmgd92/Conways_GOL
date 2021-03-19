CC := gcc
CFLAGS := -g -Wall -Werror -O -std=c99 -D_DEFAULT_SOURCE
LDFLAGS := -lncurses


SOURCEFILES := parser.c term.c main.c

all: life

life: $(patsubst %.c,src/%.o,$(SOURCEFILES))
	$(CC) -o $@ $^ $(LDFLAGS)

test: life
	@echo
	@echo "Testing a static block; you should make sure this one works first!"
	@echo
	./life inputs/block.life 0 > outputs/block.output.txt
	@cmp -s outputs/block.expected.txt outputs/block.output.txt \
	    || printf "\nblock not as expected at generation 0\n\n"
	@echo
	@echo "Testing an oscillator with period 2 for three generations"
	@echo
	./life inputs/blinker.rle 0 > outputs/blinker.output.txt
	./life inputs/blinker.rle 1 >> outputs/blinker.output.txt
	./life inputs/blinker.rle 2 >> outputs/blinker.output.txt
	@cmp -s outputs/blinker.expected.txt outputs/blinker.output.txt \
	    || printf "\nblinker not as expected for first three generations\n\n"
	@echo



%.o: %.c Makefile
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *~ src/*~ src/*.o life life.tar outputs/*.output.txt
	rm -f core core.* vgcore.*

.PHONY: all clean submission
