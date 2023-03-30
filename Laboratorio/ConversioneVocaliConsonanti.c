//
// Created by Leonardo Birardi on 30/03/2023.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

// Prototipi
void acquisisci_password(char *password);
void converti_password(char *password);
int controlla_consonante(char c);
int controlla_vocale(char c);
void stampa_password_convertita(char *password);


int main() {
    char password[MAX_LENGTH];

    acquisisci_password(password);

    converti_password(password);

    stampa_password_convertita(password);

    return 0;
}


void acquisisci_password(char *password) {
    printf("Inserisci la password: ");
    scanf("%s", password);
}

void stampa_password_convertita(char *password) {
    printf("Password convertita: %s\n", password);
}

void converti_password(char *password) {
    for (int i = 0; i < strlen(password); i++) {
        if (controlla_vocale(password[i])) {
            password[i] = '$';
        } else if (controlla_consonante(password[i])) {
            password[i] = '*';
        }
    }
}

int controlla_vocale(char c) {
    return strchr("aeiouAEIOU", c) != NULL;
}

int controlla_consonante(char c) {
    return isalpha(c) && !controlla_vocale(c);
}