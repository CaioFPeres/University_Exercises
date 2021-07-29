#include <stdio.h>
#include <stdlib.h>

struct No{
    int chave;
    struct No* prox;
}; 
typedef struct No Elemento;


Elemento *alocaNo(int chave){
    Elemento *aux = (Elemento *) malloc(sizeof(Elemento));
    aux->prox = NULL;
    aux->chave = chave;
    return aux;
}

void imprimir(Elemento *lista){
	if(lista != NULL){
		printf("%i - ", lista->chave);
		imprimir(lista->prox);
	}
	
	
}

void insereFinal(Elemento **lista, int chave){
    if((*lista)==NULL){ //lista vazia
        *lista = alocaNo(chave);
        return;
    }
    else { //lista ja contem elementos
    	insereFinal(&(*lista)->prox, chave);
    
/*        Elemento *aux = alocaNo(chave);
        if((aux) == NULL) return;
        
        (*lista)->prox = aux;
        
        aux->prox= NULL;
        
        *lista = (*lista)->prox;*/
    }
}

void insereInicio(Elemento **lista, int chave){
    if((*lista)==NULL){ //lista vazia
        *lista = alocaNo(chave);
    }
    else { //lista ja contem Elementos
        Elemento *aux = alocaNo(chave);
        if((aux) == NULL) return;
        aux->prox = (*lista);
        *lista = aux;
    }
}

Elemento *buscaChave(Elemento *lista, int chave){
    if(lista == NULL) return NULL; //caso base
    if(lista->chave == chave) return lista;
    buscaChave(lista->prox, chave);
}

void removeFinal(Elemento **lista){
	Elemento *p;
	Elemento *p2=*lista;
	p = *lista;
	while(p->prox!=NULL){
		p2=p;
		p=p->prox;
	}
	free(p);
	p2->prox = NULL;
}

void removeInicio(Elemento **lista){
    Elemento *aux = (*lista)->prox;
    free((*lista));
    (*lista) = aux;
}

void removeChave(Elemento **lista, int chave){
    if((*lista) == NULL) return;    //lista vazia
    if((*lista)->chave == chave) removeInicio(&(*lista)); return;//primeiro Elemento
    Elemento *aux = (*lista);
    if(aux->prox->chave == chave){
        Elemento *maisUmAux;
        maisUmAux = aux->prox;
        if(maisUmAux->prox->prox == NULL){
            free(maisUmAux);
            aux->prox == NULL;
        }
        else{
            aux->prox == maisUmAux->prox;
            free(maisUmAux);
            maisUmAux == NULL;
        }
    }else   removeChave(&(*lista)->prox, chave);
}

void main(){
    Elemento *lista = NULL, *busca = NULL;

    insereFinal(&lista, 5);
    insereFinal(&lista, 3);
    insereFinal(&lista, 2);
    insereFinal(&lista, 1);
    removeFinal(&lista);
//    insereFinal(&lista, 1);// 1 3 5
    //printf("%d, %d, %d", lista->chave, lista->prox->chave, lista->prox->prox->chave);

	//while(lista && lista->prox != NULL){
 	imprimir(lista);
//    busca = buscaChave(lista, 5);
    //if(busca)   printf("\nEncontrado!");
/*    removeChave(&lista, 1);
    insereInicio(&lista, 1);
    removeChave(&lista, 3);
    insereInicio(&lista, 3);
    removeChave(&lista, 5);
    insereInicio(&lista, 5);
    printf("%d, %d, %d", lista->chave, lista->prox->chave, lista->prox->prox->chave);*/
}
