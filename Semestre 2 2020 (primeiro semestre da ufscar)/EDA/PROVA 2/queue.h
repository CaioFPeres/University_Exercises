#ifndef QUEUE_H
#define QUEUE_H

typedef struct qnode_ {
    void* data;
    struct qnode_ *next;
} qnode;

typedef struct {
    qnode *first, *last;
} queue;

void initialize(queue *q);

void destroy(queue *q);

void* front(queue *q);

void* back(queue *q);

void pushFront(queue *q, void* data);

void pushBack(queue *q, void* data);

void popFront(queue *q);

void popBack(queue *q);

int empty(queue *q);

#endif
