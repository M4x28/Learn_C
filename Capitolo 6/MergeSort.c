//
// Created by Leonardo Birardi on 16/12/2022.
//

/*
 * Merge sort è un algoritmo Divide et impera. Il merge sort divide un array di grandi dimensioni in due sottoarray
 * più piccoli e quindi ordina in modo ricorsivo i sottoarray.
 *
 * Fondamentalmente, due passaggi sono coinvolti nell'intero processo:
 *  1) Dividere l'array non ordinato in n sottoarray,
 *      ciascuno di dimensioni 1(un array di dimensioni 1è considerato ordinato).
 *
 *  2) Unisci ripetutamente i sottoarray per produrre nuovi sottoarray ordinati finché non rimane solo 1 sottoarray,
 *      che sarebbe il nostro array ordinato.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LUNGHEZZA_ARRAY 10


// Unione di 2 subarray riordinati `arr[low … mid]` e `arr[mid+1 … high]`
void Merge(int arr[], int aux[], int low, int mid, int high) {
    int k = low, i = low, j = mid + 1;

    // finchè ci sono elementi a dx e a sx dell'array
    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            aux[k++] = arr[i++];
        } else {
            aux[k++] = arr[j++];
        }
    }

    // copia degli elementi rimanenti
    while (i <= mid) {
        aux[k++] = arr[i++];
    }

    // Non c'è bisogno di ricopiare la seconda parte (dato che gli elementi rimanenti sono già
    // nella posizione corretta nell'array ausiliario)

    // ricopiamo l'array ausiliario in quello originale
    for (int i = low; i <= high; i++) {
        arr[i] = aux[i];
    }
}


// Riordino array `arr[low…high]` utilizzando un array ausiliario `aux`
void mergesort(int arr[], int aux[], int low, int high) {
    // caso base
    if (high <= low)
        return;         //  Espressione di ritorno nulla per le funzioni di tipo void


    // Trova il punto intermedio
    int mid = (low + ((high - low) >> 1));

    // divisione in modo ricorsivo gli array finchè size <= 1,
    // in fine uniscili tutti

    mergesort(arr, aux, low, mid);          // split/merge dx
    mergesort(arr, aux, mid + 1, high);     // split/merge sx

    Merge(arr, aux, low, mid, high);
}


// Funzione per capire se un array è ordinato in maniera asc o desc
int isSorted(int arr[]) {
    int prev = arr[0];
    for (int i = 1; i < LUNGHEZZA_ARRAY; i++) {
        if (prev > arr[i]) {
            printf("MergeSort Fails!!");
            return 0;
        }
        prev = arr[i];
    }

    return 1;
}


int main(void) {
    int arr[LUNGHEZZA_ARRAY], aux[LUNGHEZZA_ARRAY];
    srand(time(NULL));

    // Generazione di numeri casuali
    for (int i = 0; i < LUNGHEZZA_ARRAY; i++)
        aux[i] = arr[i] = (rand() % 100) - 50;

    printf("Prima dell'ordinamento: ");
    for (int i = 0; i < LUNGHEZZA_ARRAY; i++)
        printf("%d ", arr[i]);
    puts("");

    // Riordina array `arr` utilizzando l'array ausiliare `aux`
    mergesort(arr, aux, 0, LUNGHEZZA_ARRAY - 1);

    if (isSorted(arr)) {
        printf("Dopo dell'ordinamento: ");
        for (int i = 0; i < LUNGHEZZA_ARRAY; i++) {
            printf("%d ", arr[i]);
        }
    }

    return 0;
}