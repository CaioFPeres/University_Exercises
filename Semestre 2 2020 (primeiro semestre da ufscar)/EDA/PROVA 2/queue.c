#include <stdlib.h>
#include "queue.h"

void initialize(queue *q) {
    q->first = q->last = 0;
}

void destroy(queue *q) {
    while(!empty(q))
        popFront(q);
}

void* front(queue *q) {
    if(!empty(q))
        return q->first->data;
    return 0;
}

void* back(queue *q) {
    if(!empty(q))
        return q->last->data;
    return 0;
}

void pushFront(queue* q, void* data){

    qnode *p = (qnode*)malloc(sizeof(qnode));
    p->data = data;
    p->next = 0;

    if(q->first){
        qnode *aux = q->first;
        q->first = p;
        q->first->next = aux;
    }
    else
        q->first = q->last = p;
}

void pushBack(queue *q, void* data) {
	
    qnode *p = (qnode*)malloc(sizeof(qnode));
    p->data = data;
    p->next = 0;
    if(q->last)
        q->last->next = p;
    else
        q->first = p;
    q->last = p;
    
}

void popFront(queue *q) {

    if(!empty(q)) {
        qnode *p = q->first;
        q->first = p->next;
        free(p);
        if(!q->first)
            q->last = 0;
    }
	
	
}

void popBack(queue *q) {

    if(!empty(q)) {
        qnode *p = q->last;
        qnode *aux = q->first;
        
        if(q->last == q->first){
            q->first = q->last = 0;
            free(q->first);
            return;
        }


        while(aux->next != q->last){
            aux = aux->next;
        }

        q->last = aux;
        free(p);

        if(!q->last)
            q->first = 0;
    }
		
}

int empty(queue *q) {
    return q->first == 0;
}
