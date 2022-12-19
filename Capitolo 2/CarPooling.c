//
// Created by Leonardo Birardi on 09/12/2022.
//
// Sicurezza C: https://wiki.sei.cmu.edu/confluence/display/c


#include <stdio.h>
#include <limits.h>


int main(void) {
    // Azzero le variabili per evitare l'errore logico
    // INIZIALIZZARE SEMPRE TUTTI I CONTATORI E I TOTALI
    float kmDaPercorrere = 0,
            costoCarburanteAlLitro = 0,
            mediaKmPerLitro = 0,
            costoParcheggioAlGiorno = 0,
            costoPedaggioAlGiorno = 0,
            carburanteUtilizzato = 0,
            costoCarburanteUtilizzato = 0,
            totale = 0;
    // Il numero dei contatori e di alcune variabili può essere solo positivo (risparmio memoria)
    unsigned int nPasseggeri;

    // USIAMO scanf_s (implementata dalla Microsoft) perchè ci consente di controllare che non vengano inseriti valori che generino overflow
    printf("Inserisci i km da percorrere:");
    scanf_s("%f", &kmDaPercorrere, sizeof(kmDaPercorrere));
    printf("Insersci il costo del carburante per litro in euro:");
    scanf_s("%f", &costoCarburanteAlLitro, sizeof(costoCarburanteAlLitro));
    printf("Interisci la media di km percorsi con un litro:");
    scanf_s("%f", &mediaKmPerLitro, sizeof(mediaKmPerLitro));
    printf("Inserisci il costo del parcheggio giornaliero in euro:");
    scanf_s("%f", &costoParcheggioAlGiorno, sizeof(costoPedaggioAlGiorno));
    printf("Inserisci il costo del pedaggio giornaliero in euro:");
    scanf_s("%f", &costoPedaggioAlGiorno, sizeof(costoPedaggioAlGiorno));
    printf("Inserisci il numero di passeggeri per il calcolo del Car Pooling:");
    scanf_s("%d", &nPasseggeri, sizeof(nPasseggeri));

    // --- Calcolo spesa giornaliera senza car pooling ---

    // Assicurarsi che il divisore dia != 0
    if (mediaKmPerLitro > 0)
        carburanteUtilizzato = kmDaPercorrere / mediaKmPerLitro;
    else {
        printf_s("Divisione per 0 non possibile");
        exit(0);
    }

    // __builtin_sadd_overflow è una funzione che controlla se c'è overflw fra i valori
    if (__builtin_sadd_overflow(carburanteUtilizzato, costoCarburanteAlLitro, &costoCarburanteUtilizzato)) {
        printf_s("Overflow");
        exit(0);
    } else
        costoCarburanteUtilizzato = carburanteUtilizzato * costoCarburanteAlLitro;

    // Gestisco errore overflow
    if (__builtin_sadd_overflow(costoCarburanteUtilizzato + costoParcheggioAlGiorno, costoPedaggioAlGiorno, &totale)) {
        printf_s("Overflow");
        exit(0);
    } else
        totale = costoCarburanteUtilizzato + costoParcheggioAlGiorno + costoPedaggioAlGiorno;

    // Print sicura
    printf_s("Costo Totale SENZA Car Pooling: %.2f euro\n", totale, sizeof(totale));

    // --- Calcolo spesa giornaliera con car pooling ---
    if (nPasseggeri > 0)
        printf_s("Costo Totale CON Car Pooling: %.2f euro\n", totale / nPasseggeri, sizeof(totale / nPasseggeri));
    else {
        printf_s("Divisione per 0 non possibile");
        exit(0);
    }

    return 0;
}
