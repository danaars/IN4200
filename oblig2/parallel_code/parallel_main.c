#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "../one_folder/simple-jpeg/import_export_jpeg.h"
#include "parallel_functions.h"

int main(int argc, char *argv[]){

    int m, n, c, iters;
    int my_m, my_n, my_rank, num_procs;
    float kappa;
    image u, u_bar, whole_image;
    unsigned char *image_chars, *my_image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    kappa = atof(argv[1]);
    iters = atoi(argv[2]);
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];

    /* Sanity check, works this far
    printf("kappa: %f\n", kappa);
    printf("iters: %d\n", iters);
    printf("jpeg input filename: %s\n", input_jpeg_filename);
    printf("jpeg output filename: %s\n", output_jpeg_filename);
    */

    if (my_rank == 0){
        printf("Input JPEG: %s\n", input_jpeg_filename);
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
        printf("Grayscale? expect 1, get: %d\n", c);
        //allocate_image(&whole_image, m, n);
        printf("Rank 0 has m: %d, n: %d\n", m, n);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);   // Optional
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);   // Optional

    //printf("m: %d, n: %d\n");
    my_m = m/num_procs + (my_rank < m % num_procs);   // Height, 1 if true, 0 if false
    my_n = n;    // Width

    //printf("My rank: %d, my image: (%d, %d)\n", my_rank, my_m, my_n);
    allocate_image(&u, my_m, my_n);
    allocate_image(&u_bar, my_m, my_n);

    //printf("Riktig frem hit\n");
    
    int rank_ind[num_procs+1];
    *rank_ind = 0;
    for (int i=0; i<num_procs-1; i++){
        rank_ind[i+1] = rank_ind[i] + m/num_procs + (i+1 < m % num_procs);
    }
    rank_ind[num_procs] = m;

    /*
    for (int rank=0; rank < num_procs-1; rank++){
        int j = 0;
        for (int i=rank_ind[rank]; i < rank_ind[rank + 1]; i++){
            MPI_Send(image_chars[i], n, MPI_FLOAT, (u->image_data)[j], rank, MPI_COMM_WORLD);
            MPI_Recv((u->image_data)[i], n, MPI_FLOAT, )<++>
            j++;
        }<++>
    }<++>
    MPI_Send()<++>
    */

    //convert_jpeg_to_image(my_image_chars, &u);
    //iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters);
    
    MPI_Finalize();

    return 0;
}
