#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

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

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters)
{
    image *tmp;
    for (int iter=0; iter<iters; iter++){
        for (int i=1; i<u->m-1; i++){
            for (int j=1; j<u->n-1; j++){
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa * 
                    (u->image_data[i-1][j] + u->image_data[i][j-1] - 
                     4*u->image_data[i][j] + u->image_data[i][j+1] + 
                     u->image_data[i+1][j]);
            }
        }
        // Swap pointer if not last iteration
        if (iter < iters-1){
            tmp = u_bar;
            u_bar = u;
            u = tmp; 
        }
    } 

    // Doing the borders manually
    // These are never included in the iterations loop
    // and can thus be saved untill the end.
    for (int i=0; i<u->m; i++){
        u_bar->image_data[i][0] = u->image_data[i][0];
        u_bar->image_data[i][u->n-1] = u->image_data[i][u->n-1];
    }

    for (int i=1; i<u->n-1; i++){
        u_bar->image_data[0][i] = u->image_data[0][i];
        u_bar->image_data[u->m-1][i] = u->image_data[u->m-1][i];
    }
}   // End iso_diffusion_denoising
