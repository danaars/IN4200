#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters);

void allocate_image(image *u, int m, int n)
{
    u->m = m;
    u->n = n;

    u->image_data = (float**) malloc(m * sizeof(float**));
    for (int i=0; i<m; i++){
        u->image_data[i] = (float*) malloc(n * sizeof(float*));
    }
}   // End allocate_image

void deallocate_image(image *u)
{
    for (int i=0; i<u->m; i++){
        free(u->image_data[i]);
    }
    free(u->image_data);
}   // End deallocate_image

void convert_jpeg_to_image(const unsigned char *image_chars, image *u)
{
    //float max_float = (2 - pow(2, -23)) * pow(2, 127);
    //float scaler = max_float / 255.0;
    
    //printf("input const char: %u\n", image_chars[0]);
    //printf("Scaler: %f\n", scaler);
    //printf("output float value: %f\n", image_chars[0]*scaler);
    for (int i=0; i<u->m; i++){
        for (int j=0; j<u->n; j++){
             u->image_data[i][j] = (float) (image_chars[u->n * i + j]);// * scaler);
        }
    }    
}   // End convert_jpeg_to_image

void convert_image_to_jpeg(const image *u, unsigned char *image_chars)
{
    //float max_float = (2 - pow(2, -23)) * pow(2, 127);
    //float scaler = 255.0/max_float;

    //printf("input float value: %f\n", u->image_data[0][0]);
    //printf("Scaler: %E\n", scaler);
    //printf("output unsigned char: %u\n", (unsigned char) (u->image_data[0][0] * scaler));
    for (int i=0; i<u->m; i++){
        for (int j=0; j<u->n; j++){
            image_chars[u->n*i + j] = (unsigned char) (u->image_data[i][j]);// * scaler);
        }
    }
}   // End convert_image_to_jpeg
