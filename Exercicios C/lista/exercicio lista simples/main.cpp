#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef int TipoChave;
typedef int TipoValor;

struct TipoLista_Encadeada {
TipoChave chave;
TipoValor valorQualquer;
struct TipoLista_Encadeada *prox;
};

typedef struct TipoLista_Encadeada TipoListaEncadeada;

TipoListaEncadeada *insereInicioListaEncadeada (TipoListaEncadeada **prim, TipoChave chave, TipoValor valor){
	
	
	if(*prim == NULL){
		
		*prim = (TipoListaEncadeada *)malloc(sizeof(TipoListaEncadeada));
	
		if(*prim == NULL) return NULL;
		
		(*prim)->chave=chave;
		(*prim)->valorQualquer= valor;
		
		return *prim;
		
	}
	
	
	TipoListaEncadeada *aux;
	aux= (TipoListaEncadeada *)malloc(sizeof(TipoListaEncadeada));
	if(aux == NULL){
		return *prim;
	}
	
	aux->chave= chave;
	aux->valorQualquer= valor;
	aux->prox= *prim;
	(*prim)=aux;
	return *prim;
}

int main(int argc, char** argv) {
	
	TipoListaEncadeada *p= NULL;
	
	p = insereInicioListaEncadeada (&p, 10, 50);
	p = insereInicioListaEncadeada (&p, 22, 32);
	p = insereInicioListaEncadeada (&p, 28, 37);
	
	printf("%d\n", p->prox->prox->chave);
	

	return 0;
}
