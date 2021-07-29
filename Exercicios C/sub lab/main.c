#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct site{
	char link[100];
	struct site *prox;
	struct site *ant;
}sites;

sites *aloca(char link[100]){
    sites *aux = (sites*) malloc(sizeof(sites));
    aux->prox = NULL;
    aux->link = link;
    return aux;
}

sites *buscaSite(sites *P, char link[100]){
    if(P == NULL) return NULL;
    if(strcmp((*P)->link), link) return P;
    buscaSite(P->prox, link);
}

sites InserirSite (sites *P, sites **I, char link[100]){
	    if((*P)==NULL){
        *P = aloca(link);
}else {
		*I= P;
        site *aux = aloca(link);
        if((aux) == NULL) return;
        
        (*P)->prox = aux;
        
        aux->prox= NULL;
        
        *P = (*P)->prox;
}}

void remove(sites *P, char link[100]){
    *P = buscaSite(*P, link);
   	(*P)->ant->prox = (*P)->prox;
    free(*P);
}

int main() {
	int sw;
	sites *P;
	sites *I;
	char link[100];
	
	do{
		printf("Digite 1 para inserir site, 2 para buscar site, 3 para remover site, 4 para mostrar os 10 mais buscados, 5 para mostrar as 10 buscas mais recentes");
	switch(sw){
	case 1:
		printf("Digite o nome do site a ser inserido na lista: ");
		scanf("%s", link);
		InserirSite(*P,*I, link);
	case 2:
		buscaSite(P,link);
	case 3:
		printf("Digite o site que quer remover: ");
		scanf("%s", link);
		remove(P,link);
	case 4:
		
	return 0;
}
}while(1==1);
}
