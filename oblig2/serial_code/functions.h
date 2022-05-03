#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Image struct definition
typedef struct image
{   // Stores a 2D matrix of size m x n
    float **image_data;
    int m;
    int n;
} image;

void allocate_image(image *u, int m, int n);
void deallocate_image(image *u);
void convert_jpeg_to_image(const unsigned char *image_chars, image *u);
void convert_image_to_jpeg(const image *u, unsigned char *image_chars);
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters);

#endif
