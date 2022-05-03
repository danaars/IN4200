CC = gcc
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

all: simple-jpeg serial_main

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

serial_main: serial_main.o functions.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o
	$(MAKE) -C ../simple-jpeg clean

clean_exe:
	rm -f serial_main

run:
	./serial_main 0.2 10 mona_lisa_noisy.jpg ml_denoise.jpg
