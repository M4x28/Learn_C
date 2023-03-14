#include <stdio.h>
#include <stdbool.h>

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

void acquisisciStudente(Studente *s);
void visualizzaStudenti(Studente studenti[], int n);
void acquisisciVoti(Studente studenti[], int n);
void visualizzaMedie(Studente studenti[], int n);

int main() {
    Studente studenti[N_STUDENTI];

    return 0;
}

void acquisisciStudente(Studente *s)
{
    printf("Inserisci il nome dello studente: ");
    scanf("%s", s->nome);

    printf("Inserisci il cognome dello studente: ");
    scanf("%s", s->cognome);

    printf("Inserisci la data di nascita dello studente (gg/mm/aaaa): ");
    scanf("%d/%d/%d", &s->dataDiNascita.giorno, &s->dataDiNascita.mese, &s->dataDiNascita.anno);
}

void visualizzaStudenti(Studente studenti[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Nome: %s\n", studenti[i].nome);
        printf("Cognome: %s\n", studenti[i].cognome);
        printf("Data di nascita: %d/%d/%d\n", studenti[i].dataDiNascita.giorno, studenti[i].dataDiNascita.mese, studenti[i].dataDiNascita.anno);
        printf("\n");
    }
}

void acquisisciVoti(Studente studenti[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < N_VOTI; j++)
        {
            printf("Inserisci il voto %d dello studente %s %s: ", j + 1, studenti[i].nome, studenti[i].cognome);
            float voto;
            scanf("%f", &voto);

            while (voto < 0.0 || voto > 30.0)
            {
                printf("Il voto deve essere compreso tra 0 e 10. Reinserisci il voto %d dello studente %s %s: ", j + 1, studenti[i].nome, studenti[i].cognome);
                scanf("%f", &voto);
            }

            studenti[i].voti[j].voto = voto;

            printf("Lo studente %s %s ha preso la lode per il voto %d? (1 = si, 0 = no): ", studenti[i].nome, studenti[i].cognome, j + 1);
            int lode;
            scanf("%d", &lode);

            while (lode != 0 && lode != 1)
            {
                printf("Inserisci 1 se lo studente %s %s ha preso la lode per il voto %d, altrimenti inserisci 0: ", studenti[i].nome, studenti[i].cognome, j + 1);
                scanf("%d", &lode);
            }

            studenti[i].voti[j].lode = (bool)lode;
        }
    }
}

void visualizzaMedie(Studente studenti[], int n)
{
    for (int i = 0; i < n; i++)
    {
        float media = 0.0;

        for (int j = 0; j < N_VOTI; j++)
        {
            media += studenti[i].voti[j].voto;
        }

        media /= N_VOTI;

        printf("Media voti dello studente %s %s: %.2f\n", studenti[i].nome, studenti[i].cognome, media);
    }
}