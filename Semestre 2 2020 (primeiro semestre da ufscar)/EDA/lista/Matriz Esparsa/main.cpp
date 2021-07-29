#include <iostream>
#include <stdio.h>
#include <stdlib.h>


typedef struct celula {
       int valor;
       int lin;
       int col;
       struct celula *prox;
       struct celula *ant;

} t_celula;



t_celula *alocaNo(int valor, int lin, int col){
    t_celula *aux = (t_celula *) malloc(sizeof(t_celula));
    aux->prox = NULL;
    aux->valor = valor;
    aux->col = col;
    aux->lin = lin;
    return aux;
}

void insereFinal(t_celula **lista, int valor, int lin, int col){
    if((*lista)==NULL){ //lista vazia
        *lista = alocaNo(valor, lin, col);
    }
    else { //lista ja contem elementos
        t_celula *aux = alocaNo(valor, lin, col);
        if((aux) == NULL) return;
        
        (*lista)->prox = aux;
        
        aux->prox= NULL;
        
        *lista = (*lista)->prox;
    }
}


void imprimir_matriz(t_celula* lista){
	if(!vazia(lista)){
		int total_linhas = 0;
		int total_colunas = 0;
		t_celula* p;
		p= lista;
		while(p){
			if(p->col>total_colunas)
			total_colunas = p->col;
			p=p->prox;
		}
	
		p=lista;
		while(p){
			if(p->lin>total_linhas)
				total_linhas = p->lin;
			p= p->prox;
		}
		int i;
		for(i=0; i< total_linhas; i++){
			int j;
			for(j=0;j<total_colunas;j++){
				t_celula* cel = existe_celula(lista, i+1, j+1);
				if(cel)
					printf("%d\t", cel->valor);
				else
					printf("0\t");
			}
			printf("\n");
		}
	}
	else
		printf("\nLista Vazia!\n");
}


int main(int argc, char** argv) {
	t_celula* lista;
	
	insereFinal(&lista,5,1,1);
	insereFinal(&lista,2,1,2);
	insereFinal(&lista,3,2,1);
	
	imprimir_matriz(lista);
	
	
	
	
	
	
    
}
