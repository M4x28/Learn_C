//
// Created by Leonardo Birardi on 27/12/2022.
//

#include <stdio.h>
#include <string.h>

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char nome[30];
    char cognome[30];
    Data data_di_nascita;
} Studente;


int main() {
    // Dichiarazione di una variabile di tipo struttura
    Studente studente;

    // Assegnazione di valori alle variabili membro della struttura
    strcpy(studente.nome, "Mario");
    strcpy(studente.cognome, "Rossi");
    studente.data_di_nascita.giorno = 1;
    studente.data_di_nascita.mese = 1;
    studente.data_di_nascita.anno = 1990;

    // Stampa dei valori delle variabili membro della struttura
    printf("Nome: %studente\n", studente.nome);
    printf("Cognome: %studente\n", studente.cognome);
    printf("Data di nascita: %d/%d/%d\n", studente.data_di_nascita.giorno, studente.data_di_nascita.mese, studente.data_di_nascita.anno);

    return 0;
}