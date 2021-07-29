#include <iostream>
#include <stdlib.h>

struct TNoABP
{
	int chave;
	struct TNoABP* esq;
	struct TNoABP* dir;
};

typedef struct TNoABP TNoABP;

//por saulo;
//insere um novo nó de valor chave igual a k e devolve endereço deste no. Toma como entrada o endereço de memoria do ponteiro que representa a (sub) arvore.
//devolve NULL caso não haja espaço de memoria.


TNoABP *insereABP(TNoABP *r, int k){
	if (r == NULL)
	r = (TNoABP *)malloc(sizeof(TNoABP));
	if(r == NULL)
	return NULL;
	r->chave = k;
	r->esq = NULL;
	r->dir = NULL;
	return r;
	
}

TNoABP *buscaABP(TNoABP *r, int k){
	if (r == NULL)
		return NULL;
	if (r->chave == k)
		return r;
	if (r->chave < k)
		buscaABP(r->dir, k);

while (r!=NULL){
	if (r->chave == k)
	return r;
	if(r->chave<k){
		return buscaABP(r->dir, k);
	
	}
}
}

int main(int argc, char** argv) {
	TNoABP *arv1 = NULL;
	TNoABP *noCriado= insereABP(arv1, 96);
	return 0;
	
	
	
	return 0;
}
