CC = mpicc
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

all: simple-jpeg parallel_main

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

parallel_main: parallel_main.o import_export_jpeg.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o 
	$(MAKE) -C ../one_folder/simple-jpeg clean

clean_exe:
	rm -f parallel_main

run:
	mpirun -np 2 parallel_main 0.2 10 dogg.jpg john.jpg	
