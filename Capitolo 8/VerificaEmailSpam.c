//
// Created by Leonardo Birardi on 22/12/2022.
//

#include <stdio.h>
#include <string.h>

#define MESSAGE_LENGTH 1000
#define NUM_KEYWORDS 30

// Lista di parole chiave o frasi comunemente trovate nei messaggi di spam
const char *keywords[NUM_KEYWORDS] = {
        "viagra",
        "cialis",
        "pills",
        "medicine",
        "free",
        "earnings",
        "bonus",
        "investment",
        "lottery",
        "prize",
        "wealth",
        "riches",
        "million dollars",
        "billion dollars",
        "billions of dollars",
        "make money",
        "financial freedom",
        "work from home",
        "income",
        "business",
        "marketing",
        "offer",
        "satisfaction",
        "guaranteed",
        "win",
        "winner",
        "won",
        "congratulations",
        "click here",
        "subscribe",
        "subscription"
};

int main(void) {
    // Array per memorizzare il messaggio dell'utente
    char message[MESSAGE_LENGTH];

    printf("Inserisci il tuo messaggio di posta elettronica: ");
    fgets(message, MESSAGE_LENGTH, stdin);

    // Punteggio di spam del messaggio
    int spam_score = 0;

    // Analizziamo il messaggio per ognuna delle parole chiave o frasi
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        // Cerchiamo le occorrenze della parola chiave o frase nel messaggio
        char *occurrence = strstr(message, keywords[i]);
        while (occurrence != NULL) {
            // Se l'abbiamo trovata, aumentiamo il punteggio di spam del messaggio
            spam_score++;
            // Cerchiamo la successiva occorrenza della parola chiave o frase
            occurrence = strstr(occurrence + 1, keywords[i]);
        }
    }

    // Valutiamo la probabilità che il messaggio sia indesiderato
    if (spam_score == 0) {
        printf("Il messaggio non sembra essere spam.\n");
    } else if (spam_score <= 5) {
        printf("Il messaggio potrebbe essere spam.\n");
    } else {
        printf("Il messaggio è probabilmente spam.\n");
    }

    return 0;
}
