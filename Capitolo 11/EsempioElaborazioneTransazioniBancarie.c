//
// Created by Leonardo Birardi on 28/12/2022.
//

#include <stdio.h>


// definizione della struttura clientData
typedef struct {
    unsigned int acctNum; // numero di conto
    char lastName[15]; // cognome del titolare del conto
    char firstName[10]; // nome del titolare del conto
    double balance; // saldo del conto
} ClientData;


// prototipi
unsigned int enterChoice(void);
void textFile(FILE *readPtr);
void updateRecord(FILE *fPtr);
void newRecord(FILE *fPtr);
void deleteRecord(FILE *fPtr);


int main(void) {
    FILE *cfPtr; // puntatore al file accounts.dat

    // fopen apre il file per l'aggiornamento
    if ((cfPtr = fopen("accounts.dat", "rb+")) == NULL)
        puts("File could not be opened.");
    else {
        unsigned int choice; // scelta dell'utente
        // consenti all'utente di specificare l'azione
        while ((choice = enterChoice()) != 5) {
            switch (choice) {
                // crea un file di testo dal file di record
                case 1:
                    textFile(cfPtr);
                    break;
                // aggiorna un record
                case 2:
                    updateRecord(cfPtr);
                    break;
                // crea un record
                case 3:
                    newRecord(cfPtr);
                    break;
                // cancella un record esistente
                case 4:
                    deleteRecord(cfPtr);
                    break;
                // stampa un messaggio per una scelta non valida
                default:
                    puts("Incorrect choice");
                    break;
            }
        }
        fclose(cfPtr); // fclose chiude il file
    }
}


