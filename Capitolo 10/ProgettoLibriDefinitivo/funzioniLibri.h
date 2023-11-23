#ifndef funzioniLibri
#define funzioniLibri

#include <stdbool.h>

typedef struct
{
    char titolo[100];
    char autore[100];
    int annoPubblicazione;
} Libro;

bool inserisciLibri(Libro libri[], int nLibri);
bool ricercaLibri(Libro libri[], int nLibri);
bool stampaLibri(const Libro libri[], int nLibri);

#endif
