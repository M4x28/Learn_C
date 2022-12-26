//
// Created by Leonardo Birardi on 21/12/2022.
//

#include <stdio.h>

void somma(double a, double b) {
    printf("La somma di %f e %f è %f\n", a, b, a + b);
}

void sottrazione(double a, double b) {
    printf("La differenza tra %f e %f è %f\n", a, b, a - b);
}

void moltiplicazione(double a, double b) {
    printf("Il prodotto di %f e %f è %f\n", a, b, a * b);
}

void divisione(double a, double b) {
    printf("Il quoziente tra %f e %f è %f\n", a, b, a / b);
}

int main(void) {
    double a, b;
    void (*operazioni[4])(double, double) = {somma, sottrazione, moltiplicazione, divisione};
    int scelta;

    printf("Scegli un'operazione:\n");
    printf("1) Somma\n");
    printf("2) Sottrazione\n");
    printf("3) Moltiplicazione\n");
    printf("4) Divisione\n");
    scanf("%d", &scelta);

    printf("Inserisci i due valori: ");
    scanf("%lf%lf", &a, &b);

    (*operazioni[scelta - 1])(a, b);

    return 0;
}
