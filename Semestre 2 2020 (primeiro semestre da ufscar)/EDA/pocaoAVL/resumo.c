#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int chave;
	struct No *dir;
	struct No *esq;
}No;

/*No *removeArvBin(No **raiz, int valor){
	if(raiz == NULL) return 0;
	No *atual = *raiz;
	No *ant = NULL;
	while(atual != NULL){
		if(valor == atual->chave){
			if(atual == *raiz)
				*raiz = removeAtual(&atual);
			else
				if(ant->dir == atual)
					ant->dir = removeAtual(atual);
				else
					ant->esq = removeAtual(atual);
		}
		return 1;
	}
	ant = atual;
	if(valor> atual->chave)
		atual = atual->dir;
	else
		atual = atual->esq;
	
}

No *removeAtual(No **atual){
	No *no1, *no2;
	if(atual->esq == NULL){
		no2 = atual->dir;
		free(atual);
		return no2;
	}
	no1 = atual;
	no2 = atual->esq;
	while(no2->dir != NULL){
		no1 = no2;
		no2 = no2->dir;
	}
	
	if(no1 != atual){
		no1->dir = no2->esq;
		no2->esq = atual->esq;
	}
	no2->dir = atual->dir;
	free(atual);
	return no2;
}*/

No *buscaArvBinIterativa(No *raiz, int k){
	
	No *atual = raiz;
	No *ant = NULL;
		
	while(atual != NULL){
		ant = atual;
		
		if(k == atual->chave)
			return atual;
			
		if(k>atual->chave)
			atual = atual->dir;
		else
			atual = atual->esq;
		
		if(atual == NULL)
			return 0;
	}
	return 0;
	
}

No *insereArvBinIterativa(No **raiz, int valor){
	
	No *novo;
	novo = (No*)malloc(sizeof(No));
	//if(novo == NULL);
	//	return 0;
	novo->chave = valor;
	novo->dir = NULL;
	novo->esq = NULL;
	
	if(*raiz == NULL){
		*raiz = novo;
		}
	else{
		No *atual = *raiz;
		No *ant = NULL;
		
		while(atual != NULL){
			ant = atual;
			if(valor == atual->chave){
				free(novo);
				return 0; //elemento ja existe
			}
			if(valor > atual->chave)
				atual = atual->dir;
			else
				atual = atual->esq;
			}
		atual = novo;
	}
	
}


int main(int argc, char** argv) {
	int valor;
	No *raiz= NULL;
	No *p;
	int o;
	
	while(1==1){
	printf("Digite 1 para inserir, 2 para buscar valor: ");
	scanf("%i", &o);
	switch(o){
	case 1:
		printf("\nDigite valor a ser inserido na arvore: ");
		scanf("%i", &valor);
		p = insereArvBinIterativa(&raiz, valor);
		if(p == 0)
		printf("Elemento ja existe.\n\n");
		else
		printf("Inserido.\n\n");
	break;
		
		
	case 2:
		printf("\nDigite valor a ser buscado na arvore: ");
		scanf("%i", &valor);
		p = buscaArvBinIterativa(raiz, valor);
		if(p == 0)
			printf("Elemento nao encontrado!\n\n");
		else
			printf("Elemento encontrado!\n\n");
	break;
}
}
	return 0;
}

