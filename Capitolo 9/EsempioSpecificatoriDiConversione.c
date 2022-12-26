//
// Created by Leonardo Birardi on 25/12/2022.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    float valoreE, valoreF, valoreG;

// usa %e per leggere il valore
    printf("Inserisci il valore con lo specificatore di conversione %%e: ");
    scanf("%e", &valoreE);

// usa %f per leggere il valore
    printf("Inserisci il valore con lo specificatore di conversione %%f: ");
    scanf("%f", &valoreF);

// usa %g per leggere il valore
    printf("Inserisci il valore con lo specificatore di conversione %%g: ");
    scanf("%g", &valoreG);

    printf("Valore letto con %%e: %e\n", valoreE);
    printf("Valore letto con %%f: %f\n", valoreF);
    printf("Valore letto con %%g: %g\n", valoreG);

    return 0;
}