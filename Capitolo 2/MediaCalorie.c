//
// Created by Leonardo Birardi on 13/03/2023.
//

#include <stdio.h>

#define RIGHE 7
#define COLONNE 5

float media(float v[], int n);

int main() {
    float calorie[RIGHE][COLONNE] = {
            {1200, 1300, 1400, 1500, 1600},
            {1100, 1200, 1300, 1400, 1500},
            {1300, 1400, 1500, 1600, 1700},
            {1400, 1500, 1600, 1700, 1800},
            {1500, 1600, 1700, 1800, 1900},
            {1300, 1400, 1500, 1600, 1700},
            {1200, 1300, 1400, 1500, 1600}
    };

    float medieSoggetti[RIGHE];
    for (int i = 0; i < RIGHE; i++) {
        medieSoggetti[i] = media(calorie[i], COLONNE);
    }

    float mediaTotale = media(medieSoggetti, RIGHE);

    printf("Le medie dei soggetti sono:\n");
    for (int i = 0; i < RIGHE; i++) {
        printf("Soggetto %d: %.2f\n", i+1, medieSoggetti[i]);
    }

    printf("La media totale e': %.2f\n", mediaTotale);

    return 0;
}


// Funzione per calcolare la media di un vettore di lunghezza n
float media(float v[], int n) {
    float somma = 0.0;
    for (int i = 0; i < n; i++) {
        somma += v[i];
    }
    return somma / n;
}