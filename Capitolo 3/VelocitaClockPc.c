//
// Created by Leonardo Birardi  on 10/12/2022.
//
#include <stdio.h>
#include <math.h>
#include <time.h>


int main(void) {
    unsigned int i = 0.0;

    // Inizio timer
    clock_t start = clock();

    while (i < pow(10, 9)) {
        if (i % (int) pow(10, 8) == 0) printf_s("%d\n", i);
        i++;
    }

    // Finisco timer
    clock_t end = clock();
    double elapsed = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Tempo impiegato per 10 interazioni in CPU: %.4f s\n", elapsed);

    return 0;
}
