#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

struct custom_max {
    double val;
    int idx;
};

// Custom omp declariation to be used later
#pragma omp declare reduction(new_max : struct custom_max : omp_out = omp_in.val > omp_out.val ? omp_in : omp_out)
void top_n_webpages(int N, double *scores, int n){

    struct custom_max top[n];

    struct custom_max max;
    double last_max = 99.9;

    if (n > N){
        n = N;
    }

    // Find and store the n top score pages
    for (int i=0; i<n; i++){
        max.val = 0.0;
        #pragma omp parallel for reduction(new_max: max)
        for (int j=0; j<N; j++){
            if (scores[j] > max.val && scores[j] < last_max){
                max.val = scores[j];
                max.idx = j;
            }
        } 
        last_max = max.val;

        top[i] = max;
    }

    // Display final result
    printf("Top %d webpages:\n", n);
    printf("Rank:\tPage:\tScore:\n");

    for (int i=0; i<n; i++){
        printf("%2d \t %6d \t %1.6f \n", i+1, top[i].idx, top[i].val);
    }
}
