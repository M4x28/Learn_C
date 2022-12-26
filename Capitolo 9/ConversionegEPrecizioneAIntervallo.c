//
// Created by Leonardo Birardi on 25/12/2022.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    double valore = 9876.12345;

    for (int i = 1; i <= 9; i++) {
        printf("Stampando con precisione %d: %.*g\n", i, i, valore);
    }

    return 0;
}