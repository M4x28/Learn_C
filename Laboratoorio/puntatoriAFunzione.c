//
// Created by Leonardo Birardi on 23/03/2023.
//

#include <stdio.h>

int max(int a, int b);
int min(int a, int b);


int main() {
    int a, b;
    int (*op)(int, int);

    printf("Inserisci due numeri: ");
    scanf("%d %d", &a, &b);

    int choice;
    printf("Scegli l'operazione:\n");
    printf("1) Massimo\n");
    printf("2) Minimo\n");
    scanf("%d", &choice);

    if (choice == 1) {
        op = &max;
    } else if (choice == 2) {
        op = &min;
    } else {
        printf("Scelta non valida\n");
        return 1;
    }

    printf("Il risultato e': %d\n", (*op)(a, b));

    return 0;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}
