#include <stdio.h>
#include <stdlib.h>

// These declarations are needed because we use .c files and not .h
void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
void top_n_webpages(int N, double *scores, int n);


int main(int argc, char *argv[]){

    //char *filename = "8nodes_graph.txt";
    //char *filename = "web-stanford_new.txt";
    char *filename = argv[1];
    //printf("filename: %s\n", filename);
   
    int N;
    int *row_ptr;
    int *col_idx;
    double *val;

    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);
    //printf("Outside of read func\n");

    double *scores = (double*) malloc(N * sizeof(double));

    double d = atof(argv[2]);     // d in [0, 1], usually 0.85
    double epsilon = atof(argv[3]);   // Convergence threshold

    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);

    //printf("Addr scores: %p\n", scores);
    int n = atoi(argv[4]);

    top_n_webpages(N, scores, n);

    /*
    printf("d = %1.2f gives final score values:\n", d);
    for (int i=N-1; i>N-11; i--){
        printf("scores[%d] = %1.12f\n", i, scores[i]);
    }
    printf("\n");
    for (int i=0; i<10; i++){
        printf("scores[%d] = %1.12f\n", i, scores[i]);
    }
    */
    //printf("\n");
    /*
    for (int i=0; i<N; i++){
        printf("scores[%d] = %1.12f\n", i, scores[i]);
    }
    */

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
