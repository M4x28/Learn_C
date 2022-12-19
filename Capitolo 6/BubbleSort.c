//
// Created by Leonardo Birardi on 16/12/2022.
//

/*
 * L'algoritmo di merge sort è il più semplice algoritmo di riordinamento, esso si basa sul confronto
 * tra 2 celle adiacenti e lo scorrimento di tutte le celle dell'array
 */

#include <stdio.h>

// Funzione per ordinare un array d'interi usando il metodo del bubble sort
void bubble_sort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Scambiamo gli elementi se sono in ordine sbagliato
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    int array[] = {5, 3, 8, 1, 9, 2};
    int size = sizeof(array) /
               sizeof(array[0]); // calcoliamo la dimensione dell'array (lunghezza / grandezza si ogni sinola cella)


    // Stampiamo l'array prima dell'ordinamento
    printf("Prima dell'ordinamento: ");
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    puts("");


    // Ordiniamo l'array usando il bubble sort
    bubble_sort(array, size);

    // Stampiamo l'array dopo l'ordinamento
    printf("Dopo l'ordinamento: ");
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);


    return 0;
}