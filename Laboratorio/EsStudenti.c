//
// Created by Leonardo Birardi on 14/03/2023.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define N_STUDENTI 5
#define N_VOTI 3


typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    float voto;
    bool lode;
} Voto;

typedef struct {
    char nome[20];
    char cognome[20];
    Data dataDiNascita;
    Voto voti[3];
} Studente;


const int giorniDelMese[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


void acquisisciDataDiNascita(Studente *studente);
void acquisisciNomeCognome(Studente *studente);
void acquisisciStudenteEVoti(Studente *studente);
void acquisisciVotiStudente(Studente *studente);
void acquisisciVoto(Studente *studente, int votoIndex);
bool controllaData(int giorno, int mese, int anno);
void calcolaEVisualizzaMedia(const Studente *studenti, int nStudenti);
float calcolaMedia(const Studente *studente);
void generaDataDiNascita(Studente *s);
void generaNomeCognome(Studente *s);
void generaVoti(Studente *s);
void popolaStudente(Studente *s);
void popolaStudenti(Studente studenti[], int n);
Studente *trovaStudenteMigliore(const Studente studenti[], int n);
void visualizzaMedia(const Studente *studente, float media);
void visualizzaStudente(const Studente *s);
void visualizzaStudenti(const Studente studenti[], int n);


int main() {
    Studente studenti[N_STUDENTI];

    // Popolazione l'array di studenti
    popolaStudenti(studenti, N_STUDENTI);

    // Visualizzazione degli studenti generati
    visualizzaStudenti(studenti, N_STUDENTI);

    // Calcolo e Visualizzo la media dei voti di ogni studente
    calcolaEVisualizzaMedia(studenti, N_STUDENTI);

    // Troviamo lo studente con la media più alta
    Studente *studenteMigliore = trovaStudenteMigliore(studenti, N_STUDENTI);

    // Visualizzo lo studente con la media più alta
    printf("\nLo studente con media maggiore e':\n");
    visualizzaStudente(studenteMigliore);

    return 0;
}


void visualizzaStudente(const Studente *s)
{
    printf("Nome: %s\n", s->nome);
    printf("Cognome: %s\n", s->cognome);
    printf("Data di nascita: %d/%d/%d\n", s->dataDiNascita.giorno, s->dataDiNascita.mese, s->dataDiNascita.anno);
    printf("\n");
}

void visualizzaStudenti(const Studente studenti[], int n)
{
    printf("Elenco Studenti:\n");
    for (int i = 0; i < n; i++)
        visualizzaStudente(&studenti[i]);
}

void acquisisciVotiStudente(Studente *studente) {
    printf("Inserisci i voti per lo studente %s %s:\n", studente->nome, studente->cognome);
    for (int j = 0; j < N_VOTI; j++)
        acquisisciVoto(studente, j);
}

void acquisisciVoto(Studente *studente, int votoIndex) {
    printf("Inserisci il voto %d per lo studente %s %s:\n", votoIndex+1, studente->nome, studente->cognome);
    int lode;
    do {
        printf("Voto: ");
        scanf("%f", &studente->voti[votoIndex].voto);
    } while (studente->voti[votoIndex].voto < 0 || studente->voti[votoIndex].voto > 30);

    if (studente->voti[votoIndex].voto == 30) {
        printf("Lode? (1=si, 0=no): ");
        scanf("%d", &lode);
        studente->voti[votoIndex].lode = (bool) lode;
    }
}

void acquisisciStudenteEVoti(Studente *studente) {
    acquisisciNomeCognome(studente);
    acquisisciDataDiNascita(studente);
    acquisisciVotiStudente(studente);
}

void acquisisciNomeCognome(Studente *studente) {
    printf("Inserisci il nome dello studente: ");
    scanf("%s", studente->nome);

    printf("Inserisci il cognome dello studente: ");
    scanf("%s", studente->cognome);
}

void acquisisciDataDiNascita(Studente *studente) {
    int giorno, mese, anno;
    do {
        printf("Inserisci la data di nascita di %s %s (gg/mm/aaaa): ", studente->nome, studente->cognome);
        scanf("%d/%d/%d", &giorno, &mese, &anno);
    } while (!controllaData(giorno, mese, anno));

    studente->dataDiNascita.giorno = giorno;
    studente->dataDiNascita.mese = mese;
    studente->dataDiNascita.anno = anno;
}

bool controllaData(int giorno, int mese, int anno) {
    bool bisestile = (anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0;

    if (anno < 1900 || anno > 2023) {
        printf("Anno non valido.\n");
        return false;
    }

    if (mese < 1 || mese > 12) {
        printf("Mese non valido.\n");
        return false;
    }

    if (giorno < 1 || giorno > giorniDelMese[mese - 1]) {
        if (mese == 2 && bisestile && giorno == 29) {
            return true;
        } else {
            printf("Giorno non valido.\n");
            return false;
        }
    }

    return true;
}

float calcolaMedia(const Studente *studente) {
    float somma = 0;
    for (int i = 0; i < N_VOTI; i++)
        somma += studente->voti[i].voto;
    return somma / N_VOTI;
}

void visualizzaMedia(const Studente *studente, float media) {
    printf("La media dei voti dello studente %s %s e': %.2f\n", studente->nome, studente->cognome, media);
}

void calcolaEVisualizzaMedia(const Studente *studenti, int nStudenti) {
    for (int i = 0; i < nStudenti; i++)
        visualizzaMedia(&studenti[i], calcolaMedia(&studenti[i]));
}

Studente* trovaStudenteMigliore(const Studente studenti[], int n) {
    Studente *studenteMigliore = &studenti[0];
    float mediaMigliore = calcolaMedia(&studenti[0]);

    for (int i = 1; i < n; i++) {
        float media = calcolaMedia(&studenti[i]);
        if (media > mediaMigliore) {
            mediaMigliore = media;
            studenteMigliore = &studenti[i];
        }
    }
    return studenteMigliore;
}

// --- POPOLAMENTO ARRAY ---

// Funzione per generare un nome e un cognome casuali
void generaNomeCognome(Studente *s) {
    char nomi[][20] = {"Mario", "Luigi", "Giuseppe", "Francesco", "Roberto"};
    char cognomi[][20] = {"Rossi", "Verdi", "Bianchi", "Neri", "Gialli"};

    strcpy(s->nome, nomi[rand() % 5]);
    strcpy(s->cognome, cognomi[rand() % 5]);
}

// Funzione per generare una data di nascita casuale
void generaDataDiNascita(Studente *s) {
    s->dataDiNascita.giorno = rand() % 28 + 1;
    s->dataDiNascita.mese = rand() % 12 + 1;
    s->dataDiNascita.anno = rand() % 10 + 1990;
}

// Funzione per generare i voti casuali di uno studente
void generaVoti(Studente *s) {
    for (int j = 0; j < N_VOTI; j++) {
        s->voti[j].voto = rand() % 13 + 18;
        s->voti[j].lode = false; // Nessuna lode di default
    }
}

// Funzione principale per la generazione di uno studente
void popolaStudente(Studente *s) {
    generaNomeCognome(s); // Generiamo un nome e cognome casuale
    generaDataDiNascita(s); // Generiamo una data di nascita casuale
    generaVoti(s); // Generiamo i voti casuali
}

void popolaStudenti(Studente studenti[], int n) {
    srand(time(NULL)); // Inizializziamo il generatore di numeri casuali
    for (int i = 0; i < n; i++)
        popolaStudente(&studenti[i]);
}