//
// Created by Leonardo Birardi on 22/12/2022.
//

#include <stdio.h>
#include <math.h>

void circonferenza(double r) {
    printf("La circonferenza di un cerchio con raggio %f e' %f\n", r, 2 * M_PI * r);
}

void area(double r) {
    printf("L'area di un cerchio con raggio %f e' %f\n", r, M_PI * r * r);
}

void volume(double r) {
    printf("Il volume di una sfera con raggio %f e' %f\n", r, (4.0 / 3.0) * M_PI * r * r * r);
}

int main(void) {
    double r;
    void (*operazioni[3])(double) = {circonferenza, area, volume};
    int scelta;

    printf("Scegli un'operazione:\n");
    printf("1) Calcola la circonferenza di un cerchio\n");
    printf("2) Calcola l'area di un cerchio\n");
    printf("3) Calcola il volume di una sfera\n");
    scanf("%d", &scelta);

    printf("Inserisci il valore del raggio: ");
    scanf("%lf", &r);

    (*operazioni[scelta - 1])(r);

    return 0;
}