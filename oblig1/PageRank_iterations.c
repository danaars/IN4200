#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void crs_mat_vec_mult(int N, int *row_ptr, int *col_idx, double *val, double *x, double *prod);
double dangling(int num_idx, int *dang_idx, double *prev_x);
void get_dang_idx(int N, int edges, int *num_idx, int *dang_idx, int *col_idx);

void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val,
        double d, double epsilon, double *scores){

    double *Ax = (double*) malloc(N * sizeof(double));       // Initial guess

    #pragma omp parallel for
    for (int i=0; i<N; i++)
        Ax[i] = 1.0/N;

    double prev_x[N];
    double *tmp;
    double dist;
    double maxdist = 2*epsilon;
    int num_idx;
    int dang_idx[N];
    double W, damp;

    // Stores the indicies of the dangling columns
    get_dang_idx(N, row_ptr[N], &num_idx, dang_idx, col_idx);  // row_ptr[N] = edges

    #pragma omp parallel for
    for (int i=0; i<N; i++){
        prev_x[i] = Ax[i];
    }

    int iter = 0;
    while (maxdist > epsilon){      // Main iteration loop
        maxdist = 0.0;

        crs_mat_vec_mult(N, row_ptr, col_idx, val, prev_x, Ax);  // Matrix vector multiplication

        W = dangling(num_idx, dang_idx, prev_x);
        damp = (1.0 - d + d * W)/N;

        #pragma omp parallel for reduction(max: dist)
        for (int i=0; i<N; i++){        // Calculate next iter x array
            scores[i] = damp + d * Ax[i];

            dist = scores[i] - prev_x[i];
            dist = (dist > 0.0) ? dist:-dist;

            if (dist > maxdist){
                maxdist = dist;
            }

            prev_x[i] = scores[i];
        }   // End for loop
        iter+=1;
    }   // End while loop

    free(Ax);

    printf("Number of PageRank iterations: %d\n", iter);
}

void crs_mat_vec_mult(int N, int *row_ptr, int *col_idx, double *val, double *x, double *prod){

    #pragma omp parallel for
    for (int i=0; i<N; i++){
        prod[i] = 0.0;
        for (int j= row_ptr[i]; j<row_ptr[i+1]; j++){
            prod[i] += val[j] * x[col_idx[j]];
        }
    }
}

double dangling(int num_idx, int *dang_idx, double *prev_x){

    double W = 0.0;
    #pragma omp parallel for reduction(+: W)
    for (int i=0; i<num_idx; i++){
        W += prev_x[ dang_idx[i] ];
    }

    return W;
}

void get_dang_idx(int N, int edges, int *num_idx, int *dang_idx, int *col_idx){
    
    int counter[N];
    #pragma omp parallel for
    for (int i=0; i<N; i++)
        counter[i] = 0; 

    #pragma omp parallel for
    for (int i=0; i<edges; i++){
        counter[ col_idx[i] ] += 1;
    }

    *num_idx = 0;
    #pragma omp parallel for
    for (int i=0; i<N; i++){
        dang_idx[i] = 0;
        if (counter[i] == 0){
            *num_idx += 1;
        }
    }

    int idx = 0;
    #pragma omp parallel for
    for (int i=0; i<N; i++){
        if (counter[i] == 0){
            dang_idx[idx] = i;
            idx += 1;
        }
    }
}
