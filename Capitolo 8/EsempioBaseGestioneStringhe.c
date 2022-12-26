//
// Created by Leonardo Birardi on 25/12/2022.
//

#include <stdio.h>
#include <string.h>

int main() {
// gets
    char nome[50];
    printf("Inserisci il tuo nome: ");
    gets(nome);
    printf("Il tuo nome e': %s\n", nome);

// sprintf
    char buffer[50];
    int numero = 10;
    sprintf(buffer, "Il numero e': %d", numero);
    printf("%s\n", buffer);

// sscanf
    int num;
    sscanf(buffer, "Il numero e': %d", &num);
    printf("Il numero estratto e': %d\n", num);

// strtok
    char frase[50] = "Ciao, come va?";
    char *parola = strtok(frase, " ");
    while (parola != NULL) {
        printf("Parola: %s\n", parola);
        parola = strtok(NULL, " ");
    }

// strlen
    printf("La lunghezza della frase è: %lu\n", strlen(frase));

// memcpy
    char sorgente[] = "Sorgente";
    char destinazione[50];
    memcpy(destinazione, sorgente, sizeof(sorgente));
    printf("Destinazione: %s\n", destinazione);

// memmove
    char sorgente2[] = "Sorgente2";
    memmove(destinazione + 2, sorgente2, sizeof(sorgente2));
    printf("Destinazione: %s\n", destinazione);

// memchr
    char *risultato = memchr(destinazione, 'S', sizeof(destinazione));
    if (risultato != NULL) {
        printf("Trovato carattere 'S' in posizione: %d\n", risultato - destinazione);
    } else {
        printf("Carattere 'S' non trovato\n");
    }

// memcmp
    char sorgente3[] = "Sorgente3";
    if (memcmp(sorgente3, destinazione, sizeof(sorgente3)) == 0) {
        printf("Le due stringhe sono uguali\n");
    } else {
        printf("Le due stringhe sono diverse\n");
    }

// memset
    memset(destinazione, '-', 5);
    printf("Destinazione: %s\n", destinazione);

    return 0;
}