// crea un file di testo formattato per la stampa
void textFile(FILE *readPtr) {
    FILE *writePtr; // puntatore al file accounts.txt

    // fopen apre il file di testo per la scrittura
    if ((writePtr = fopen("accounts.txt", "wx")) == NULL)
        puts("File could not be opened.");
    else {
        // sposta il puntatore all'inizio del file
        //   rewind(readPtr); => può generare errori non controllabili
        //   meglio utilizzare fseek e impostarlo a 0, perchè se l'operazione fallisce la funzione ritorna un valore != 0
        if (fseek(writePtr, 0, SEEK_SET) != 0)
            printf_s("Errore nel rewind del file");
        else {
            fprintf_s(writePtr, "%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

            // copia tutti i record sul file di testo
            while (!feof(readPtr)) {
                // crea un oggetto clientData con informazioni predefinite
                ClientData client = {0, "", "", 0.0};
                unsigned long long result = fread(&client, sizeof(ClientData), 1, readPtr);

                // scrivi un singolo record sul file di testo
                if (result != 0 && client.acctNum != 0) {
                    fprintf_s(writePtr, "%-6d%-16s%-11s%10.2f\n",
                              client.acctNum,
                              client.lastName,
                              client.firstName,
                              client.balance);
                }
            }
            fclose(writePtr); // fclose chiude il file
        }
    }
}


// aggiorna il saldo in un record
void updateRecord(FILE *fPtr) {
    // ottieni il numero di conto da aggiornare
    printf_s("%s", "Enter account to update (1 - 100): ");
    long account; // numero del conto
    scanf_s("%li", &account, sizeof(account));

    // sposta il puntatore del file al record corretto nel file
    fseek(fPtr, (account - 1) * sizeof(ClientData),SEEK_SET);

    // crea un oggetto clientData senza informazioni
    ClientData client = {0, "", "", 0.0};

    // leggi il record dal file
    fread(&client, sizeof(ClientData), 1, fPtr);

    // stampa un messaggio di errore se il conto non esiste
    if (client.acctNum == 0)
        printf_s("Account #%d has no information.\n", account);
    else { // aggiorna il record
        printf_s("%-6d%-16s%-11s%10.2f\n\n",
               client.acctNum,
               client.lastName,
               client.firstName,
               client.balance);

        // richiedi l'ammontare della transazione all'utente
        printf_s("%s", "Enter charge (+) or payment (-): ");
        double transaction; // ammontare della transazione
        scanf_s("%lf", &transaction, sizeof(transaction));

        client.balance += transaction; // aggiorna il saldo del record
        printf_s("%-6d%-16s%-11s%10.2f\n",
               client.acctNum,
               client.lastName,
               client.firstName,
               client.balance);

        // sposta il puntatore del file al record corretto nel file
        fseek(fPtr, (account - 1) * sizeof(ClientData),SEEK_SET);

        // scrivi il record aggiornato al posto del vecchio record nel file
        fwrite(&client, sizeof(ClientData), 1, fPtr);
    }
}


// cancella un record esistente
void deleteRecord(FILE *fPtr) {
    // ottieni il numero del conto da cancellare
    printf_s("%s", "Enter account number to delete (1 - 100): ");
    unsigned int accountNum; // numero del conto
    scanf_s("%u", &accountNum, sizeof(accountNum));

    // sposta il puntatore del file al record corretto nel file
    fseek(fPtr, (accountNum - 1) * sizeof(ClientData),SEEK_SET);

    ClientData client; // memorizza il record letto dal file

    // leggi il record dal file
    fread(&client, sizeof(ClientData), 1, fPtr);

    // stampa un messaggio di errore se il record non esiste
    if (client.acctNum == 0)
        printf_s("Account %d does not exist.\n", accountNum);
    else { // cancella il record
        // sposta il puntatore del file al record corretto nel file
        fseek(fPtr, (accountNum - 1) * sizeof(ClientData),SEEK_SET);

        ClientData blankClient = {0, "", "", 0}; // cliente vuoto

        // sostituisci il record esistente con il record vuoto
        fwrite(&blankClient,sizeof(ClientData), 1, fPtr);
    }
}


// crea e inserisci un record
void newRecord(FILE *fPtr) {
    // ottieni il numero del conto da creare
    printf_s("%s", "Enter new account number (1 - 100): ");
    unsigned int accountNum; // numero del conto
    scanf_s("%u", &accountNum, sizeof(accountNum));

    // sposta il puntatore del file al record corretto nel file
    fseek(fPtr, (accountNum - 1) * sizeof(ClientData),SEEK_SET);

    // crea clientData con informazioni predefinite
    ClientData client = {0, "", "", 0.0};

    // leggi il record dal file
    fread(&client, sizeof(ClientData), 1, fPtr);

    // stampa un messaggio di errore se il conto esiste gia'
    if (client.acctNum != 0)
        printf_s("Account #%d already contains information.\n",
               client.acctNum);
    else { // crea il record
        // l'utente inserisce il cognome, il nome e il saldo
        printf_s("%s", "Enter lastname, firstname, balance\n? ");
        scanf_s("%14s%9s%lf",
              &client.lastName,
              &client.firstName,
              &client.balance,
              sizeof(client.lastName),
              sizeof(client.firstName),
              sizeof(client.balance));

        client.acctNum = accountNum;

        // sposta il puntatore del file al record corretto nel file
        fseek(fPtr, (client.acctNum - 1) * sizeof(ClientData), SEEK_SET);

        // inserisci il record nel file
        fwrite(&client,sizeof(ClientData), 1, fPtr);
    }
}


// consenti all'utente d'inserire la scelta del menu
unsigned int enterChoice(void) {
    // stampa le opzioni disponibili
    printf_s("%s", "\nEnter your choice\n"
                 "1 - store a formatted text file of accounts called\n"
                 " \"accounts.txt\" for printing\n"
                 "2 - update an account\n"
                 "3 - add a new account\n"
                 "4 - delete an account\n"
                 "5 - end program\n? ");

    unsigned int menuChoice; // scelta dell'utente
    scanf_s("%u", &menuChoice, sizeof(menuChoice)); // ricevi la scelta dall'utente
    return menuChoice;
}