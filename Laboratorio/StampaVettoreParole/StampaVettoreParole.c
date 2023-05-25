//
// Created by Leonardo Birardi on 30/03/2023.
//

#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 100

// Prototipi
void acquisisci_parole(char words[][MAX_LENGTH], int *n);
void stampa_parole_distinte(char words[][MAX_LENGTH], int n);


int main() {
    char words[MAX_WORDS][MAX_LENGTH];
    int n;

    acquisisci_parole(words, &n);

    stampa_parole_distinte(words, n);

    return 0;
}


// Acquisisci Parole
void acquisisci_parole(char words[][MAX_LENGTH], int *n) {
    printf("Inserisci il numero di parole: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        printf("Inserisci la parola %d: ", i + 1);
        scanf("%s", words[i]);
    }
}

// Stampa Parole
void stampa_parole_distinte(char words[][MAX_LENGTH], int n) {
    printf("\nParole distinte:\n");
    for (int i = 0; i < n; i++) {
        int unique = 1;
        for (int j = 0; j < i; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                unique = 0;
                break;
            }
        }
        if (unique) {
            printf("%s\n", words[i]);
        }
    }
}