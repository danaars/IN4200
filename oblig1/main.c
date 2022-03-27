#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// These declarations are needed because we use .c files and not .h
void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
void top_n_webpages(int N, double *scores, int n);


int main(int argc, char *argv[]){

    char *filename = argv[1];
   
    // Allocations for the CRS formatted matrix
    int N;
    int *row_ptr;
    int *col_idx;
    double *val;

    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);

    double *scores = (double*) malloc(N * sizeof(double));

    double d = atof(argv[2]);     // d in [0, 1], usually 0.85
    double epsilon = (double) atof(argv[3]);   // Convergence threshold

    // Computes the final PageRank-score values and store them in the scores array
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);

    int n = atoi(argv[4]);

    // Find and print out the top n webpages as well as their scores
    top_n_webpages(N, scores, n);

    // Deallocate memory on the heap
    free(scores);
    free(row_ptr);
    free(col_idx);
    free(val);

return 0;
}
