#include <stdlib.h>
#include "lista.h"

void inicializa( lista* l, int (*cmp)( lista_item i1, lista_item i2)) {
	lista_no* sentinela = (lista_no*) malloc(sizeof(lista_no));
	sentinela->prox = sentinela;
	sentinela->ant = sentinela;
	l->quantidade = 0;
	l->sentinela = sentinela;
	l->compara = cmp;

}


void destroi(lista* l) {
	while(!vazia(l))
		retira(l, elemento(primeiro(l)));
	free(l->sentinela);
}

int vazia(lista* l) {
	return l->sentinela->prox == l->sentinela;
}

void insere(lista* l, lista_item item) {
	lista_iterador it = procuraTeto(l,item);
	lista_no* novo = (lista_no*)malloc(sizeof(lista_no));
	novo->item = item;
	novo->prox = it.p;
	novo->ant = it.p->ant;
	it.p->ant = novo;
	novo->ant->prox = novo;
	l->quantidade++;
}

void retira(lista* l, lista_item item) {
	l->sentinela->item = item;
	lista_iterador li = primeiro(l);
	
	while(l->compara(item, li.p->item) != 0 ){
		proximo(&li);
	}
	
	while(!acabou(li) && l->compara(item, li.p->item) == 0){
		li.p->ant->prox = li.p->prox;
		li.p->prox->ant = li.p->ant;
		lista_no* n = li.p;
		proximo(&li);
		free(n);
		l->quantidade--;
		
	}

}

lista_iterador primeiro(lista* l) {
	lista_iterador it;
	it.l = l;
	it.p = l->sentinela->prox;
	return it;
}

lista_iterador ultimo(lista* l) {
	lista_iterador it;
	it.l = l;
	it.p = l->sentinela->ant;
	return it;
}
lista_item elemento(lista_iterador i) {
	return i.p->item;
}

int proximo(lista_iterador* i) {
	if( !acabou(*i) ) {
		i->p = i->p->prox;
		return 1;
	}
	return 0;
}

int anterior(lista_iterador* i) {
	if( !acabou(*i) ) {
		i->p = i->p->ant;
		return 1;
	}
	return 0;
}

int acabou(lista_iterador i) {
	return i.p == i.l->sentinela;
}

lista_iterador procuraPrimeiro(lista* l, lista_item item) {
	lista_iterador it = procuraTeto(l,item);
	if(!acabou(it) && l->compara(elemento(it),item) != 0 ) {
		it.p = l->sentinela;
	}
	return it;
}

lista_iterador procuraTeto(lista* l, lista_item item) {
	l->sentinela->item = item;
	lista_iterador it = primeiro(l);
	while( l->compara( elemento(it), item ) == -1 ) {
		proximo(&it);
	}
	return it;

}

lista_iterador procuraPiso(lista* l, lista_item item) {
	l->sentinela->item = item;
	lista_iterador it = ultimo(l);
	while( l->compara( elemento(it), item ) == 1 ) {
		anterior(&it);
	}
	return it;
}
