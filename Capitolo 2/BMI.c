//
// Created by Leonardo Birardi on 09/12/2022.
//


#include <stdio.h>


void stampaInfo();


int main(void) {
    float massaInKg, altezzaInM, bmi;

    printf("Inserisci il tuo peso in kg:");
    scanf("%f", &massaInKg);
    printf("Inserisci la tua altezza in m:");
    scanf("%f", &altezzaInM);

    bmi = massaInKg / (altezzaInM * altezzaInM);
    printf("Il tuo BMI e' di: %.1f\n\n", bmi);
    stampaInfo();

    return 0;
}


void stampaInfo() {
    puts("VALORI del BMI");
    puts("Sottopeso: meno di 18.5");
    puts("Normale: tra 18.5 e 24.9");
    puts("Sovrappeso: tra 25 e 29.9");
    puts("Obeso: 30 o oltre");
}