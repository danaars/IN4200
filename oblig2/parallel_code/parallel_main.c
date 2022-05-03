#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "parallel_functions.h"

void import_JPEG_file(const char *filename, unsigned char **image_chars,
        int *image_height, int *image_width, int *num_components);
void export_JPEG_file(const char *filename, const unsigned char *image_chars,
        int image_height, int image_width, int num_components, int quality);

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

    if (my_rank == 0){
        printf("Input JPEG: %s\n", input_jpeg_filename);
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    }

    allocate_image(&whole_image, m, n);     // Needs to be here?

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);   // Optional
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);   // Optional

    my_m = m/num_procs + (my_rank < m % num_procs);   // Height, 1 if true, 0 if false
    my_n = n;    // Width
    my_image_chars = (unsigned char*) malloc(my_m * my_n * sizeof(unsigned char));

    allocate_image(&u, my_m, my_n);
    allocate_image(&u_bar, my_m, my_n);
    
    int rank_elems[num_procs];        // How many elements should be sent
    int displs[num_procs];          // From which index does the counting start
    rank_elems[0] = (m/num_procs + (0 < m % num_procs)) * n;
    displs[0] = 0;

    for (int i=0; i<num_procs-1; i++){
        rank_elems[i+1] = (m/num_procs + (i+1 < m % num_procs)) * n;
        displs[i+1] = rank_elems[i] + displs[i];
    }

    // Scatter the image_chars array to all processes
    MPI_Scatterv(image_chars, rank_elems, displs, MPI_UNSIGNED_CHAR, my_image_chars,
            my_m * my_n, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    convert_jpeg_to_image(my_image_chars, &u);
    iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters);

    
    MPI_Gatherv((u_bar.image_data[0]), my_m * my_n, MPI_FLOAT, (whole_image.image_data[0]),
            rank_elems, displs, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    if (my_rank == 0){
        convert_image_to_jpeg(&whole_image, image_chars);
        export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
    }

    deallocate_image(&whole_image);
    deallocate_image(&u);
    deallocate_image(&u_bar);

    free(my_image_chars);

    MPI_Finalize();

    return 0;
}
