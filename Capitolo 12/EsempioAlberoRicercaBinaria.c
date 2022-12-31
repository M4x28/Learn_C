//
// Created by Leonardo Birardi on 29/12/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// struttura autoreferenziale
struct treeNode {
    struct treeNode *leftPtr; // puntatore al sottoalbero sinistro
    int data; // valore del nodo
    struct treeNode *rightPtr; // puntatore al sottoalbero destro
};

typedef struct treeNode TreeNode; // sinonimo per struct treeNode
typedef TreeNode *TreeNodePtr; // sinonimo per TreeNode*


// prototipi
void insertNode(TreeNodePtr *treePtr, int value);

void inOrder(TreeNodePtr treePtr);

void preOrder(TreeNodePtr treePtr);

void postOrder(TreeNodePtr treePtr);


// la funzione main inizia l'esecuzione del programma
int main(void) {
    TreeNodePtr rootPtr = NULL; // albero inizialmente vuoto
    srand(time(NULL));
    puts("The numbers being placed in the tree are:");

    // inserisci nell'albero valori a caso tra 0 e 14
    for (unsigned int i = 1; i <= 10; ++i) {
        int item = rand() % 15;
        printf("%3d", item);
        insertNode(&rootPtr, item);
    }

    // attraversa l'albero in pre-ordine
    puts("\n\nThe preOrder traversal is:");
    preOrder(rootPtr);
    // attraversa l'albero in ordine
    puts("\n\nThe inOrder traversal is:");
    inOrder(rootPtr);
    // attraversa l'albero in post-ordine
    puts("\n\nThe postOrder traversal is:");
    postOrder(rootPtr);
}


// inserisci un nodo nell'albero
void insertNode(TreeNodePtr *treePtr, int value) {
    // se l'albero e' vuoto
    if (*treePtr == NULL) {
        *treePtr = malloc(sizeof(TreeNode)); // se la memoria e' stata allocata, allora memorizza il valore
        if (*treePtr != NULL) {
            (*treePtr)->data = value;
            (*treePtr)->leftPtr = NULL;
            (*treePtr)->rightPtr = NULL;
        } else {
            printf("%d not inserted. No memory available.\n", value);
        }
    } else { // l'albero non e' vuoto
        // il valore da inserire e' minore del valore nel nodo corrente
        if (value < (*treePtr)->data) {
            insertNode(&((*treePtr)->leftPtr), value);
        }
        // il valore da inserire e' maggiore del valore nel nodo corrente
        else if (value > (*treePtr)->data) {
            insertNode(&((*treePtr)->rightPtr), value);
        } else { // i valori duplicati vengono ignorati
            printf("%s", "dup");
        }
    }
}


// inizia l'attraversamento in ordine dell'albero
void inOrder(TreeNodePtr treePtr) {
    // se l'albero non e' vuoto, allora attraversalo
    if (treePtr != NULL) {
        inOrder(treePtr->leftPtr);
        printf("%3d", treePtr->data);
        inOrder(treePtr->rightPtr);
    }
}


// inizia l'attraversamento in pre-ordine dell'albero
void preOrder(TreeNodePtr treePtr) {
    // se l'albero non e' vuoto, allora attraversalo
    if (treePtr != NULL) {
        printf("%3d", treePtr->data);
        preOrder(treePtr->leftPtr);
        preOrder(treePtr->rightPtr);
    }
}


// inizia l'attraversamento in post-ordine dell'albero
void postOrder(TreeNodePtr treePtr) {
    // se l'albero non e' vuoto, allora attraversalo
    if (treePtr != NULL) {
        postOrder(treePtr->leftPtr);
        postOrder(treePtr->rightPtr);
        printf("%3d", treePtr->data);
    }
}