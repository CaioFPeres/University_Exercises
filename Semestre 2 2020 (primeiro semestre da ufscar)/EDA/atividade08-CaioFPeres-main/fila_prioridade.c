#include <stdlib.h>
#include "fila_prioridade.h"

// ***************************************************************
// Funções internas !
// ***************************************************************

void swap( fp_item_prioridade *i1, fp_item_prioridade *i2 ) {
	fp_item_prioridade i = *i1;
	*i1 = *i2;
	*i2 = i;
}

void fixDown(fp_item_prioridade* vetor, int k, int N) {
	//implementar
}

void fixUp(fp_item_prioridade* vetor, int k) {
	//implementar
}

// ****************************************************************


int inicializa(fp* f, unsigned maximo) {
	f->heap = (fp_item_prioridade*)malloc(sizeof(fp_item_prioridade)*maximo);
	if(!f->heap)
		return 0;
	f->quantidade = 0;
	f->maximo = maximo;
	return 1;
}

void destroi(fp* f) {
	free(f->heap);
	f->quantidade = 0;
	f->maximo = 0;
	f->heap = NULL;
}

int vazia(fp* f){

	if( f->quantidade == 0 ){
		return 1;
	}
	else{
		return 0;
	}
	
}

int cheia(fp* f){
	
	if( f->quantidade == f->maximo){
		
		return 1;
	}
	else{
		return 0;
	}

}

unsigned tamanho(fp* f){
	
	return f->quantidade;
	
}

int insere(fp* f, fp_item item, int prioridade){
	
	int i = f->quantidade;
	
	if(cheia(f))
		return 0;
	
	f->heap[f->quantidade].item = item;
	f->heap[f->quantidade].prioridade = prioridade;
	
	
	
	if(f->quantidade == 0){
		f->quantidade++;
		
		if(f->heap[f->quantidade -1].item != NULL){
			return 1;
		}
		else{
			return 0;
		}
		
	}
	
	
	while(f->heap[i].prioridade > f->heap[(i-1)/2].prioridade){
		
		swap(&f->heap[i], &f->heap[(i-1)/2]);
		
		i = (i-1)/2;
	}
	
	f->quantidade++;
	
	if(f->heap[f->quantidade -1].item != NULL){
		return 1;
	}
	else{
		return 0;
	}

	
}


int removeMaiorPrioridade(fp* f){
	
	if(vazia(f))
		return 0;
	

	int pai = 0;
	int filho = pai*2 + 1;
	
	f->quantidade--;
	
	f->heap[0] = f->heap[f->quantidade];
	
	f->heap[f->quantidade].item = NULL;
	f->heap[f->quantidade].prioridade = NULL;
	
	
	
	while( filho < f->quantidade ){
				
				
			if( f->heap[filho].prioridade < f->heap[filho + 1].prioridade ){

				filho++;
				
			}
			
			
			if( f->heap[pai].prioridade >= f->heap[filho].prioridade ){
				break;
			}
		
			swap(&f->heap[pai], &f->heap[filho]);
	
		pai = filho;
		
		filho = pai*2 + 1;

		
	}
	
	
	
	if(f->heap[f->quantidade+1].item == NULL){
		return 1;
	}
	else{
		return 0;
	}
	
	
	
}






int maiorPrioridade(fp* f, fp_item* item, int* prioridade){
	
	if(vazia(f))
		return 0;
	
	
	*item = f->heap[0].item;
	*prioridade = f->heap[0].prioridade;
	
	
	if(item != NULL){
		return 1;
	}
	else{
		return 0;
	}
	
	
	
}





