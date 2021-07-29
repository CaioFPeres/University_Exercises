#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "queue.c"

typedef struct node_ {
	int data;
	struct node_ *dir, *esq;
} node;


node* inserir( node* p, int dados ) {
	if( !p ) {
		node* novo = (node*)malloc(sizeof(node));
		novo->data = dados;
		novo->esq = novo->dir = 0;
		return novo;
	} else if (dados < p->data ) {
		p->esq = inserir( p->esq, dados);
	} else if (dados > p->data ) {
		p->dir = inserir( p->dir, dados);
	} else { //repetido
		p->data = dados; // atualizando outros campos
	}
	return p;
}

void destruir( node *p ) {
	
	if( p ) {
	    destruir(p->esq);
	
	    destruir(p->dir);
	
		free(p);
	}
}

void pos_order( node *p, void (*process)(int dado) ) {
	
	if( p ) {
	    pos_order(p->esq, process);
	
	    pos_order(p->dir, process);
	
		process( p->data );
	}
}

void pre_order( node *p, void (*process)(int dado) ) {
	if( p ) {
		process( p->data );

	    pre_order(p->esq, process);

	    pre_order(p->dir, process);
	}
}

void in_order( node *p, void (*process)(int dado) ) {
	
	if( p ) {
	    in_order(p->esq, process);

		process( p->data );

	    in_order(p->dir, process);
	}
}


void in_level( node *p, void (*process)(int dado)) {

	queue q;
	initialize(&q);
	push(&q,p);


	while( !empty(&q) ) {
	
		node *e = front(&q);
		process( e->data);
    	pop(&q);


    	if(e->esq != NULL)
			push(&q, e->esq);
            
        if ( e->dir != NULL )
            push(&q, e->dir);

	  }


	destroy(&q);

}

	


void print(int dado) {
    printf(" %d", dado);
}

int main() {

	int n,a;
	scanf("%d", &n);
	
	node* raiz = 0;
	
	int i;
	
	for(i=0;i<n; i++) {
		scanf("%d", &a);
		raiz = inserir(raiz,a);
	}
	
	printf("Pr.:");
	pre_order(raiz, print);
	printf("\n");
	printf("In.:");
	in_order(raiz, print);
	printf("\n");
	printf("Po.:");
	pos_order(raiz, print);
	printf("\n");
	printf("Ni.:");
	in_level(raiz, print);
	printf("\n");

    destruir(raiz);
	
	return 0;
}
