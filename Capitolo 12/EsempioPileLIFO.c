//
// Created by Leonardo Birardi on 29/12/2022.
//

#include <stdio.h>
#include <stdlib.h>


// struttura autoreferenziale
struct stackNode {
    int data; // il campo dati e' un int
    struct stackNode *nextPtr; // puntatore a stackNode
};

typedef struct stackNode StackNode; // sinonimo per struct stackNode
typedef StackNode *StackNodePtr; // sinonimo per StackNode*


// prototipi
void push(StackNodePtr *topPtr, int info);

int pop(StackNodePtr *topPtr);

int isEmpty(StackNodePtr topPtr);

void printStack(StackNodePtr currentPtr);

void instructions(void);


// la funzione main inizia l'esecuzione del programma
int main(void) {
    StackNodePtr stackPtr = NULL; // punta alla cima della pila
    int value; // valore int inserito dall'utente

    instructions(); // stampa il menu
    printf("%s", "? ");

    unsigned int choice; // scelta da menu da parte dell'utente
    scanf("%u", &choice);

    // finche' l'utente non inserisce 3
    while (choice != 3) {
        switch (choice) {
            // effettua un push di un valore nella pila
            case 1:
                printf("%s", "Enter an integer: ");
                scanf("%d", &value);
                push(&stackPtr, value);
                printStack(stackPtr);
                break;
                // effettua un pop di un valore dalla pila
            case 2:
                // se la pila non e' vuota
                if (!isEmpty(stackPtr)) {
                    printf("The popped value is %d.\n", pop(&stackPtr));
                }
                printStack(stackPtr);
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
    puts("Enter choice:\n"
         "1 to push a value on the stack\n"
         "2 to pop a value off the stack\n"
         "3 to end program");
}


// inserisci un nodo in cima alla pila
void push(StackNodePtr *topPtr, int info) {
    StackNodePtr newPtr = malloc(sizeof(StackNode));

    // inserisci il nodo in cima alla pila
    if (newPtr != NULL) {
        newPtr->data = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } else { // non c'e' spazio disponibile
        printf("%d not inserted. No memory available.\n", info);
    }
}


// rimuovi un nodo dalla cima della pila
int pop(StackNodePtr *topPtr) {
    StackNodePtr tempPtr; = *topPtr;
    int popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);
    return popValue;
}


// stampa la pila
void printStack(StackNodePtr currentPtr) {
    // se la pila e' vuota
    if (currentPtr == NULL) {
        puts("The stack is empty.\n");
    } else {
        puts("The stack is:");
        // finche' non si raggiunge la fine della pila
        while (currentPtr != NULL) {
            printf("%d --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL\n");
    }
}

// restituisci 1 se la pila e' vuota, altrimenti 0
int isEmpty(StackNodePtr topPtr) {
    return topPtr == NULL;
}