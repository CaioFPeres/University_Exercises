#include <iostream>
#include <assert.h>

// supondo que r não é nulo
//funcao devolve o ponteiro do ponteiro para o elemento de menor valor chave ou NULL em caso de arvore vazia

TNoABP **menorPP(TNoABP **r){
	//assert(r != NULL) return NULL;
	if(*r == NULL) return NULL;
	
	if((*r)->esq == NULL)
		return r;
		
	return menorPP(&((*r)->esq));
	
}



int main(int argc, char** argv) {
	
	
	
	
	return 0;
}
