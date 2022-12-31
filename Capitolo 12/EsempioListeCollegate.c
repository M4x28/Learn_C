//
// Created by Leonardo Birardi on 29/12/2022.
//

#include <stdio.h>
#include <stdlib.h>


// struttura autoreferenziale
struct listNode {
    char data; // ogni listNode contiene un carattere
    struct listNode *nextPtr; // puntatore al nodo successivo
};
typedef struct listNode ListNode; // sinonimo per struct listNode
typedef ListNode *ListNodePtr; // sinonimo per ListNode*


// prototipi
void insert(ListNodePtr *sPtr, char value);
char delete(ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);


int main(void) {
    ListNodePtr startPtr = NULL; // inizialmente non vi sono nodi
    char item; // char inserito dall'utente

    instructions(); // stampa il menu
    printf("%s", "? ");

    unsigned int choice; // scelta dell'utente
    scanf("%u", &choice);

    // ripeti il ciclo finche' l'utente non sceglie 3
    while (choice != 3) {
        switch (choice) {
            case 1:
                printf("%s", "Enter a character: ");
                scanf("\n%c", &item);
                insert(&startPtr, item); // inserisci l'elemento nella lista
                printList(startPtr);
                break;
            case 2: // cancella un elemento
                // se la lista non è vuota
                if (!isEmpty(startPtr)) {
                    printf("%s", "Enter character to be deleted: ");
                    scanf("\n%c", &item);
                    // se il carattere viene trovato, rimuovilo
                    if (delete(&startPtr, item)) { // rimuovi l'elemento
                        printf("%c deleted.\n", item);
                        printList(startPtr);
                    } else {
                        printf("%c not found.\n\n", item);
                    }
                } else {
                    puts("List is empty.\n");
                }
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
void instructions(void)
{
puts("Enter your choice:\n"
" 1 to insert an element into the list.\n"
" 2 to delete an element from the list.\n"
" 3 to end.");
}


// inserisci un nuovo valore nella lista ordinata
void insert(ListNodePtr *sPtr, char value) {
    ListNodePtr newPtr = malloc(sizeof(ListNode)); // crea il nodo

    if (newPtr != NULL) { // se c'e' spazio disponibile
        newPtr->data = value; // inserisci value nel nodo
        newPtr->nextPtr = NULL; // il nodo non è collegato ad altri nodi
        ListNodePtr previousPtr = NULL;
        ListNodePtr currentPtr = *sPtr;

        // ripeti il ciclo per trovare la posizione corretta nella lista
        while (currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr; // va avanti ...
            currentPtr = currentPtr->nextPtr; // ... al nodo successivo
        }

        // inserisci il nuovo nodo all'inizio della lista
        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } else { // inserisci il nuovo nodo tra previousPtr e currentPtr
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    } else {
        printf("%c not inserted. No memory available.\n", value);
    }
}


// cancella un elemento della lista
char delete(ListNodePtr *sPtr, char value) {
    // cancella il primo nodo se viene trovata una corrispondenza
    if (value == (*sPtr)->data) {
        ListNodePtr tempPtr = *sPtr; // aggancia il nodo da rimuovere
        *sPtr = (*sPtr)->nextPtr; // sfila il nodo
        free(tempPtr); // libera il nodo
        return value;
    }
    else {
        ListNodePtr previousPtr = *sPtr;
        ListNodePtr currentPtr = (*sPtr)->nextPtr;

        // ripeti il ciclo per trovare la posizione corretta nella lista
        while (currentPtr != NULL && currentPtr->data != value) {
            previousPtr = currentPtr; // va avanti ...
            currentPtr = currentPtr->nextPtr; // ... al nodo successivo
        }

        // cancella il nodo a cui punta currentPtr
        if (currentPtr != NULL) {
            ListNodePtr tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        }
    }
    return '\0';
}


// restituisci 1 se la lista e' vuota, altrimenti 0
int isEmpty(ListNodePtr sPtr) {
    return sPtr == NULL;
}


// stampa la lista
void printList(ListNodePtr currentPtr) {
    // se la lista e' vuota
    if (isEmpty(currentPtr)) {
        puts("List is empty.\n");
    } else {
        puts("The list is:");
        // finche' non si raggiunge la fine della lista
        while (currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL\n");
    }
}