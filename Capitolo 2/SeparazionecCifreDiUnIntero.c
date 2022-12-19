//
// Created by Leonardo Birardi on 09/12/2022.
//


#include <stdio.h>


int main(void) {
    int n = 42139;
    int old, temp;

    printf("Inserisci un numero a 5 cifre: ");
    scanf("%d", &n);

    if (n > 99999) {
        printf("Numero non valido");
        exit(0);
    }


    old = (n - (n % 10000)) / 10000;
    printf("%d   ", old);
    temp = ((n - (n % 1000)) / 1000) - old * 10;
    old = ((n - (n % 1000)) / 1000);
    printf("%d   ", temp);
    temp = ((n - (n % 100)) / 100) - old * 10;
    old = ((n - (n % 100)) / 100);
    printf("%d   ", temp);
    temp = ((n - (n % 10)) / 10) - old * 10;
    old = ((n - (n % 10)) / 10);
    printf("%d   ", temp);
    temp = n - old * 10;
    printf("%d", temp);

    return 0;

}