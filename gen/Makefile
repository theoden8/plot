CFLAGS = -O3 -std=c99 -Wno-implicit-int -lm -lc
OBJECTS = $(wildcard *.c)

all: $(patsubst %.c, %, $(OBJECTS))

%: %.c
	$(CC) $(CFLAGS) $< -o bin_$@

clean:
	rm -vf bin_*
