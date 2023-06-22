//
// Created by Leonardo Birardi  on 20/04/2023.
//

#include<stdio.h>
#include<stdlib.h>

/* self-referential structure */
struct stackNode {
    int data;                  /* define data as an int */
    struct stackNode *nextPtr; /* stackNode pointer */
}; /* end structure stackNode */

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

/* prototypes */
void push(StackNodePtr *topPtr, int info);

int pop(StackNodePtr *topPtr);

int isEmpty(StackNodePtr topPtr);

void printStack(StackNodePtr currentPtr);

void instructions(void);


/* function main begins program execution */
int main() {
    StackNodePtr stackPtr = NULL; /* points to stack top */
    int choice;                   /* user's menu choice */
    int value;                    /* int input by user */

    instructions();
    printf("2 ");
    scanf("%d", &choice);

    /* while user does not enter 3 */
    while (choice != 3) {
        switch (choice) {
            /* push value onto stack */
            case 1:
                printf("Enter an integer: ");
                scanf("%d", &value);
                push(&stackPtr, value);
                printStack(stackPtr);
                break;
                /* pop value off stack */
            case 2:
                /* if stack is not empty */
                if (!isEmpty(stackPtr)) {
                    printf("The popped value is %d.\n", pop(&stackPtr));
                } /* end if */
                printStack(stackPtr);
                break;
            default:
                printf("Invalid choice.\n\n");
                instructions();
                break;
        } /* end switch */

        printf("? ");
        scanf("%d", &choice);
    } /* end while */

    printf("End of run.\n");
    return 0; /* indicates successful termination */
} /* end main */

void instructions(void) {
    printf("Enter choice:\n"
           "1 to push a value on the stack\n"
           "2 to pop a value off the stack\n"
           "3 to end program\n");
} /* end function instructions */

/* Insert a node at the stack top */
void push(StackNodePtr *topPtr, int info) {
    StackNodePtr newPtr; /* pointer to new node */
    newPtr = malloc(sizeof(StackNode));
    /* insert the node at stack top */
    if (newPtr != NULL) {
        newPtr->data = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } else {
        /* no space available */
        printf("%d not inserted. No memory available.\n", info);
    } /* end else */
} /* end function push */

/* Remove a node from the stack top */
int pop(StackNodePtr *topPtr) {
    StackNodePtr tempPtr; /* temporary node pointer */
    int popValue; /* node valve */
    tempPtr = *topPtr;
    popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);
    return popValue;
} /* end function pop */

/* Print the stack */
void printStack(StackNodePtr currentPtr) {
    /* if stack is empty */
    if (currentPtr == NULL) {
        printf("The stack is empty.\n\n");
    } /* end if */
    else {
        printf("The stack is:\n");
        /* while not the end of the stack */
        while (currentPtr != NULL) {
            printf("%d --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        } /* end while */
        printf("NULL\n\n");
    } /* end else */
} /* end function printList */

/* Return 1 if the stack is empty, O otherwise */
int isEmpty(StackNodePtr topPtr) {
    return topPtr == NULL;
} /* end function isEmpty */
