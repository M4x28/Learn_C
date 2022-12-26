//
// Created by Leonardo Birardi on 10/12/2022.
//


#include <stdio.h>


float stimaPopolazione(float popolazioneAttuale, int nAnniStima);
float differenzaDemograficaInPercentuale(float popolazionePrimoAnno, float popolazioneSecondoAnno);


int main(void) {
    // Inizializzo a 0 per pulire la memoria da eventuali valori sporchi
    unsigned int scelta = 0, nAnniStima = 0, annoCorrente = 0;
    float popolazioneAttuale = 0, popolazionePrimoAnno = 0, popolazioneSecondoAnno = 0;

    while (scelta != 1 && scelta != 2) {
        printf_s("Cosa vuoi fare? [1:Stima della crescita demografica nei prossimi N anni, 2:Calcola la crescita demografica in % tra 2 anni]:");
        scanf_s("%d", &scelta, sizeof(scelta));
    }


    if (scelta == 1) {
        printf_s("Inserisci la popolazione Mondiale attuale in miliardi: ");
        scanf_s("%f", &popolazioneAttuale, sizeof(popolazioneAttuale));

        printf_s("Inserisci l'anno attuale: ");
        scanf_s("%d", &annoCorrente, sizeof(annoCorrente));

        printf_s("Inserisci per quanti anni fare la stima: ");
        scanf_s("%d", &nAnniStima, sizeof(nAnniStima));

        // Non e' 0.1% annuo ma varia, in media si calcola che sia 0.1% annuo
        puts("Nel 2022 la crescita della popolazione mondiale e' pari all'1%% annuo, statisticamente si e' dimostrato che questa percentuale diminuisce delll'0.1%% ogni anno.");

        for (unsigned int i = 1; i <= nAnniStima; i++)
            printf_s("La popolazione nel %d sara' di: %f miliardi\n", annoCorrente + i, stimaPopolazione(popolazioneAttuale, i));


    } else if (scelta == 2) {
        printf_s("Inserisci la popolazione Mondiale del primo anno in miliardi: ");
        scanf_s("%f", &popolazionePrimoAnno, sizeof(popolazionePrimoAnno));

        printf_s("Inserisci la popolazione Mondiale del secondo anno in miliardi: ");
        scanf_s("%f", &popolazioneSecondoAnno, sizeof(popolazioneSecondoAnno));

        printf_s("La crescita demografica tra i due anni e' del %.3f%%.", differenzaDemograficaInPercentuale(popolazionePrimoAnno, popolazioneSecondoAnno));
    }

    return 0;
}


// Inizio stima popolazione per i prossimi N anni
float stimaPopolazione(float popolazioneAttuale, int nAnniStima) {
    float parcentualeAttuale = 1.0;

    for (unsigned int i = 0; i < nAnniStima; i++) {
        popolazioneAttuale += ((popolazioneAttuale * parcentualeAttuale) / 100);
        parcentualeAttuale -= 0.1;
    }

    return popolazioneAttuale;
}
// Fine


// Inizio differenza della popolazione mondiale tra 2 anni in %
float differenzaDemograficaInPercentuale(float popolazionePrimoAnno, float popolazioneSecondoAnno) {
    return (((100.0 / popolazionePrimoAnno) * popolazioneSecondoAnno) - 100.0);
}
// Fine