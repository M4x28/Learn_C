//
// Created by Leonardo Birardi on 23/03/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N_AUTO 5
#define N_CHAR 20

typedef struct
{
    char modello[N_CHAR];
    char nome[N_CHAR];
    int cilindrata;
} Automobile;

// Dichiarazione Prototipi
void acquisisciAutomobile(Automobile *automobile);
void acquisisciAutomobili(Automobile *automobili, int n);
void bubbleSort(Automobile *array, int n, int (*compare)(Automobile, Automobile));
int compareCilindrataAscendente(Automobile a, Automobile b);
int compareCilindrataDiscendente(Automobile a, Automobile b);
int max(int a, int b);
int min(int a, int b);
int menu();
void popolaArray(Automobile *automobili, int l);
void stampaAutomobile(Automobile automobile);
void stampaAutomobili(Automobile *automobili, int n);
void swap(Automobile *a, Automobile *b);


int main()
{
    Automobile automobili[N_AUTO];

    // Popola Array Automobili automaticamente
    popolaArray(automobili, N_AUTO);

    // Acquisisci Scelta
    int choice = menu();

    // Ordina in base alla scelta
    if (choice == 1)
    {
        bubbleSort(automobili, N_AUTO, compareCilindrataAscendente);
    }
    else if (choice == 2)
    {
        bubbleSort(automobili, N_AUTO, compareCilindrataDiscendente);
    }
    else
    {
        printf("Scelta non valida\n");
        return 1;
    }

    // Stampa automobili
    stampaAutomobili(automobili, N_AUTO);

    return 0;
}

// Menú utente
int menu()
{
    int choice = 0;

    do
    {
        printf("Scegli il tipo di ordinamento:\n");
        printf("1) Ascendente\n");
        printf("2) Discendente\n");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2);

    return choice;
}

// Popolamento Array Automobili Automatico
void popolaArray(Automobile *automobili, int l)
{
    char *nomi[] = {"Fiat", "Ford", "Renault", "Peugeot", "Citroen"};
    char *modelli[] = {"Panda", "Fiesta", "Clio", "208", "C3"};
    int cilindrate[] = {1200, 1400, 1600, 1800, 2000};

    for (int i = 0; i < l; i++)
    {
        strcpy(automobili[i].nome, nomi[i % 5]);
        strcpy(automobili[i].modello, modelli[i % 5]);
        automobili[i].cilindrata = cilindrate[i % 5];
    }
}

// Acquisizione singola Automobile
void acquisisciAutomobile(Automobile *automobile)
{
    printf("Inserisci il nome dell'automobile: ");
    scanf("%s", automobile->nome);
    printf("Inserisci la marca dell'automobile: ");
    scanf("%s", automobile->modello);
    printf("Inserisci la cilindrata dell'automobile: ");
    scanf("%d", &automobile->cilindrata);
}

// Acquisizione piú Automobili
void acquisisciAutomobili(Automobile *automobili, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nAutomobile %d:\n", i + 1);
        acquisisciAutomobile(&automobili[i]);
    }
}

// Scambio Automobili
void swap(Automobile *a, Automobile *b)
{
    Automobile temp = *a;
    *a = *b;
    *b = temp;
}

// Funzione di Ordinamento
void bubbleSort(Automobile *array, int n, int (*compare)(Automobile, Automobile))
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (compare(array[i], array[i + 1]) > 0)
            {
                swap(&array[i], &array[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

// Ordinamento Ascendente
int compareCilindrataAscendente(Automobile a, Automobile b)
{
    return min(a.cilindrata, b.cilindrata) == a.cilindrata ? -1 : 1;
}

// Ordinamento Discendente
int compareCilindrataDiscendente(Automobile a, Automobile b)
{
    return max(a.cilindrata, b.cilindrata) == a.cilindrata ? -1 : 1;
}

// Stampa singola Automobile
void stampaAutomobile(Automobile automobile)
{
    printf("%s %s %d\n", automobile.nome, automobile.modello, automobile.cilindrata);
}

// Stampa tutte le Automobili
void stampaAutomobili(Automobile *automobili, int n)
{
    printf("Elenco automobili:\n");
    for (int i = 0; i < n; i++)
    {
        stampaAutomobile(automobili[i]);
    }
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}
