//
// Created by Leonardo Birardi on 27/12/2022.
//

#include <stdio.h>


int main(void) {

    FILE *cfPtr; // cfPtr = puntatore al file clients.txt

    // fopen apre il file per la lettura
    if ((cfPtr = fopen("clients.txt", "r")) == NULL) {
        puts("File could not be opened");
    } else { // leggi account, name e balance dal file

        unsigned int account; // numero del conto
        char name[30]; // nome del titolare del conto
        double balance; // saldo del conto

        printf("%-10s%-13s%s\n", "Account", "Name", "Balance");
        fscanf(cfPtr, "%d%29s%lf", &account, name, &balance);

        // finché non si incontra un end of file
        while (!feof(cfPtr)) {
            printf("%-10d%-13s%7.2f\n", account, name, balance);
            fscanf(cfPtr, "%d%29s%lf", &account, name, &balance);
        }

        fclose(cfPtr); // fclose chiude il file
    }
}