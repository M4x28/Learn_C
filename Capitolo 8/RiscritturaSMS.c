//
// Created by Leonardo Birardi on 25/12/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LUNGHEZZA_TESTO 1000

int main() {
    char testo[MAX_LUNGHEZZA_TESTO];
    int numeroParole = 0;

// leggi il testo
    printf("Inserisci il testo: ");
    fgets(testo, MAX_LUNGHEZZA_TESTO, stdin);

// estrai le parole dal testo usando strtok
    char *parola = strtok(testo, " \n");
    while (parola != NULL) {
        numeroParole++;
        parola = strtok(NULL, " \n");
    }

    printf("Numero di parole: %d\n", numeroParole);

    return 0;
}