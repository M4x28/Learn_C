//
// Created by Leonardo Birardi on 16/12/2022.
//


#include <stdio.h>
#include <ctype.h>

#define LUNGHEZZA_STRINGA 100


int testPalindrome(char string[], int i, int j) {
    if (i >= j) {
        return 1; // la stringa è palindroma
    }

    // Se non è un carattere
    if (!isalpha(string[i])) // ignoro gli spazi e la punteggiatura
    {
        return testPalindrome(string, i + 1, j);
    }

    if (!isalpha(string[j])) // ignoro gli spazi e la punteggiatura
    {
        return testPalindrome(string, i, j - 1);
    }

    if (tolower(string[i]) != tolower(string[j])) {
        return 0; // la stringa non è palindroma
    }

    return testPalindrome(string, i + 1, j - 1);
}

int main() {
    char string[LUNGHEZZA_STRINGA];

    printf("Inserisci la stringa da verificare: ");
    scanf("%s", string);

    if (testPalindrome(string, 0, strlen(string) - 1)) {
        printf("La stringa e' un palindromo.\n");
    } else {
        printf("La stringa non e' un palindromo.\n");
    }


    return 0;
}