#include <stdlib.h>
#include "pilha.h"

pilha inicializa() {
	
    pilha p = (pilha)malloc(sizeof(struct pilha_struct));
	p->topo = NULL;
	p->quantidade = 0;

	return p;

}

void destroi(pilha p) {

	if(!vazia(p)){

	  	pilha_no proxTopo;
		
		while(p->topo != NULL){
	   		
	   		proxTopo = p->topo->prox;
			free(p->topo);
			
			p->topo = proxTopo;
		}
		//p = NULL;
		free(p);
	}
}


int vazia(pilha p) {
    
    if(p->topo == NULL)
    	return 1;
	else
    	return 0;
}


unsigned tamanho(pilha p) {
    return p->quantidade;
}

int empilha(pilha p, pilha_item item) {
    
    pilha_no aux = p->topo;
	p->topo = (pilha_no)malloc(sizeof(struct pilha_no_struct));
	p->quantidade++;
	p->topo->item = item;
	p->topo->prox = aux;

    return 0;
}



int desempilha_retorna(pilha p, pilha_item* item) {
    
    if(!vazia(p)){
		pilha_no aux = p->topo->prox;
		item = &p->topo->item;
		free(p->topo);
		p->topo = aux;
		p->quantidade--;
		return 1;
}
else{
    return 0;
}
}

int desempilha(pilha p) {
    if(!vazia(p)){
		pilha_no aux = p->topo->prox;
		free(p->topo);
		p->topo = aux;
		p->quantidade--;
		return 1;
	}
	else{
 		return 0;		
	}

}

int topo(pilha p, pilha_item* item) {
    
    if(!vazia(p)){
    	
		*item = p->topo->item;
		return 1;
}
else{
    return 0;
}
}
