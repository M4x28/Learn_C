//
// Created by Leonardo Birardi on 20/04/2023.
//

#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    char dato;
    struct Nodo *proxPtr;
};

typedef struct Nodo NodoLista;
typedef NodoLista *NodoListaPtr;

void inserisciNodo(NodoListaPtr *, char);

char cancellallodo(NodoListaPtr *, char);

int listaVuota(NodoListaPtr);

void stampaLista(NodoListaPtr);

void stampaMenu();

int main() {
    NodoListaPtr testaPtr = NULL;
    int scelta;
    char elemento;

    stampaMenu();
    printf("? ");
    scanf("%d", &scelta);

    while (scelta != 3) {
        switch (scelta) {
            case 1:
                printf("Inserire un carattere: ");
                scanf("\n%c", &elemento);
                inserisciNodo(&testaPtr, elemento);
                stampaLista(testaPtr);
                break;
            case 2:
                if (!listaVuota(testaPtr)) {
                    printf("Inserire il carattere da eliminare:");
                    scanf("\n%c", &elemento);
                    if (cancellallodo(&testaPtr, elemento)) {
                        printf("%c è stato eliminato.\n", elemento);
                        stampaLista(testaPtr);
                    } else printf("%c non esiste.\n\n", elemento);
                } else printf("La lista è vuota.\n\n");
                break;
            default:
                printf("Scelta non valida.\n\n");
                stampaMenu();
                break;
        }
        printf("? ");
        scanf("%d", &scelta);
    }
    printf("Fine del programma.\n");
    return 0;
}

void stampaMenu(void) {
    printf("Inserire la scelta:\n"
           "1 per inserire un elemento in lista.\n"
           "2 per cancellareun elemento dalla lista.\n"
           "3 per chiudere il programma.\n");
}

void inserisciNodo(NodoListaPtr *tPtr, char valore) {
    NodoListaPtr nuovoPtr, precPtr, corrPtr;
    nuovoPtr = malloc(sizeof(NodoLista));

    if (nuovoPtr != NULL) {
        nuovoPtr->dato = valore;
        nuovoPtr->proxPtr = NULL;
        precPtr = NULL;
        corrPtr = *tPtr;
        while (corrPtr != NULL && valore > corrPtr->dato) {
            precPtr = corrPtr;
            corrPtr = corrPtr->proxPtr;
        }
        if (precPtr == NULL) {
            nuovoPtr->proxPtr = *tPtr;
            *tPtr = nuovoPtr;
        } else {
            precPtr->proxPtr = nuovoPtr;
            nuovoPtr->proxPtr = corrPtr;
        }
    }
        else printf("%c non inserito. Manca la memoria.\n", valore);
    }

char cancellallodo(NodoListaPtr *tPtr, char valore) {
    NodoListaPtr precPtr, corrPtr, tempPtr;
    if (valore == (*tPtr)->dato) {
        tempPtr = *tPtr;
        *tPtr = (*tPtr)->proxPtr;
        free(tempPtr);
        return valore;
    } else {
        precPtr = *tPtr;
        corrPtr = (*tPtr)->proxPtr;
        while (corrPtr != NULL && corrPtr->dato != valore) {
            precPtr = corrPtr;
            corrPtr = corrPtr->proxPtr;
        }
        if (corrPtr != NULL) {
            tempPtr = corrPtr;
            precPtr->proxPtr = corrPtr->proxPtr;
            free(tempPtr);
            return valore;
        }
    }
    return '\0';
}

int listaVuota(NodoListaPtr tPtr) {
    return tPtr == NULL;
}

void stampaLista(NodoListaPtr corrPtr) {
    if (corrPtr == NULL) printf("Lista vuota.\n\n");
    else {
        printf("La lista è:\n");
        while (corrPtr != NULL) {
            printf("%c --> ", corrPtr->dato);
            corrPtr = corrPtr->proxPtr;
        }
    }
    printf("NULL\n\n");

}