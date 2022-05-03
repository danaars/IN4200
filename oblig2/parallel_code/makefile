CC = mpicc
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

all: simple-jpeg parallel_main

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

parallel_main: parallel_main.o parallel_functions.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o 
	#$(MAKE) -C ../simple-jpeg clean

clean_exe:
	rm -f parallel_main

run:
	mpirun -np 2 parallel_main 0.2 10 mona_lisa_noisy.jpg ml_denoise.jpg	
