#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct av{
	int i;
	int passageiros;
	struct av *prox;
}aviao;

int i=1;

aviao aloca(aviao **p, aviao **p2, int passageiros){
	if(*p == NULL){
		aviao *aux=(aviao*)malloc(sizeof(aviao));
		*p= aux;
		(*p)->i=i;
		(*p)->passageiros=passageiros;
		*p2= *p;
		*p=(*p)->prox;
		
	}
	i++;
}

aviao decolagem(aviao **p2, aviao **p){
	*p= (*p2)->prox;
	(*p2)= NULL;
	free(p2);
}

aviao *divisao(aviao **p2, aviao **p3, aviao **p4){
	int maior;
	*p3=*p2;
	maior= (*p2)->passageiros;
	while((*p2)->prox !=NULL){
	*p2= (*p2)->prox;
	if((*p2)->passageiros > maior){
		maior= (*p2)->passageiros;
	}
}
	*p2=*p3;
	while((*p2)->passageiros!=maior){
		*p2=(*p2)->prox;
	}
	*p4=(*p2)->prox;
	return (*p4);
}

int main(int argc, char** argv) {
	aviao *p;
	aviao *p2;
	aviao *p3;
	aviao *p4;
	
	int w=1;
	int passageiros;
	int sw;
	int j;
	
	do{
		printf("\nDigite 1 para adicionar aviao a fila, 2 para ver o numero de avioes, 3 para decolar o primeiro aviao da fila, 4 para listar o identificador de todos os avioes da fila, 5 para dividir a fila ou 0 para sair: ");
		scanf("%i", &sw);
	switch(sw){
	case 1:
		printf("Digite numero de passageiros: ");
		scanf("%i", &passageiros);
	aloca(&p, &p2, passageiros);
	break;
	case 2:
		printf("Numero de avioes: %i", i);
		break;
	case 3:
		decolagem(&p2, &p);
		break;
	case 4:
		for(j=0;j<i;j++){
			printf("%i->", p->i);
		}
	case 5:
		divisao(&p2,&p3,&p4);
		break;
}
}while(sw!=0);
	return 0;
}
