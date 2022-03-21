#include <stdio.h>
#include <stdlib.h>

//#include "read_graph_from_file.c"
void crs_mat_vec_mult(int N, int *row_ptr, int *col_idx, double *val, double *x, double *prod);
//void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
double dangling(int num_idx, int *dang_idx, double *prev_x);
void get_dang_idx(int N, int edges, int *num_idx, int *dang_idx, int *col_idx);

void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val,
        double d, long double epsilon, double *scores){

    double *x = (double*) malloc(N * sizeof(double));       // Initial guess

    for (int i=0; i<N; i++)
        x[i] = 1.0/N;

    double prev_x[N];
    double *tmp;
    double dist;
    long double maxdist = 2*epsilon;
    int num_idx;
    int dang_idx[N];
    double W;

    get_dang_idx(N, row_ptr[N], &num_idx, dang_idx, col_idx);  // row_ptr[N] = edges

    //printf("---Initial guess:\n");
    for (int i=0; i<N; i++){
        prev_x[i] = x[i];
        //printf("%12.6f", x[i]);
    }
    //printf("\n");

    int iter = 0;
    while (maxdist > epsilon){
    //while (iter < 5){
        maxdist = 0.0;

        crs_mat_vec_mult(N, row_ptr, col_idx, val, prev_x, scores);  // Matrix vector multiplication

        W = dangling(num_idx, dang_idx, prev_x);
        //printf("W = %f\n", W);
        //exit(1);
        //printf("---After iteration %d:\n", iter + 1);
        for (int i=0; i<N; i++){        // Calculate next iter x array
            x[i] = (1.0 - d + d * W)/N + d * scores[i];

            //printf("%12.6f", x[i]);

            dist = x[i] - prev_x[i];
            dist = (dist > 0.0) ? dist:-dist;
            if (dist > maxdist)
                maxdist = dist;

            prev_x[i] = x[i];
        }
        //printf("\n");
        //printf("Addr scores: %p\n", scores);

        //printf("maxdist: %.12f\n", maxdist);
        
        tmp = scores;
        scores = x;

        //printf("Addr scores etter bytte: %p\n", scores);
        x = tmp;
        iter+=1;
    }
    if (iter % 2 != 0){
        scores = tmp;
    } else {
        free(x);
    }
    //free(dang_idx);
    /*
    for (int i=0; i<N; i++){
        printf("%1.12f\n", prev_x[i]);
    }
    */
    //printf("\n");

    //printf("Siste internal score addr: %p\n", scores);
    printf("Number of PageRank iterations: %d\n", iter);
}

void crs_mat_vec_mult(int N, int *row_ptr, int *col_idx, double *val, double *x, double *prod){
    //*prod = (double*) calloc(N, sizeof(double));
    for (int i=0; i<N; i++){
        prod[i] = 0.0;
        for (int j= row_ptr[i]; j<row_ptr[i+1]; j++){
            prod[i] += val[j] * x[col_idx[j]];
        }
    }
}

double dangling(int num_idx, int *dang_idx, double *prev_x){

    double W = 0.0;
    for (int i=0; i<num_idx; i++){
        W += prev_x[ dang_idx[i] ];
        //printf("W_%d = %f\n", i, prev_x[dang_idx[i]]);
    }

    return W;
}

void get_dang_idx(int N, int edges, int *num_idx, int *dang_idx, int *col_idx){
    
    int counter[N];
    for (int i=0; i<N; i++)
        counter[i] = 0; 

    for (int i=0; i<edges; i++){
        counter[ col_idx[i] ] += 1;
        //printf("col_idx[%d] = %d \t counter[%d] = %d\n", i, col_idx[i], col_idx[i], counter[col_idx[i]]);
    }

    *num_idx = 0;
    for (int i=0; i<N; i++){
        dang_idx[i] = 0;
        if (counter[i] == 0){
            *num_idx += 1;
        }
    }
    
    //printf("number of indicies: %d\n",*num_idx);
    //int *dang_idx = (int*) malloc(*num_idx * sizeof(int));


    int idx = 0;
    for (int i=0; i<N; i++){
        if (counter[i] == 0){
            //printf("counter[%d] = %d bool equals 0\n", i, counter[i]);
            dang_idx[idx] = i;
            //printf("index stored: %d\n", i);
            idx += 1;

        }
    }

    //return dang_idx;
}
