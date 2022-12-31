//
// Created by Leonardo Birardi on 29/12/2022.
//

#include <stdio.h>
#include <stdlib.h>


// struttura autoreferenziale
struct queueNode {
    char data; // il campo dati e' un char
    struct queueNode *nextPtr; // puntatore a queueNode
};

typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

// prototipi di funzione
void printQueue(QueueNodePtr currentPtr);

int isEmpty(QueueNodePtr headPtr);

char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr);

void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value);

void instructions(void);


// la funzione main inizia l'esecuzione del programma
int main(void) {
    QueueNodePtr headPtr = NULL; // inizializza headPtr
    QueueNodePtr tailPtr = NULL; // inizializza tailPtr
    char item; // char inserito dall'utente

    instructions(); // stampa il menu
    printf("%s", "? ");

    unsigned int choice; // scelta da menu da parte dell'utente
    scanf("%u", &choice);

    // finche' l'utente non inserisce 3
    while (choice != 3) {
        switch (choice) {
            // metti in coda un valore
            case 1:
                printf("%s", "Enter a character: ");
                scanf("\n%c", &item);
                enqueue(&headPtr, &tailPtr, item);
                printQueue(headPtr);
                break;
            // estrai dalla coda un valore
            case 2:
                // se la coda non e' vuota
                if (!isEmpty(headPtr)) {
                    item = dequeue(&headPtr, &tailPtr);
                    printf("%c has been dequeued.\n", item);
                }
                printQueue(headPtr);
                break;
            default:
                puts("Invalid choice.\n");
                instructions();
                break;
        }
        printf("%s", "? ");

        scanf("%u", &choice);
    }
    puts("End of run.");
}


// stampa le istruzioni per l'utente
void instructions(void) {
    printf("Enter your choice:\n"
           " 1 to add an item to the queue\n"
           " 2 to remove an item from the queue\n"
           " 3 to end\n");
}


// inserisci un nodo in fondo alla coda
void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value) {
    QueueNodePtr newPtr = malloc(sizeof(QueueNode));

    if (newPtr != NULL) { // c'e' spazio disponibile?
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        // se la coda e' vuota, inserisci il nodo in testa
        if (isEmpty(*headPtr)) {
            *headPtr = newPtr;
        } else {
            (*tailPtr)->nextPtr = newPtr;
        }
        *tailPtr = newPtr;
    } else {
        printf("%c not inserted. No memory available.\n", value);
    }
}


// rimuovi un nodo dalla testa della coda
char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr) {
    char value = (*headPtr)->data;
    QueueNodePtr tempPtr = *headPtr;
    *headPtr = (*headPtr)->nextPtr;

    // se la coda e' vuota
    if (*headPtr == NULL) {
        *tailPtr = NULL;
    }
    free(tempPtr);
    return value;
}


// restituisci 1 se la coda e' vuota, altrimenti 0
int isEmpty(QueueNodePtr headPtr) {
    return headPtr == NULL;
}


// stampa la coda
void printQueue(QueueNodePtr currentPtr) {
    // se la coda e' vuota
    if (currentPtr == NULL) {
        puts("Queue is empty.\n");
    } else {
        puts("The queue is:");
        // finche' non si raggiunge la fine della coda
        while (currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL\n");
    }
}