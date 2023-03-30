//
// Created by Leonardo Birardi on 30/03/2023.
//

#include <stdio.h>
#include <string.h>

int conta_parole(char frase[]);

int main() {
    char frase[100];

    printf("Inserisci una frase: ");
    fgets(frase, 100, stdin);
    printf("La frase contiene %d parole.\n", conta_parole(frase));

    return 0;
}

int conta_parole(char frase[]) {
    int parole = 0;
    char *token = strtok(frase, " ");
    while (token != NULL) {
        parole++;
        token = strtok(NULL, " ");
    }
    return parole;
}