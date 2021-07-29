#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct Elem {
	int ordem;
	struct Elem *ant;
	struct Elem *prox;	
	
}Elemento;

int ordem=0;
Elemento ***b;

Elemento *alocaNo(){
	ordem=ordem++;
	
	Elemento *aux = (Elemento *) malloc(sizeof(Elemento));
    aux->ant = NULL;
    aux->ordem = ordem;
	return aux;
};

void insereFinal(Elemento **lista){
	if((*lista)==NULL){ //lista vazia
        (*lista)->ant = alocaNo();
        *lista = (*lista)->ant;
    }
}

void circular(Elemento **a){
	***b=**a;
	
	while((*a)->ant != NULL){
		*a= (*a)->ant;
	}
	if((*a)->ant == NULL){
		(**b)->prox= *a;
	}
}

void chegada(Elemento **lista){
	if(ordem==10){
		printf("Estacionamento Cheio!");}
	else{
			if((*lista)->ant == NULL){
				insereFinal(*(&lista));
			}
		}	
	
}

void partida(Elemento **lista){
	
	int ordemdigitada;
	
	printf("Digite a ordem do carro na fila: ");
	scanf("%i", &ordemdigitada);
//	if(*(lista)->ordem != ordemdigitada){
//		*(lista)= *(lista)->ant;
//	}
//	else{
//		
//	}
//	
	
}

int main(int argc, char** argv) {
	char C;
	
	Elemento *lista= (Elemento*)malloc(sizeof(Elemento));
	lista->ordem= ordem;
	
	Elemento *a= lista;
	
	
	printf("Digite C ou P para chegada ou partida: ");
	scanf("%i", C);
	
	circular(&a);
	
	switch (C)
{
case 'c':
      chegada(&lista);
break;

case 'p':
      partida(&lista);
break;
}
	
	insereFinal(&lista);
	
	return 0;
}
