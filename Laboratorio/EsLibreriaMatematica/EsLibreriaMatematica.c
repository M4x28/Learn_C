//
// Created by Leonardo Birardi on 23/03/2023.
//

#include <stdio.h>

// Prototypes
int max(int *a, int *b);
int min(int *a, int *b);
int media(int *a, int *b);
int valoreAssoluto(int *a);

void min1(int* a, int* b, int* result);
void max2(int* a, int* b, int* result);
void media3(int* a, int* b, int* result);
void valore_assoluto4(int* a, int* result);


int main() {
    int a = -5;
    int b = 10;

    printf("Minimo tra %d e %d: %d\n", a, b, min(&a, &b));
    printf("Massimo tra %d e %d: %d\n", a, b, max(&a, &b));
    printf("Media tra %d e %d: %d\n", a, b, media(&a, &b));
    printf("Valore assoluto di %d: %d\n", a, valoreAssoluto(&a));

    a = 10, b = 20;
    int c;

    min1(&a, &b, &c);
    printf("Il minimo tra %d e %d e' %d\n", a, b, c);

    max2(&a, &b, &c);
    printf("Il massimo tra %d e %d e' %d\n", a, b, c);

    media3(&a, &b, &c);
    printf("La media tra %d e %d e' %d\n", a, b, c);

    valore_assoluto4(&a, &c);
    printf("Il valore assoluto di %d e' %d\n", a, c);

    return 0;
}


int min(int *a, int *b) {
    int result = *a < *b ? *a : *b;
    return result;
}

int max(int *a, int *b) {
    int result = *a > *b ? *a : *b;
    return result;
}

int media(int *a, int *b) {
    int result = (*a + *b) / 2;
    return result;
}

int valoreAssoluto(int *a) {
    int result = *a < 0 ? -*a : *a;
    return result;
}

void min1(int* a, int* b, int* result) {
    *result = (*a < *b) ? *a : *b;
}

void max2(int* a, int* b, int* result) {
    *result = (*a > *b) ? *a : *b;
}

void media3(int* a, int* b, int* result) {
    *result = (*a + *b) / 2;
}

void valore_assoluto4(int* a, int* result) {
    *result = (*a < 0) ? -(*a) : *a;
}