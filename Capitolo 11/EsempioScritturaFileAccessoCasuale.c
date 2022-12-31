//
// Created by Leonardo Birardi on 28/12/2022.
//

#include <stdio.h>


// definizione della struttura clientData
typedef struct {
    unsigned int acctNum; // numero del conto
    char lastName[15]; // cognome del titolare del conto
    char firstName[10]; // nome del titolare del conto
    double balance; // saldo del conto
} ClientData;
// fine della struttura clientData


int main(void) {

    FILE *cfPtr; // puntatore al file accounts.dat

    // fopen apre il file per l'aggiornamento
    if ((cfPtr = fopen("accounts.dat", "rb+")) == NULL) {
        puts("File could not be opened.");
    } else {
        // crea un oggetto clientData con informazioni predefinite
        ClientData client = {0, "", "", 0.0};

        // richiedi all'utente di specificare il numero di conto
        printf("%s", "Enter account number" " (1 to 100, 0 to end input): ");
        scanf("%d", &client.acctNum);

        // l'utente inserisce le informazioni, che vengono copiate sul file
        while (client.acctNum != 0) {
            // l'utente inserisce il cognome, il nome e il saldo
            printf("%s", "\nEnter lastname, firstname, balance: ");

            // imposta il record con il cognome, il nome e il valore del saldo
            fscanf(stdin, "%14s%9s%lf", client.lastName, client.firstName, &client.balance);

            // cerca (seek) nel file la posizione del record specificato
            fseek(cfPtr, (client.acctNum - 1) * sizeof(ClientData), SEEK_SET);

            // scrivi le informazioni specificate dall'utente sul file, il terzo argomento specifica quanti elementi scrivere
            // la funzione fwrite ritorna il numero di elementi scritti con successo
            fwrite(&client, sizeof(ClientData), 1, cfPtr);

            // consenti all'utente di inserire un altro numero di conto
            printf("%s", "\nEnter account number: ");
            scanf("%d", &client.acctNum);
        }

        fclose(cfPtr); // fclose chiude il file
    }
}