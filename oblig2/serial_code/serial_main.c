#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

// import_JPEG_file and export_JPEG_file defined in import_export_jpeg.c
void import_JPEG_file(const char *filename, unsigned char **image_chars,
        int *image_height, int *image_width, int *num_components);

void export_JPEG_file(const char* filename, const unsigned char* image_chars,
        int image_height, int image_width, int num_components, int quality);

int main(int argc, char* argv[])
{
    int m, n, c, iters;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;

    // Read from command line
    kappa = atof(argv[1]);
    iters = atoi(argv[2]);
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];
    printf("Input JPEG: %s\n", input_jpeg_filename);

    // m, n and c obtains values from this func
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    printf("c = %d\n", c);
    printf("Number of iterations: %d\n", iters);

    allocate_image(&u, m, n);
    allocate_image(&u_bar, m, n);
    /*
    printf("Before conversion, int top left pixel:%d\n", u.image_data[0][0]);
    printf("Before conversion, unsigned char top left pixel:%u\n", u.image_data[0][0]);
    printf("Before conversion, float top left pixel:%f\n", u.image_data[0][0]);
    printf("Before conversion, char top left pixel:%c\n", u.image_data[0][0]);
    */


    convert_jpeg_to_image(image_chars, &u);
    //printf("After conversion, unsigned char top left pixel:%u\n", u.image_data[0][0]);
    //printf("After conversion, int top left pixel of u:%d\n", u.image_data[0][0]);
    //printf("After conversion, float top left pixel of u:%f\n", u.image_data[0][0]);
    //printf("Max float: %f\n", (2-pow(2, -23))*pow(2, 127));

    iso_diffusion_denoising(&u, &u_bar, kappa, iters);

    //printf("After denoising algorithm\n");
    //printf("top left pixel u_bar: %f\n", u_bar.image_data[0][0]);
    convert_image_to_jpeg(&u_bar, image_chars);
    //convert_image_to_jpeg(&u_bar, image_chars);
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

    deallocate_image(&u);
    deallocate_image(&u_bar);


    return 0;
}
