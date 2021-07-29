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
//insere um novo n� de valor chave igual a k e devolve endere�o deste no. Toma como entrada o endere�o de memoria do ponteiro que representa a (sub) arvore.
//devolve NULL caso n�o haja espa�o de memoria.


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
