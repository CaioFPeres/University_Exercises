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

void swap (qnode *i1, qnode *i2){

    qnode aux;
    aux = *i1;
    *i1 = *i2;
    *i2 = aux;
    printf("%i ", i2->data);

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

void pushFrontPrioridade(queue* q, void* data){

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

    qnode *it = q->first;

    while( it->next != NULL){
      if(it->data > it->next->data){
            swap(it, it->next);
        }
        it = it->next;
    }


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
