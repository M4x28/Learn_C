//
// Created by Leonardo Birardi on 24/04/2023.
//

#include <stdio.h>
#include <stdlib.h>

/* self-referential structure */
struct queueNode {
    char data; /* define data as a char */
    struct queueNode *nextPtr; /* queueNode pointer */
}; /* end structure queueNode */

typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

/* function prototypes */
void printQueue(QueueNodePtr currentPtr);

int isEmpty(QueueNodePtr headPtr);

char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr);

void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value);

void instructions(void);

/* function main begins program execution */
int main() {
    QueueNodePtr headPtr = NULL; /* initialize headPtr */
    QueueNodePtr tailPtr = NULL; /* initialize tailPtr */
    int choice;                  /* user's menu choice */
    char item;                   /* char input by user */

    instructions(); /* display the menu */
    printf("? ");
    scanf("%d", &choice);

    /* while user does not enter 3 */
    while (choice != 3) {
        switch (choice) {
            /* enqueue value */
            case 1:
                printf("Enter a characti.r: scanf( r%c", &item);
                enqueue(&headPtr, &tailPtr, item);
                printQueue(headPtr);
                break;
                /* dequeue value */
            case 2:
                /* if queue is not empty */
                if (!isEmpty(headPtr)) {
                    item = dequeue(&headPtr, &tailPtr);
                    printf("%c has been dequeued.\n", item);
                } /* end if */
                printQueue(headPtr);
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

/* display program instructions to user */
void instructions(void) {
    printf("Enter your choice:\n" "1 to add an item to the queue\n" "2 to remove an item from the queue\n" "3 to end\n");
} /* end function instructions */

/* insert a node a queue tail */
void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value) {
    QueueNodePtr newPtr; /* pointer to new node */
    newPtr = malloc(sizeof(QueueNode));

    if (newPtr != NULL) {
        /* is space available */
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        /* if empty, insert node at head */
        if (isEmpty(*headPtr)) {
            *headPtr = newPtr;
        } /* end if */
        else {
            (*tailPtr)->nextPtr = newPtr;
        } /* end else */
        *tailPtr = newPtr;
    } /* end if */
    else {
        printf("%c not inserted. No memory available.\n", value);
    } /* end else */

} /* end function enqueue */

/* remove node from queue head */
char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr) {
    char value; /* node value */
    QueueNodePtr tempPtr; /* temporary node pointer */
    value = (*headPtr)->data;
    tempPtr = *headPtr;
    *headPtr = (*headPtr)->nextPtr;

    /* if queue is empty */
    if (*headPtr == NULL) {
        *tailPtr = NULL;
    } /* end if */
    free(tempPtr);
    return value;
} /* end function dequeue */

/* Return l if the list is empty, O otherwise */
int isEmpty(QueueNodePtr headPtr) {
    return headPtr == NULL;
} /* end function isEmpty */

/* Print the queue */
void printQueue(QueueNodePtr currentPtr) {
    /* if queue is empty */
    if (currentPtr == NULL) {
        printf("Queue is empty.\n\n");
    } /* end if */
    else {
        printf("The queue is:\n");
        /* while not end of queue */
        while (currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        } /* end while */
        printf("NULL\n\n");
    } /* end else */
} /* end function printQueue */
