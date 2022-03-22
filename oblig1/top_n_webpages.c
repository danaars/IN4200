#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//void merge(double *arr, int l, int m, int r);
//void mergesort(double * arr, int l, int r);

void top_n_webpages(int N, double *scores, int n){

    double top_scores[n];
    int top_nodes[n];

    double max;
    double last_max = 99.9;
    int idx;

    if (n > N){
        n = N;
    }

    for (int i=0; i<n; i++){
        max = 0.0;
        //#pragma omp parallel for reduction(max: max)
        for (int j=0; j<N; j++){
            if (scores[j] > max && scores[j] < last_max){
                max = scores[j];
                idx = j;
            }
        } 
        last_max = max;

        top_scores[i] = max;
        top_nodes[i] = idx;
    }

    printf("Top %d webpages:\n", n);
    printf("Node:\tScore:\n");
    for (int i=0; i<n; i++){
        printf("%d \t %1.6f \n", top_nodes[i], top_scores[i]);
    }
}

// Not used
//void merge(double *arr, int l, int m, int r)   // Copied from https://www.geeksforgeeks.org/merge-sort/
//{
//    int i, j, k;
//    int n1 = m - l + 1;
//    int n2 = r - m;
//
//    /* create temp arrays */
//    double L[n1], R[n2];
//
//    /* Copy data to temp arrays L[] and R[] */
//    for (i = 0; i < n1; i++)
//        L[i] = arr[l + i];
//
//    for (j = 0; j < n2; j++)
//        R[j] = arr[m + 1 + j];
//
//    /* Merge the temp arrays back into arr[l..r]*/
//    i = 0; // Initial index of first subarray
//    j = 0; // Initial index of second subarray
//    k = l; // Initial index of merged subarray
//    while (i < n1 && j < n2) {
//        if (L[i] <= R[j]) {
//            arr[k] = L[i];
//            i++;
//        }
//        else {
//            arr[k] = R[j];
//            j++;
//        }
//        k++;
//    }
//
//    /* Copy the remaining elements of L[], if there
//    are any */
//    while (i < n1) {
//        arr[k] = L[i];
//        i++;
//        k++;
//    }
//
//    /* Copy the remaining elements of R[], if there
//    are any */
//    while (j < n2) {
//        arr[k] = R[j];
//        j++;
//        k++;
//    }
//}
//
//void mergesort(double *arr, int l, int r)     // Copied from https://www.geeksforgeeks.org/merge-sort/
//{
//    if (l < r) {
//        // Same as (l+r)/2, but avoids overflow for
//        // large l and h
//        int m = l + (r - l) / 2;
//  
//        // Sort first and second halves
//        mergesort(arr, l, m);
//        mergesort(arr, m + 1, r);
//  
//        merge(arr, l, m, r);
//    }
//}
