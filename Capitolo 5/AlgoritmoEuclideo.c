//
// Created by Leonardo Birardi on 16/12/2022.
//

#include <stdio.h>

// Funzione ricorsiva per il calcolo dell'MCD di 2 numeri
// Algoritmo ottimizzato utilizzando il resto della divisione di a e b
unsigned short int euclid(unsigned short int a, unsigned short int b)
{
    // se il resto è uguale a 0 ritorna a
    if (b == 0) {
        return a;
    }

    int q = a / b;  // quoziente
    int r = a % b;  // resto


    // a diventa b e b diventa r
    return euclid(b, r);
}

int main()
{
    unsigned short int a = 2740, b = 1760;

    printf("Insericsi i 2 numeri di cui calcolare MCD:");
    scanf_s("%hu %hu", &a, &b, sizeof(a), sizeof(b));

    printf_s("Euclide(%hu, %hu) = %hu", a, b, euclid(a, b), sizeof(a), sizeof(b), sizeof(euclid(a, b)));

    return 0;
}
