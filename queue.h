#ifndef QUEUE_H
#define QUEUE_H

// struct to a queue
typedef struct queueTag qNode;

struct queueTag {
    int data;
    qNode *next;
};

//functions
void enqueue(qNode **queue, qNode **rear, int data);
void destroyQueue(qNode *queue);
void printQueue(qNode *queue, int format);

#endif
