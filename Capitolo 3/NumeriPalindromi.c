//
// Created by Leonardo Birardi on 10/12/2022.
//
// Palindromi di 5 cifre
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LEN_N 5


// Con funzione
bool palindromo(int n)
{
    // Conversione del numero in una stringa
    char str[MAX_LEN_N];


    /*
     * sprintf è una funzione che scrive su stringa, in questo modo possiamo convertire numero di qualsiasi formato, in array di caratteri.
     * sscanf è una funzione che legge da array
     * !!! LA funzione con _s è la riscrittura da parte Microsoft per la gestione di errori di overflow, per effettuare il controllo ha bisogno che come parametro gli
     * venge passato anche la lunghezza dell'array, in caso di errore la funzione imposta il valore dell'array a -1
     * (unsigned)_countof(array) è una funzione che ritorna la lunghezza del buffer -1 perchè prende in considerazione anche il carattere tappo/di terminazione
    */

    sprintf_s(str, (unsigned)_countof(str), "%d", n);

    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }

    return true;
}


int main(void) {
    unsigned int primaC, secondaC, quartaC, quintaC, old, n = 13231;

    while(n > 99999 || n < 10000) {
        printf_s("Inserisci un numero a 5 cifre:");
        scanf_s("%d", &n, sizeof(n));
    }

    // 1a cifra da sx
    primaC = (n - (n % 10000)) / 10000;

    // 2a cifra da sx
    secondaC = ((n - (n % 1000)) / 1000) - primaC * 10;

    // 3a cifra da sx
    old = ((n - (n % 100)) / 100);

    // 4a cifra da sx
    quartaC = ((n - (n % 10)) / 10) - old * 10;
    old = ((n - (n % 10)) / 10);

    // 5a cifra da sx
    quintaC = n - old * 10;

    if (primaC == quintaC && secondaC == quartaC) printf_s("Il numero e' palindromo.");
    else printf_s("Il numero non e' palindromo.");

    return 0;
}
