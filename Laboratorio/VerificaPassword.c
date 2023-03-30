//
// Created by Leonardo Birardi on 30/03/2023.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Seed Random non prevedibile (Windows)
#include <windows.h>
#include <wincrypt.h>

// Costanti
#define LUNGHEZZA_PASSWORD 8
#define MAX_LUNGHEZZA 100
#define MIN_MAIUSCOLE 1
#define MIN_NUMERI 1
#define MIN_SPECIALI 1

// Prototipi
void acquisisci_password(char *password);
void acquisisci_scelta(int *scelta);
char genera_carattere_casuale(char tipo);
void genera_password(char *password);
void gestisci_scelta(int *scelta, char *password);
void menu();
void stampa_password_generata(const char *password);
void stampa_risultato_verifica_password(int errore);
int verifica_lunghezza(const char *password);
int verifica_maiuscola(const char *password);
int verifica_numero(const char *password);
int verifica_speciale(const char *password);
int verifica_password(const char *password);


int main() {
    char password[MAX_LUNGHEZZA];
    int scelta;

    do {
        acquisisci_scelta(&scelta);
        gestisci_scelta(&scelta, password);
    } while (scelta != 0);

    return 0;
}


// Menù
void menu() {
    printf("\nMenu:\n");
    printf("1. Verifica password\n");
    printf("2. Genera password\n");
    printf("0. Esci\n");
    printf("Inserisci la tua scelta: ");
}

// Acquisizione Password
void acquisisci_password(char *password) {
    printf("Inserisci la password: ");
    fgets(password, MAX_LUNGHEZZA, stdin);
    password[strcspn(password, "\n")] = '\0'; // rimuove il carattere di nuova riga
}

// Acquisisci Scelta Utente
void acquisisci_scelta(int *scelta) {
    char buffer[100];
    char *endptr;

    do {
        menu();
        fgets(buffer, sizeof(buffer), stdin); // leggo riga in input
        *scelta = strtol(buffer, &endptr, 10); // converto in intero
        if (*endptr != '\n') {
            printf("Input non valido. Riprova.\n");
        } else if (*scelta < 0 || *scelta > 2) {
            printf("Scelta non valida. Riprova.\n");
        }
    } while (*endptr != '\n' || *scelta < 0 || *scelta > 2);
}

// Gestore scelta utente
void gestisci_scelta(int *scelta, char *password) {
    switch (*scelta) {
        case 1:
            acquisisci_password(password);
            stampa_risultato_verifica_password(verifica_password(password));
            break;
        case 2:
            do
                genera_password(password);
            while (verifica_password(password) != 0);

            stampa_password_generata(password);
            break;
        case 0:
            printf("Uscita dal programma.\n");
            break;
        default:
            printf("Scelta non valida.\n");
            break;
    }
}

// Controllo che la password soddisfa i requisiti minimi
int verifica_password(const char *password) {
    if (verifica_maiuscola(password) && verifica_numero(password) && verifica_lunghezza(password) && verifica_speciale(password)) {
        return 0;
    } else {
        if (!verifica_maiuscola(password)) {
            return 1;
        }
        if (!verifica_numero(password)) {
            return 2;
        }
        if (!verifica_lunghezza(password)) {
            return 3;
        }
        if (!verifica_speciale(password)) {
            return 4;
        }
    }
}

// Stampa a video il risultato della verifica
void stampa_risultato_verifica_password(int errore) {
    switch (errore) {
        case 0:
            printf("Password corretta!\n");
            break;
        case 1:
            printf("Errore: la password deve contenere almeno %d lettere maiuscole.\n", MIN_MAIUSCOLE);
            break;
        case 2:
            printf("Errore: la password deve contenere almeno %d numeri.\n", MIN_NUMERI);
            break;
        case 3:
            printf("Errore: la password deve essere lunga almeno %d caratteri.\n", LUNGHEZZA_PASSWORD);
            break;
        case 4:
            printf("Errore: la password deve contenere almeno %d caratteri speciali.\n", MIN_SPECIALI);
            break;
        default:
            printf("Errore generico.\n");
            break;
    }
}

