#include <stdio.h>
#include <stdlib.h>

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val){
    FILE *fp = fopen(filename, "r");

    if (fp == NULL){
        printf("Error: file not found\n");
        exit(1);
    }

    char buff[255];
    fgets(buff, 255, fp);       // Skip first two lines
    fgets(buff, 255, fp);

    int edges;
    
    fscanf(fp, "# Nodes: %d Edges: %d\n", N, &edges);   // Get nodes and edges
    fgets(buff, 255, fp);

    *row_ptr = (int*) calloc((*N + 1), sizeof(int));    // Allocate memory, initialized to zero
    *col_idx = (int*) calloc(edges, sizeof(int));
    *val = (double*) calloc(edges, sizeof(double));

    int from, to;
    int out_counter[edges];  // L(j)

    for (int i=0; i<edges; i++){
        out_counter[i] = 0;
    }

    int fromnode[edges];
    int tonode[edges];

    for (int i=0; i<edges; i++){    
        fscanf(fp, "%d %d\n", &from, &to);      // Read from and to values

        (*row_ptr)[to+1] += 1;
        out_counter[from] += 1;

        fromnode[i] = from;         // Store values
        tonode[i] = to;
    }
    
    int tot = 0;
    int counter[*N+1];

    for (int i=0; i<*N+1; i++){     // Make row_ptr array cumulative
        tot += (*row_ptr)[i];
        (*row_ptr)[i] = tot;

        counter[i] = 0;     // Initialize necessary zero-values
    }

    int idx;
    for (int i=0; i<edges; i++){   // Calculate col_idx and val array
        /*
        printf("tonode[%d] = %d\n", i, tonode[i]);
        printf("counter[%d] = %d\n", tonode[i], counter[tonode[i]]);
        printf("row_ptr[%d] = %d\n", tonode[i], (*row_ptr)[tonode[i]]);
        printf("row_ptr[%d] + counter[%d] = %d\n", tonode[i], tonode[i], 
                (*row_ptr)[tonode[i]] + counter[tonode[i]]);
        printf("col_idx[%d] = %d\n", (*row_ptr)[tonode[i]] + counter[tonode[i]], fromnode[i]);
        */
        /*
        if (counter[tonode[i]] != 0){
            printf("Attempted index: %d out of %d\n", tonode[i], *N+1);
            printf("For loop iteration: %d\n", i);
            printf("counter[%d] = %d\n", tonode[i], counter[tonode[i]]);
            printf("Massive Error dickhead, counter not initialized properly\n");
            exit(1);
        }
        */
        idx = (*row_ptr)[tonode[i]] + counter[tonode[i]];
        (*col_idx)[idx] = fromnode[i];
        counter[tonode[i]] += 1;
        //printf("out_counter[%d] = %d\n", fromnode[i], out_counter[fromnode[i]]);
        //printf("out_counter[fromnode[%d]] = %d\n", i, out_counter[fromnode[i]]);
        (*val)[idx] = 1.0/(out_counter[fromnode[i]]);
    }

    /*
    printf("From\tTo\n");
    for (int i=0; i<edges; i++){
        printf("%4d %8d\n", fromnode[i], tonode[i]);
    }

    printf("idx\tin_counter\tout_counter\n");
    for (int i=0; i<*N; i++){
        printf("%4d %8d %8d\n", i, in_counter[i], out_counter[i]);
    }
    */
    

    //printf("\n");
    //printf("L(j):\n");
    //for (int i=0; i<*N; i++){
        //printf("%5d", out_counter[i]);
    //}

   //printf("\n"); 
}   // End: read_graph_from_file function

// Main-function for testing purposes only

/*
int main(int argc, char *argv[]){
    int N;
    int *row_ptr;
    int *col_idx;
    double *val;
    char *filename = "simple-webgraph.txt";
    */
    /*
    FILE *fp = fopen(filename, "r");

    if (fp == NULL){
        printf("Error: Could not open %s\n", filename);
        return 1;
    }

    const unsigned MAX = 256;
    int nolines = 254;
    char data[nolines][MAX];
    int ind = 0;
    while (fgets(data[ind], MAX, fp)){
        ind += 1;
    }

    fclose(fp);
    */

    /*
    int rownumbs = 100;
    for (int i=0; i<rownumbs; i++){
        string 
    }<++>
    */
    //printf("Main read-loop finished\n");
    //printf("Manual print:\n");

    // Fixed row in matrix
    //for (int row = 0; row<nolines; row++){
        //for (int col=0; col<MAX; col++){
            //printf("%s", data[row]);
        //}
    //}
    //printf("%s", data[nolines-1]);
    /*
    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);

    int edges = row_ptr[N];
    
    printf("row_ptr=\n");
    for (int i=0; i<N+1; i++){
        printf("%5d", row_ptr[i]);
    }
    printf("\n");

    printf("col_idx=\n");
    for (int i=0; i<edges; i++){
        printf("%5d", col_idx[i]);
    }
    printf("\n");

    printf("val=\n");
    for (int i=0; i<edges; i++){
        printf("%8.3f", val[i]);
    }
    printf("\n");

    free(row_ptr);      // Free allocated memory
    free(col_idx);
    free(val);

return 0;
}
*/
