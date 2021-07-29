#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int v;
	int bal;
	struct no *esq, *dir;
} No;

int conta_nos( No* t, int count ) {
    
	if (t != NULL)
    {
      conta_nos(t->esq, count);
      count++;
      conta_nos(t->dir, count);
    }
    
    return count;
    
}


int conta_folhas(No* t, int count){
	
	if (t != NULL)
    {
    
		if(t->dir == NULL && t->esq == NULL)
			count++;
		
      conta_folhas(t->esq, count);
      conta_folhas(t->dir, count);
    
	}
	
	return count;
    
	
}



int n_rec_inorder(No* t){
	

	
}


No* espelho(No* t){
	
	
		
	
	
}




int abb(struct no* raiz){

  if (raiz == NULL)
    return 1;

	struct no* atual = raiz->esq;

  while(atual->dir != NULL ){
		atual = atual->dir;
  }

  if (raiz->esq != NULL && atual->chave > raiz->chave)
    return 0;

    atual = raiz->dir;

    while(atual->esq != NULL ){
		atual = atual->esq;
  }

  if (raiz->dir != NULL && atual->chave < raiz->chave)
    return 0;

  if (!abb(raiz->esq) || !abb(raiz->direita))
    return 0;

  return 1;
}





void imprimir(No *raiz, int menor, int maior){
	
    if (raiz != NULL)
    {
      if(raiz->chave > menor && raiz->chave < maior)
    	printf( " %d", raiz->chave);
      
	  imprimir(raiz->esq);
      imprimir(raiz->dir);
     }
}





struct no* anterior(struct no *p){
	
struct no* atual = p;

struct no* ant;
		
	while(atual != NULL){
			
		atual = atual->pai;
	}
	
	
	while(atual != NULL){
		
		ant = atual;
			
		if(p->chave > atual->chave){
			atual = atual->dir;
			
			if(atual->chave > p->chave)
				if(ant->chave == p->chave)
					return ant->pai;
				else
					return ant;
		}
		else
			atual = atual->esq;
			
			if(atual->chave > p->chave)
				if(ant->chave == p->chave)
					return ant->pai;
				else
					return ant;
		
	}

	return ant;
		
}
	
	
	
	
	
	
	













No* vet2arv(int vet[ ], int n){

	if(n%2 == 0)
		int mid = n/2;
	else
		int mid = (n/2) + 1;
 

    if (mid <= 1){
    	struct TNode *root = newNode(arr[mid+1]); 
    	return root;
    }
	
		struct TNode *root = newNode(arr[mid]);	
		root->left =  sortedArrayToBST(arr, mid-1);
  
    	root->right = sortedArrayToBST(arr, mid+1);
    	
	}
  
    return root; 
	
	
}


void calcula_bal(No* t){
	
    if (t == null)
        return 0;

    if (t->esq == null && t->dir == null)
        return 1;

    int esquerda = altura(t->esq);
    int direita = altura(t->dir);

	t->bal = direita - esquerda;
}

int max_bal(No* t){
	
	if(t != NULL){
		
		int aux = t->bal;
		
		max_bal(t->esq);
		max_bal(t->dir);
		
		return t->bal > aux ? t->bal : aux;
	
	}
	
	
	
}






No* vet2arv(int vet[ ], int n){
	
	int indiceMeio = n/2;
	int indiceEsquerda = indiceMeio - 1;
	int indiceDireita = indiceMeio - 1;
	
	
	inserir(vet[indiceMeio]);
	
	
	while(indiceEsquerda > 4){
		
		inserir(vet[indiceEsquerda]);
		
	}
	
	
	indiceMeio = (indiceMeio - 1)/2;
	
	
	
	
	
}






int main(){
	
	
	int c = 2;
	
	int* a;
	int* b = &c;
	
	a = b;
	
	printf("%i, %i, %i", &a, b, &c);
	
	
	a = &c;
	
	printf("\n%i", a);
	
	
	
	
	// se a for ponteiro e b não, então a = &b sempre.
	// se a for ponteiro e b também, então a = b;
	
	// se a for ponteiro e b não, fazendo a = b é impossivel de acessar o endereco que o ponteiro a aponta.
	// se a for ponteiro e b também, fazendo a = &b é impossivel acessar o valor que o ponteiro a aponta.
	
	
	
	
	return 0;
}
