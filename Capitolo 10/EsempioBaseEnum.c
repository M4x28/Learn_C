//
// Created by Leonardo Birardi on 27/12/2022.
//

#include <stdio.h>

// le costanti di enumerazione rappresentano i mesi dell'anno
enum months {
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
}; // specifico che parte da 1 il conteggio

int main(void) {
    // inizializza un array di puntatori
    const char *monthName[] = {"", "January", "February", "March",
                               "April", "May", "June", "July", "August", "September", "October",
                               "November", "December"};

    // effettua un'iterazione attraverso months
    for (enum months month = JAN; month <= DEC; ++month) {
        printf("%2d%11s\n", month, monthName[month]);
    }
}