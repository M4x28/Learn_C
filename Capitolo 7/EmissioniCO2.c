//
// Created by Leonardo Birardi on 22/12/2022.
//

#include <stdio.h>


void edificio() {
    double metri_quadri, consumo_energetico, emissione_co2;

    printf("Inserisci la superficie dell'edificio (in metri quadri): ");
    scanf("%lf", &metri_quadri);
    printf("Inserisci il consumo energetico dell'edificio (in KWh): ");
    scanf("%lf", &consumo_energetico);

    emissione_co2 = consumo_energetico * 0.555;  // Assumiamo una emissione di 555 gCO2 per KWh di consumo energetico

    printf("L'edificio emette %f kg di CO2 all'anno\n", emissione_co2 / 1000);
}


void automobile() {
    double km_percorsi, consumo, emissione_co2;

    printf("Inserisci i km percorsi dall'automobile (in km): ");
    scanf("%lf", &km_percorsi);
    printf("Inserisci il consumo dell'automobile (in litri/100 km): ");
    scanf("%lf", &consumo);

    emissione_co2 = km_percorsi * consumo * 2.32;  // Assumiamo una emissione di 2.32 kgCO2 per litro di carburante

    printf("L'automobile emette %f kg di CO2 all'anno\n", emissione_co2);
}


void bicicletta() {
    printf("La bicicletta non emette CO2\n");
}


int main(void) {
    void (*operazioni[3])(void) = {edificio, automobile, bicicletta};
    int scelta;

    printf("Scegli il tipo di emissione di CO2 da calcolare:\n");
    printf("1) Edificio\n");
    printf("2) Automobile\n");
    printf("3) Bicicletta\n");
    scanf("%d", &scelta);

    (*operazioni[scelta - 1])();

    return 0;
}
