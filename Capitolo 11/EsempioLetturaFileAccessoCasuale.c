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


int main(void) {
    FILE *cfPtr; // puntatore al file accounts.dat

    // fopen apre il file per la lettura binaria
    if ((cfPtr = fopen("accounts.dat", "rb")) == NULL) {
        puts("File could not be opened.");
    } else {
        printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

        // leggi tutti i record dal file (fino a eof)
        while (!feof(cfPtr)) {

            // crea clientData con informazioni predefinite
            ClientData client = {0, "", "", 0.0};
            // fread ritorna il numero degli elementi letti correttamente
            int result = fread(&client, sizeof(ClientData), 1, cfPtr);

            // stampa il record
            if (result != 0 && client.acctNum != 0) {
                printf("%-6d%-16s%-11s%10.2f\n",
                       client.acctNum,
                       client.lastName,
                       client.firstName,
                       client.balance);
            }
        }
        fclose(cfPtr); // fclose chiude il file
    }
}