//
// Created by Leonardo Birardi on 16/12/2022.
//

/*
 * Ricerca Binaria è un algoritmo che impiega la strategia divide et impera.
 * Confrontando il valore da cercare con l’elemento centrale, un array ORDINATO viene diviso in due metà.
 * Ma invece di lavorare su entrambi i sottoarray, l’algoritmo dal confronto deduce su quale sottoarray proseguire
 * la ricerca, scartando l’altro sottoarray.
 *
 * Prestazioni della ricerca binaria:
 *  Lo spazio ausiliario richiesto dal programma è O(1) per l'implementazione iterativa e O(log2(n)) per
 *  l'implementazione ricorsiva dovuta allo stack di chiamate.
 */


#include <stdio.h>


// Funzione di ricerca binaria implementazione iterativa
int binarySearch(int array[], int size, int value) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (array[mid] == value) {
            return mid;
        } else if (array[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}
// Fine implementazione iterativa


// Funzione di ricerca binaria implementazione ricorsiva
int binarySearchRecur(int array[], int left, int right, int value)
{
    // Se il sottoarray è vuoto, non è presente l'elemento cercato
    if (right < left)
        return -1;

    int middle = left + (right - left) / 2;

    // Se l'elemento cercato è presente al centro del sottoarray, restituisci l'indice
    if (array[middle] == value)
        return middle;

    // Altrimenti, se l'elemento cercato è più piccolo del valore al centro, cerca nella metà sinistra del sottoarray
    if (array[middle] > value)
        return binarySearchRecur(array, left, middle - 1, value);

    // Altrimenti, cerca nella metà destra del sottoarray
    return binarySearchRecur(array, middle + 1, right, value);
}
// Fine implementazione ricorsiva


int main(void) {
    int array[] = {1, 3, 4, 6, 7, 8, 10};
    int valuetoFind = 7;
    int arraySize = sizeof(array) / sizeof(array[0]);


    int indexIter = binarySearch(array, arraySize, valuetoFind);
    int indexRecur = binarySearchRecur(array, 0, arraySize--, valuetoFind);

    if (indexIter != -1) {
        printf("Il valore %d e' stato trovato all'indice %d, tramite ricerca binaria iterativa \n", valuetoFind, indexIter);
    } else {
        printf("Il valore %d non e' stato trovato nell'array\n", valuetoFind);
    }

    if (indexRecur != -1) {
        printf("Il valore %d e' stato trovato all'indice %d, tramite ricerca binaria ricorsiva \n", valuetoFind, indexRecur);
    } else {
        printf("Il valore %d non e' stato trovato nell'array\n", valuetoFind);
    }

    return 0;
}
