#include "funzioniLibri.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool ricercaLibri(Libro libri[], int nLibri)
{
    int annoSpecificato;
    printf("Inserisci l'anno di riferimento: ");
    scanf("%d", &annoSpecificato);

    printf("Libri pubblicati dopo il %d:\n", annoSpecificato);
    for (int i = 0; i < nLibri; i++)
    {
        if (libri[i].annoPubblicazione > annoSpecificato)
        {
            printf("%s\n", libri[i].titolo);
        }
    }
    return true;
}

bool inserisciLibri(Libro libri[], int nLibri) {

    for (int i = 0; i < nLibri; i++) {
        printf("Inserisci il titolo del libro %d: ", i + 1);
        scanf("%s", libri[i].titolo);
        printf("Inserisci l'autore del libro %d: ", i + 1);
        scanf("%s", libri[i].autore);
        printf("Inserisci l'anno di pubblicazione del libro %d: ", i + 1);
        scanf("%d", &libri[i].annoPubblicazione);
    }

    return true;
}

bool stampaLibri(const Libro libri[], int nLibri) {
    printf("Libri:\n");

    for (int i = 0; i < nLibri; i++)
    {
        printf("%s\n", libri[i].titolo);
    }
    return true;
}