//
// Created by Leonardo Birardi on 16/12/2022.
//

#include <stdio.h>

void torriDiHanoi(unsigned short int n, char piolo_iniziale, char piolo_finale, char piolo_temporaneo);

int main()
{
    unsigned short int nDischi = 4;

    do {
        printf("Inserisci il numero dei dischi da spostare:");
        scanf_s("%hu", &nDischi, sizeof(nDischi));
    } while(nDischi <= 0);

    torriDiHanoi(nDischi, 'A', 'C', 'B');


    return 0;
}

void torriDiHanoi(unsigned short int n, char piolo_iniziale, char piolo_finale, char piolo_temporaneo)
{
    if (n == 1)
    {
        printf("Sposta disco 1: %c -> %c\n", piolo_iniziale, piolo_finale);
        return;
    }
    torriDiHanoi(n-1, piolo_iniziale, piolo_temporaneo, piolo_finale);
    printf("Sposta disco %d: %c -> %c\n", n, piolo_iniziale, piolo_finale);
    torriDiHanoi(n-1, piolo_temporaneo, piolo_finale, piolo_iniziale);
}