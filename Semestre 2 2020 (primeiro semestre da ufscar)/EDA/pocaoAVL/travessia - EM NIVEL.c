#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int chave;
	struct No *dir;
	struct No *esq;
}No;

void preOrdem(No *raiz){
	
    if (raiz != NULL)  
    { 
      printf( " %d", raiz->chave);
      preOrdem(raiz->esq);
      preOrdem(raiz->dir);
     }
}

void emOrdem(No *raiz){
	
    if (raiz != NULL)  
    { 
      emOrdem(raiz->esq); 
      printf( " %d", raiz->chave); 
      emOrdem(raiz->dir);  
    } 
} 

void posOrdem(No *raiz){
	
    if (raiz != NULL)  
    { 
       posOrdem( raiz->esq); 
       posOrdem( raiz->dir);  
       printf( " %d", raiz->chave); 
    } 
} 

int altura(No *raiz) {
    if (raiz == NULL) {
        return -1;
    }

    int esquerda = altura(raiz->esq);
    int direita = altura(raiz->dir);

    if (esquerda > direita) {
        return esquerda + 1;
    } else {
        return direita + 1;
    }
}

void printEmNivel(No *raiz, int level)
{ 
    if (raiz == NULL) 
        return; 
    if (level == 1)
        printf(" %d", raiz->chave);
    else if (level > 1) 
    { 
        printEmNivel(raiz->esq, level-1);
        printEmNivel(raiz->dir, level-1);
    } 
} 

void printOrdemNivel(No *raiz)
{ 
    int h = altura(raiz)  + 1; 
    int i; 
    for (i=1; i<=h; i++) 
    { 
        printEmNivel(raiz, i);
    } 
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
		if(valor > ant->chave)
			ant->dir = novo;
		else
			ant->esq = novo;
	}
	
}


int main(int argc, char** argv) {
	
	int valor;
	No *raiz= NULL;
	int a, l, c, k, j;
	
	
	scanf("%i", &l);
	for(c=0;c<l;c++){
	scanf("%i", &a);
	insereArvBinIterativa(&raiz, a);}
	
	//printf("%i", raiz->chave);
	
	//impressoes
	printf("Pr.:");
	preOrdem(raiz);
	printf("\nIn.:");
	emOrdem(raiz);
	printf("\nPo.:");
	posOrdem(raiz);
	printf("\nNi.:");
	printOrdemNivel(raiz);
	printf("\n");
	
	return 0;
}
