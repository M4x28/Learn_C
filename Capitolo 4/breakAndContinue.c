//
// Created by Leonardo Birardi on 15/12/2022.
//

#include <stdio.h>

int main(void) {
    // Break
    unsigned int x; // dichiarato qui per un utilizzo dopo il ciclo
    // ripeti 10 volte
    for (x = 1; x <= 10; ++x) {

        // se x e' 5, termina il ciclo
        if (x == 5) {
            break; // interrompi il ciclo solo se x e' 5
        }
        printf("%u ", x);
    }
    printf("\nBroke out of loop at x == %u\n", x);

    // Continue
    // ripeti 10 volte
    for (unsigned int x = 1; x <= 10; ++x) {

        // se x e' 5, continua con la successiva iterazione del ciclo
        if (x == 5) {
            continue; // salta il restante codice nel corpo del ciclo
        }

        printf("%u ", x);
    }

    puts("\nUsed continue to skip printing the value 5");
}