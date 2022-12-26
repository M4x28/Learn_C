//
// Created by Leonardo Birardi on 25/12/2022.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Prova della sequenza di escape \':\n");
    printf("Il cane disse: \"Woof!\"\n");
    printf("Prova della sequenza di escape \":\n");
    printf("Il gatto disse: 'Meow!'\n");
    printf("Prova della sequenza di escape \?:\n");
    printf("La volpe disse: 'Che cosa?'\n");
    printf("Prova della sequenza di escape \\:\n");
    printf("Il serpente disse: 'Sssssssss!'\n");
    printf("Prova della sequenza di escape \a:\n");
    printf("AAAAAAAAAAAAAAH!\a\n");
    printf("Prova della sequenza di escape \b:\nX\bX\n");
    printf("Prova della sequenza di escape \n:\n");
    printf("Prima linea\nSeconda linea\n");
    printf("Prova della sequenza di escape \r:\n");
    printf("Prima linea\rSeconda linea\n");
    printf("Prova della sequenza di escape \t:\n");
    printf("Tab\tSpazio\n");

    return 0;
}