// Verifica Maiuscole
int verifica_maiuscola(const char *password) {
    int maiuscole = 0;

    for (int i = 0; password[i] != '\0'; i++)
        if (isupper(password[i])) maiuscole++;

    return maiuscole >= MIN_MAIUSCOLE;
}

// Verifica Numeri
int verifica_numero(const char *password) {
    int numeri = 0;

    for (int i = 0; password[i] != '\0'; i++)
        if (isdigit(password[i])) numeri++;

    return numeri >= MIN_NUMERI;
}

// Verifica Lunghezza
int verifica_lunghezza(const char *password) {
    return strlen(password) >= LUNGHEZZA_PASSWORD;
}

// Verifica Caratteri Speciali
int verifica_speciale(const char *password) {
    int speciali = 0;

    for (int i = 0; password[i] != '\0'; i++)
        if (!isalnum(password[i])) speciali++;

    return speciali >= MIN_SPECIALI;
}

// Stampa Password Generata
void stampa_password_generata(const char *password) {
    printf("La password generata e': %s\n", password);
}

// Generatore di Password
void genera_password(char *password) {
    int maiuscola = 0;
    int numero = 0;
    int speciali = 0;

    for (int i = 0; i < LUNGHEZZA_PASSWORD; i++) {
        // Inizializzazione seme casuale mediante l'utilizzo di algoritmi aleatori
        HCRYPTPROV hCryptProv;
        if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) {
            fprintf(stderr, "CryptAcquireContext failed with error %lu\n", GetLastError());
            exit(EXIT_FAILURE);
        }
        unsigned int scelta;
        if (!CryptGenRandom(hCryptProv, sizeof(scelta), (BYTE *)&scelta)) {
            fprintf(stderr, "CryptGenRandom failed with error %lu\n", GetLastError());
            exit(EXIT_FAILURE);
        }
        CryptReleaseContext(hCryptProv, 0);

        scelta %= 4;
        if (scelta == 0) {
            // genera una lettera minuscola
            password[i] = genera_carattere_casuale('l');
        } else if (scelta == 1) {
            // genera una lettera maiuscola
            password[i] = genera_carattere_casuale('L');
            maiuscola = 1;
        } else if (scelta == 2) {
            // genera un numero
            password[i] = genera_carattere_casuale('n');
            numero = 1;
        } else {
            // genera un carattere speciale
            password[i] = genera_carattere_casuale('s');
            speciali++;
        }
    }

    // se non è stata generata una lettera maiuscola o un numero o un carattere speciale, li aggiungiamo alla fine
    if (!maiuscola) {
        password[LUNGHEZZA_PASSWORD - 3] = genera_carattere_casuale('L');
    }
    if (!numero) {
        password[LUNGHEZZA_PASSWORD - 2] = genera_carattere_casuale('n');
    }
    if (speciali < MIN_SPECIALI) {
        for (int i = LUNGHEZZA_PASSWORD - MIN_SPECIALI; i < LUNGHEZZA_PASSWORD; i++) {
            password[i] = genera_carattere_casuale('s');
        }
    }

    // terminatore di stringa
    password[LUNGHEZZA_PASSWORD] = '\0';
}

// Generatore di Caratteri Casuali
char genera_carattere_casuale(char tipo) {
    // Inizializzazione seme casuale mediante l'utilizzo di algoritmi aleatori
    HCRYPTPROV hCryptProv;
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        fprintf(stderr, "CryptAcquireContext failed with error %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }
    unsigned int c;
    if (!CryptGenRandom(hCryptProv, sizeof(c), (BYTE *)&c)) {
        fprintf(stderr, "CryptGenRandom failed with error %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }
    CryptReleaseContext(hCryptProv, 0);

    if (tipo == 'l') {
        // genera una lettera minuscola
        return (char) (97 + c % 26); // a
    } else if (tipo == 'L') {
        // genera una lettera maiuscola
        return (char) (65 + c % 26); // A
    } else if (tipo == 'n') {
        // genera un numero
        return (char) (48 + c % 10); // 0
    } else if (tipo == 's') {
        // genera un carattere speciale
        const char speciali[] = "!@#$%^&*()";
        return speciali[c % (sizeof(speciali) - 1)];
    } else {
        fprintf(stderr, "Tipo di carattere non valido: %c\n", tipo);
        exit(EXIT_FAILURE);
    }
}