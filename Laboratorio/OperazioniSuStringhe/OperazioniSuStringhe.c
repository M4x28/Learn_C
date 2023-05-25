//
// Created by Leonardo Birardi on 30/03/2023.
//

#include <stdio.h>
#include <string.h>

// Costanti
#define MAX_STRINGS 100
#define MAX_LENGTH 100

// Prototipi
void acquisisci_stringhe(char M[][MAX_LENGTH], int *n);
int contaparole(char M[MAX_STRINGS][MAX_LENGTH], int n, char *p);
void gestisci_scelta(int scelta, char M[][MAX_LENGTH], int n);
void mostra_menu();
void scambio(char M[MAX_STRINGS][MAX_LENGTH], int i, int j);
void stampa_stringhe(char M[][MAX_LENGTH], int n);
void rimpiazza(char M[MAX_STRINGS][MAX_LENGTH], int n, char *p1, char *p2);


int main() {
    char M[MAX_STRINGS][MAX_LENGTH];
    int n;

    acquisisci_stringhe(M, &n);

    int scelta;
    do {
        mostra_menu();
        printf("Inserisci la tua scelta: ");
        scanf("%d", &scelta);

        gestisci_scelta(scelta, M, n);
    } while (scelta != 5);

    return 0;
}


// Menù
void mostra_menu() {
    printf("\nMenù:\n");
    printf("1. Stampa stringhe\n");
    printf("2. Scambia prima e seconda stringa\n");
    printf("3. Conta occorrenze parola\n");
    printf("4. Sostituisci parola\n");
    printf("5. Esci\n");
}

// Acquisisci stringhe
void acquisisci_stringhe(char M[][MAX_LENGTH], int *n) {
    printf("Inserisci il numero di stringhe: ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        printf("Inserisci la stringa %d: ", i + 1);
        scanf("%s", M[i]);
    }
}

// Scambio tra la stringa memorizzata in posizione M[i] e la stringa memorizzata in posizione M[j]
void scambio(char M[MAX_STRINGS][MAX_LENGTH], int i, int j) {
    char temp[MAX_LENGTH];
    strcpy(temp, M[i]);
    strcpy(M[i], M[j]);
    strcpy(M[j], temp);
}

// Contaparole
int contaparole(char M[MAX_STRINGS][MAX_LENGTH], int n, char *p) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(M[i], p) == 0) {
            count++;
        }
    }
    return count;
}

// Rimpiazza parole
void rimpiazza(char M[MAX_STRINGS][MAX_LENGTH], int n, char *p1, char *p2) {
    for (int i = 0; i < n; i++) {
        if (strcmp(M[i], p1) == 0) {
            strcpy(M[i], p2);
        }
    }
}

void stampa_stringhe(char M[][MAX_LENGTH], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", M[i]);
    }
}

// Gestore scelta utente
void gestisci_scelta(int scelta, char M[][MAX_LENGTH], int n) {
    switch (scelta) {
        case 1:
            printf("\nStringhe inserite:\n");
            stampa_stringhe(M, n);
            break;
        case 2:
            scambio(M, 0, 1);
            printf("\nStringhe dopo lo scambio tra la prima e la seconda:\n");
            stampa_stringhe(M, n);
            break;
        case 3:
        {
            char p[MAX_LENGTH];
            printf("\nInserisci la parola da cercare: ");
            scanf("%s", p);
            int count = contaparole(M, n, p);
            printf("La parola '%s' è stata trovata %d volte.\n", p, count);
        }
            break;
        case 4:
        {
            char p1[MAX_LENGTH];
            char p2[MAX_LENGTH];
            printf("\nInserisci la parola da sostituire: ");
            scanf("%s", p1);
            printf("Inserisci la nuova parola: ");
            scanf("%s", p2);
            rimpiazza(M, n, p1, p2);
            printf("\nStringhe dopo la sostituzione di '%s' con '%s':\n", p1, p2);
            stampa_stringhe(M, n);
        }
            break;
        case 5:
            printf("Uscita dal programma.\n");
            break;
        default:
            printf("Scelta non valida. Riprova.\n");
            break;
    }
}