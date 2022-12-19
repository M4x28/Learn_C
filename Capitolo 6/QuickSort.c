//
// Created by Leonardo Birardi on 16/12/2022.
//

/*
 * Quicksort è un efficiente algoritmo che solitamente funziona da due a tre volte più velocemente del
 * merge sort e heapsort se implementato correttamente.
 *
 *  Quicksort è un ordinamento di confronto, il che significa che può ordinare elementi di qualsiasi tipo per i quali è
 *  definita una relazione minore di x.
 *  Nelle implementazioni efficienti, di solito non è un tipo stabile.
 *
 *  Quicksort, in media, effettua O(n.log(n)) confronti per ordinare N elementi.
 *   Nel peggiore dei casi, effettua O(n^2) confronti.
 *
 *   Quicksort è un algoritmo divide et impera. Dunque prima divide un array di grandi dimensioni in due sottoarray
 *    più piccoli e quindi ordina in modo ricorsivo i sottoarray.
 *
 *    Fondamentalmente, tre passaggi sono coinvolti nell'intero processo:
 *      1) Selezione pivot: scegli un elemento, chiamato pivot, dall'array
 *          (di solito l'elemento più a sinistra o più a destra della partizione).
 *
 *      2) Partizionamento: riordina l'array in modo tale che tutti gli elementi con valori inferiori al pivot
 *          vengano prima del pivot. Al contrario, tutti gli elementi con valori maggiori del pivot vengono dopo di esso
 *          I valori uguali possono andare in entrambi i modi. Dopo questo partizionamento,
 *          il perno è nella sua posizione finale.
 *
 *      3) Recur: applica in modo ricorsivo i passaggi precedenti al sottoarray di elementi con valori inferiori
 *          rispetto al pivot e separatamente al sottoarray di elementi con valori maggiori rispetto al pivot.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LUNGHEZZA_ARRAY 10


void quicksort(int array[], int left, int right) {
    int pivot, i, j;
    if (left < right) {
        pivot = array[left];
        i = left;
        j = right;
        while (i < j) {
            while (array[j] > pivot) {
                j--;
            }
            while (i < j && array[i] <= pivot) {
                i++;
            }
            if (i < j) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        array[left] = array[j];
        array[j] = pivot;
        quicksort(array, left, j - 1);
        quicksort(array, j + 1, right);
    }
}

int main() {
    int array[LUNGHEZZA_ARRAY];
    srand(time(NULL));

    // Generazione di numeri casuali
    for (int i = 0; i < LUNGHEZZA_ARRAY; i++)
        array[i] = (rand() % 100) - 50;

    printf("Prima dell'ordinamento: ");
    for (int i = 0; i < LUNGHEZZA_ARRAY; i++)
        printf("%d ", array[i]);
    puts("");

    // Richiamo la funzione di riordinamento
    quicksort(array, 0, LUNGHEZZA_ARRAY - 1);

    printf("Dopo dell'ordinamento: ");
    for (int i = 0; i < LUNGHEZZA_ARRAY; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
