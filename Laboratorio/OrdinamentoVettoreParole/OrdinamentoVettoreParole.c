//
// Created by Leonardo Birardi on 30/03/2023.
//

#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 100

// Prototipi
void acquisisci_parole(char words[][MAX_LENGTH], int *n);
void ordina_parole(char words[][MAX_LENGTH], int n);
void swap(char a[], char b[]);
void stampa_parola(char word[]);
void stampa_parole(char words[][MAX_LENGTH], int n);


int main() {
    char words[MAX_WORDS][MAX_LENGTH];
    int n;

    acquisisci_parole(words, &n);

    ordina_parole(words, n);

    stampa_parole(words, n);

    return 0;
}


void acquisisci_parole(char words[][MAX_LENGTH], int *n) {
    printf("Inserisci il numero di parole: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        printf("Inserisci la parola %d: ", i + 1);
        scanf("%s", words[i]);
    }
}

// Ordinamento stringhe
void ordina_parole(char words[][MAX_LENGTH], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(words[i], words[j]) > 0)
                swap(words[i], words[j]);
        }
    }
}

// Scambio stringhe
void swap(char a[], char b[]) {
    char temp[MAX_LENGTH];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void stampa_parole(char words[][MAX_LENGTH], int n) {
    printf("\nParole ordinate:\n");
    for (int i = 0; i < n; i++)
        stampa_parola(words[i]);
}

void stampa_parola(char word[]) {
    printf("%s\n", word);
}