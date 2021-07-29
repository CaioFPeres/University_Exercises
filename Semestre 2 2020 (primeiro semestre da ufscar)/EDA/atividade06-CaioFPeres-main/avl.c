#include <stdlib.h>
#include "avl.h"

void inicializar( avl* arvore ) {
	arvore->raiz = 0;
}

void destruir_privado( node *p ) {
	
    if(p) {
    	destruir_privado(p->esq);
        destruir_privado(p->dir);
        free(p);
    }

}

void destruir( avl* arvore ) {
    destruir_privado(arvore->raiz);
}

node* rotEE( node* A ) { 
    node* B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    A->bal = 0;
    B->bal = 0;
    return B;
}

node* rotDD( node* A ) {
	node* B = A->dir;
	A->dir = B->esq;
	B->esq = A;
	A->bal = 0;
    B->bal = 0;
	return B;
}

node* rotED( node* A ) {
	node* B = A->esq;
	node* C = B->dir;
	B->dir = C->esq;
	C->esq = B;
	A->esq = C->dir;
	C->dir = A;
	
	if( C->bal == -1){
		A->bal = 1;
		B->bal = 0;
		C->bal = 0;
	}
	else if( C->bal == 1){
		A->bal = 0;
		B->bal = -1;
		C->bal = 0;
	}
	else{
		A->bal = 0;
		B->bal = 0;
	}
		
	return C;
}

node* rotDE( node* A ) {
	node* B = A->dir;
	node* C = B->esq;
	B->esq = C->dir;
	C->dir = B;
	A->dir = C->esq;
	C->esq = A;
	
	if( C->bal == -1){
		A->bal = 0;
		B->bal = 1;
		C->bal = 0;
	}
	else if( C->bal == 1){
		A->bal = -1;
		B->bal = 0;
		C->bal = 0;
	}
	else{
		A->bal = 0;
		B->bal = 0;
	}
	
	return C;
}


node* inserir_privado( node* p, int data, int *mudouAltura) {
	
	if(!p) {
		node* novo = (node*)malloc(sizeof(node));
		novo->data = data;
		novo->bal = 0;
		novo->dir = novo->esq = 0;
		*mudouAltura = 1;
		return novo;
	}
	
    else if (data < p->data){
    	
        p->esq  = inserir_privado(p->esq, data, mudouAltura);
    	
		if(*mudouAltura == 1){
    		p->bal = p->bal - 1;
    		if(p->bal == 0)
    			*mudouAltura = 0;
		}

		if (p->bal < -1)
       		return rotED(p);

       	else if (p->bal > 1)
        	return rotEE(p);
	}
	
	else if (data > p->data){
	
        p->dir = inserir_privado(p->dir, data, mudouAltura);
	
		if(*mudouAltura == 1){
    		p->bal = p->bal + 1;
    		if(p->bal == 0)
    			*mudouAltura = 0;
		}

		if(p->bal < -1)
			return rotDD(p);
		
		else if(p->bal > 1)
        	return rotDE(p);
	}

    return p;


}


void inserir( avl* arvore, int data) {
	
	int mudouAltura = 0;
	
	arvore->raiz = inserir_privado( arvore->raiz, data, &mudouAltura );
	
}
    
node* teto_privado(node* p, int dado) {
	
   if (p == NULL)
        return NULL;
  
    if (p->data == dado) 
        return p;
  
    if (p->data < dado) 
        return teto_privado(p->dir, dado);

    node* teto = teto_privado(p->esq, dado);
    
    
    if(teto){
    	if(teto->data >= dado)
    		return teto;
    	else
    		return p;
	}
	else
		return NULL;
    
}

node* piso_privado(node* p, int dado) {
   
    if (p == NULL) 
        return NULL;
  
    if (p->data == dado) 
        return p;
  
    if (p->data > dado)
        return piso_privado(p->esq, dado);

    node* piso = piso_privado(p->dir, dado);
    
    
    if(piso){
	    if(piso->data <= dado)
	    	return piso;
	    else
	    	return p;
	}
	else
		return NULL;
}


int teto( avl* arvore, int dado, int *teto_dado ) {
    node* c = teto_privado(arvore->raiz, dado);
    if(c) {
        *teto_dado = c->data;
        return 1;
    }
    return 0;
}

int piso( avl* arvore, int dado, int *piso_dado ) {
    node* f = piso_privado(arvore->raiz, dado);
    if(f) {
        *piso_dado = f->data;
        return 1;
    }
    return 0;
}

