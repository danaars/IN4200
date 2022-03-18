#include <stdio.h>
#include <stdlib.h>

//#include "read_graph_from_file.c"
//#include "PageRank_iterations.c"

// These declarations are needed because we use .c files and not .h
void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);
//void crs_mat_vec_mult(int N, int *row_ptr, int *col_idx, double *val, double *x, double *prod);
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);

int main(int argc, char *argv[]){

    char *filename = "8nodes_graph.txt";
   
    int N;
    int *row_ptr;
    int *col_idx;
    double *val;

    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);

    double *scores = (double*) malloc(N * sizeof(double));

    double d = 0.85;     // d in [0, 1], usually 0.85
    double epsilon = 1E-6;

    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);

    printf("d = %1.2f gives final score values:\n", d);
    for (int i=0; i<N; i++){
        printf("%f\n", scores[i]);
    }
    //printf("\n");

    free(scores);

    /*
    printf("Output crs matrix and vector multiplication:\n");
    for (int j=0; j<max_iter; j++){
        crs_mat_vec_mult(N, row_ptr, col_idx, val, x, prod);
    
        printf("Iteration: %d:\n", j+1);
        for (int i=0; i<N; i++){
            printf("%8.4f", prod[i]);
        }
        printf("\n");
        //printf("x address: \t\t%p\n", x);
        //printf("tmp address: \t\t%p\n", tmp);
        tmp = x;
        //printf("new tmp address: \t%p\n", tmp);
        //printf("prod address: \t\t%p\n", prod);
        x = prod;
        //printf("new x address: \t\t%p\n", x);
        prod = tmp;
        //printf("new prod address: \t%p\n", prod);
    }
    */

    free(row_ptr);
    free(col_idx);
    free(val);
    //free(prod);
    //printf("FML bro, helt ærlig hvor faen er feilen\n");
    //printf("åÅåÅåÅåÅåÅåÅåÅåÅåÅåÅåÅåÅåÅåÅåÅåÅåÅåÅåÅå\n");

return 0;
}
