#include <stdio.h>
#include <stdlib.h>


typedef struct lig1{
	int chave;
	struct lig1* prox;
}lig;


struct No{
    int chave;
    lig ligacoes;
    struct No* prox;
}; 
typedef struct No Bolinha;


Bolinha *alocaNo(int chave){
    Bolinha *aux = (Bolinha *) malloc(sizeof(Bolinha));
    aux->prox = NULL;
    aux->chave = chave;
    return aux;
}


void insereFinal(Bolinha **lista, int chave){
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



int main(int argc, char** argv) {
	Bolinha *lista = NULL, *busca = NULL;
	
	insereFinal(&lista, 5);
	
	
	return 0;
}
