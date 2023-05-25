//
// Created by Leonardo Birardi on 13/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RIGHE 5
#define COLONNE 7

float media(float v[], int n);
void popola_valori_singolo_individuo(float v[], int n);
void popola_valori_singolo_individuo_input(float v[], int n);
void stampArray(float v[], int n);
void stampaMatrice(float matrice[][COLONNE], int righe);


int main() {
    float calorie[RIGHE][COLONNE];
    float medieSoggetti[RIGHE];

    // Popola la matrice con valori generati casualmente
    for (int i = 0; i < RIGHE; i++)
        popola_valori_singolo_individuo(calorie[i], COLONNE);

    stampaMatrice(calorie, RIGHE);

    // Calcola le medie dei soggetti e la media totale
    for (int i = 0; i < RIGHE; i++)
        medieSoggetti[i] = media(calorie[i], COLONNE);

    float mediaTotale = media(medieSoggetti, RIGHE);

    // Stampa i risultati
    for (int i = 0; i < RIGHE; i++) {
        printf("Soggetto %d: ", i+1);
        stampArray(calorie[i], COLONNE);
    }

    // Stampare le medie solo una volta passando l'array medieSoggetti
    printf("Le medie dei soggetti sono: ");
    stampArray(medieSoggetti, RIGHE);

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

// Funzione per popolare i valori di un singolo individuo con numeri casuali
void popola_valori_singolo_individuo(float v[], int n) {
    srand(time(NULL)); // Inizializza il generatore di numeri casuali con il tempo corrente
    for (int i = 0; i < n; i++)
        v[i] = rand() % 1000 + 1000; // Genera un numero casuale tra 1000 e 1999
}

// Funzione per popolare i valori di un singolo individuo con input da tastiera
void popola_valori_singolo_individuo_input(float v[], int n) {
    printf("Inserisci i valori di consumo calorico per questo soggetto:\n");
    for (int i = 0; i < n; i++)
        scanf("%f", &v[i]);
}

void stampArray(float v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%.2f ", v[i]);
    printf("\n");
}

void stampaMatrice(float matrice[][COLONNE], int righe) {
    printf("La matrice e':\n");
    for (int i = 0; i < righe; i++) {
        printf("Soggetto %d: ", i+1);
        stampArray(matrice[i], COLONNE);
    }
}