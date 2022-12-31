//
// Created by Leonardo Birardi on 25/12/2022.
//

#include <stdio.h>
#include <time.h>

#define MIN_FREQUENZA_CARDIACA 220


typedef struct {
    char nome[50];
    char cognome[50];
    char sesso;
    int giornoNascita;
    int meseNascita;
    int annoNascita;
    int altezza;
    int peso;
} HealthProfile;


// calcola l'età della persona in anni
int calcolaEta(HealthProfile persona) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int eta = tm.tm_year + 1900 - persona.annoNascita;
    if (tm.tm_mon + 1 < persona.meseNascita ||
        (tm.tm_mon + 1 == persona.meseNascita && tm.tm_mday < persona.giornoNascita)) {
        eta--;
    }
    return eta;
}

// calcola la massima frequenza cardiaca della persona
int calcolaMassimaFrequenzaCardiaca(HealthProfile persona) {
    return MIN_FREQUENZA_CARDIACA - calcolaEta(persona);
}

// calcola l'intervallo di frequenza cardiaca normale della persona
void calcolaIntervalloFrequenzaCardiacaNormale(HealthProfile persona, int *minimo, int *massimo) {
    int massima = calcolaMassimaFrequenzaCardiaca(persona);
    *minimo = massima * 0.5;
    *massimo = massima * 0.85;
}

// calcola l'indice di massa corporea della persona
double calcolaIndiceMassaCorporea(HealthProfile persona) {
    return (double) persona.peso / ((double) persona.altezza * persona.altezza) * 10000;
}

int main() {
    HealthProfile persona;
    int min_frequenza_cardiaca = 0, max_frequenza_cardiaca = 0;

    printf("Inserisci le informazioni della persona:\n");
    printf("Nome: ");
    scanf("%s", persona.nome);
    printf("Cognome: ");
    scanf("%s", persona.cognome);
    printf("Sesso (M/F): ");
    scanf(" %c", &persona.sesso);
    printf("Inserisci la data di nascita nel formato dd-mm-AAAA: ");
    scanf("%d%*c%d%*c%d", &persona.giornoNascita, &persona.meseNascita, &persona.annoNascita); // l'operatore %*c come carattere di soppressione dell'assegnazione
    printf("Altezza (in cm): ");
    scanf("%d", &persona.altezza);
    printf("Peso (in kg): ");
    scanf("%d", &persona.peso);

    printf_s("Eta' soggetto: %d\n", calcolaEta(persona), sizeof(calcolaEta(persona)));
    printf_s("BMI soggetto: %f\n", calcolaIndiceMassaCorporea(persona), sizeof(calcolaIndiceMassaCorporea(persona)));
    printf_s("Massima frequenza cardiaca del soggetto: %d\n", calcolaMassimaFrequenzaCardiaca(persona),
             sizeof(calcolaMassimaFrequenzaCardiaca(persona)));

    calcolaIntervalloFrequenzaCardiacaNormale(persona, &min_frequenza_cardiaca, &max_frequenza_cardiaca);
    printf_s("Intervallo della frequenza cardiaca normale del soggetto: %d-%d\n", min_frequenza_cardiaca,
             max_frequenza_cardiaca,
             sizeof(min_frequenza_cardiaca), sizeof(max_frequenza_cardiaca));

    return 0;
}