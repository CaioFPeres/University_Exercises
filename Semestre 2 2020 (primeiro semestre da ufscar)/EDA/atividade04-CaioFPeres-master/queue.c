#include <stdlib.h>
#include "queue.h"

void initialize(queue *q) {
	q->first = q->last = 0;
}

void destroy(queue *q) {
    while(!empty(q))
        pop(q);
}

void* front(queue *q) {
    if(!empty(q))
        return q->first->data;
    return 0;
}

void push(queue *q, void* data) {
	
    qnode *p = (qnode*)malloc(sizeof(qnode));
    p->data = data;
    p->next = 0;
    if(q->last)
        q->last->next = p;
    else
        q->first = p;
    q->last = p;
    
}

void pop(queue *q) {

    if(!empty(q)) {
        qnode *p = q->first;
        q->first = p->next;
        free(p);
        if(!q->first)
            q->last = 0;
    }
	
	
}

int empty(queue *q) {
    return q->first == 0;
}
