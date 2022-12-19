// C program for implementation of Bubble sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define ARR_LEN 100000


void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

/* Function to print an array */
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program to test above functions
int main(void) {
    clock_t start_t, end_t;
    double total_t;

    srand(time(NULL));
    int arr[ARR_LEN] = {0};
    for (unsigned int j = 0; j < ARR_LEN; j++) arr[j] = rand();

    int n = sizeof(arr) / sizeof(arr[0]);

    start_t = clock();
    bubbleSort(arr, n);
    end_t = clock();

    total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f for %d numbers\n", total_t, ARR_LEN);


    return 0;
}

