## ReadMe - IN4200 Mandatory Assignment 2, Daniel Johan Aarstein

In both the serial and parallel case the program can be compiled by calling the make function in their respective folder. The executable will have the same name as the main program, that is `serial_main` and `parallel_main` for the respective cases. Note that `gcc 11.2.0` was used in both cases and that `MPI` needs to be functional in the parallelized case.

In addition, each folder contains one noisy picture which can be used for running the program.

By calling `make run` the relevant executabel will be called in the following manner:

`<executable> 0.2 10 mona_lisa_noisy.jpg ml_denoise.jpg`

That is; kappa = 0.2, number of iterations = 10, input filename = mona_lisa_noisy.jpg, output filename = ml_denoise.jpg.

To run the program with other parameters, call the executable manually or change the makefile.
