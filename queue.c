#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

//definitions


/* Add the the back */
void enqueue(qNode **queue, qNode **rear, int data){
    qNode *new = malloc(sizeof(queue));
    if(!new){
        printf("Error with creating memory");
        exit(100);
    }
    // no duplicates!
    if(*rear && (*rear)->data == data){
        return;
    }
    
    // populate memory with data
    new->data = data; new->next = NULL;

    // check for empty queue
    if(*queue == NULL) *queue = new;
    else (*rear)->next = new;

    *rear = new;
}

/* Print the queue from front to last */
void printQueue(qNode *queue, int format){
    int i = 1; // only 10 elements per line
    while(queue != NULL){
        if( i % 10 == 0 )
            printf("\n%*s", format, ""); // formatting
        printf("%d  ", queue->data);
        queue = queue->next;
        i++;
    }
}

/* Free the queue from memory. */
void destroyQueue(qNode *queue){
    qNode *walker = queue;
    while(walker != NULL){
        walker = walker->next;
        
        //free the node and move to the next
        free(queue);
        queue = walker;
    }
} 














        
