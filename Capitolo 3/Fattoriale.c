//
// Created by Leonardo Birardi on 09/12/2022.
//


#include <stdio.h>


int fattoriale();


int main(void) {
    unsigned int n = 0;

    while (n <= 0) {
        printf_s("Inserisci un numero di cui calcolare il fattoriale:");
        scanf_s("%d", &n, sizeof(n));
    }


    printf_s("Il fattoriale e': %d\n", fattoriale(n), sizeof(fattoriale(n)));

    return 0;
}


// Inizio fattoriale
int fattoriale(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * fattoriale(n - 1);
    }
}
// Fine fattoriale