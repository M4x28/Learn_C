//
// Created by Leonardo Birardi on 15/12/2022.
//

#include <stdio.h>

#define IMPORTO_BASE_PROVVIGIONE 250.0
#define PERCENTUALE_PROVVIGIONE 5.7


float CalcoloPagaManager(unsigned short int nSettimane, float importo);
float CalcoloPagaLavoratoreAOre(unsigned short int nOre, float importo);
float CalcoloLavoratoreAProvvigione(float importo);
float CalcoloLavoratoreACottimo(unsigned short int nProdotti, float importo);


int main(void) {
    unsigned short int scelta = 0, nSettimane = 0;
    float importo = 0.0f, ore;

    do {
        printf_s("Inserisci il tipo di lavoratore:\n 1) Manager;\n 2) Lavoratore a ore;\n 3) Lavoratore a provvigione;\n 4) Lavoratore a cottimo;\nOpzione:");
        scanf_s("%hu", &scelta, sizeof(scelta));
    } while(scelta <= 0 || scelta > 4);


    switch (scelta) {
        case 1:

            printf_s("Inserisci il numero delle settimane:");
            scanf_s("%d", &nSettimane);
            printf_s("Inserisci la paga settimanale:");
            scanf_s("%f", &importo);
            printf_s("Paga Manager: %.2f euro", CalcoloPagaManager(nSettimane, importo));
            break;
        case 2:
            printf_s("Inserire il numero delle ore:");
            scanf_s("%f", &ore, sizeof(ore));
            printf_s("Inserisci la paga oraria:");
            scanf_s("%f", &importo, sizeof(importo));
            printf_s("Paga Lavoratore orario: %.2f euro", CalcoloPagaLavoratoreAOre(ore, importo));
            break;
        case 3:
            printf_s("Inserisci l'importo delle vendite settimanali lorde:");
            scanf_s("%f", &importo, sizeof(importo));
            printf_s("Paga Lavoratore a provvigione: %.2f euro", CalcoloLavoratoreAProvvigione(importo));
            break;
        case 4:
            printf_s("Inserisci quantità dei prodotti consegnata:");
            scanf_s("%d", &nSettimane, sizeof(nSettimane));
            printf_s("Inserisci il prezzo per prodotto:");
            scanf_s("%f", &importo, sizeof(importo));
            printf_s("Paga Lavoratore a cottimo: %.2f euro", CalcoloLavoratoreACottimo(nSettimane, importo));
            break;
        default:
            puts("Errore nella selezione del tipo di lavoratore");
            exit(1);
    }


    return 0;
}


float CalcoloPagaManager(unsigned short int nSettimane, float importo) {
    return nSettimane * importo;
}


float CalcoloPagaLavoratoreAOre(unsigned short int nOre, float importo) {
    float resto = nOre % 40;

    if(resto > 0 && nOre > 40) return (resto * (importo + (importo/2))) + ((nOre - resto) * importo);
    else return nOre * importo;
}


float CalcoloLavoratoreAProvvigione(float importo) {
    return IMPORTO_BASE_PROVVIGIONE + ((importo / 100) * PERCENTUALE_PROVVIGIONE);
}


float CalcoloLavoratoreACottimo(unsigned short int nProdotti, float importo) {
    return nProdotti * importo;
}