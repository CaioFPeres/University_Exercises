#include <stdio.h>
#include <stdlib.h>


typedef struct No
{
    int chave;
    struct No *esq;
    struct No *dir;
    int altura;
}No;




int max(int a, int b)
{
    return (a > b)? a : b;
}


int altura(No *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}


No* novoNo(int chave)
{
    No *no = (No*) malloc(sizeof(No));
    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 1;
    return(no);
}


No *RotD(No *A) 
{
    No *B = A->esq; 
    No *C = B->dir;
    
    B->dir = A; 
    A->esq = C;

    A->altura = max(altura(A->esq), altura(A->dir))+1; 
    B->altura = max(altura(B->esq), altura(B->dir))+1; 

    return B; 
}

  
No *RotE(No *A)
{
    No *B = A->dir;
    No *C = B->esq;

    B->esq = A;
    A->dir = C;

    A->altura = max(altura(A->esq), altura(A->dir))+1;
    B->altura = max(altura(B->esq), altura(B->dir))+1;

    return B;
}


int FB(No *raiz){
	
   if (raiz == NULL)
         return 0;


      int e = FB(raiz->esq);
      int d = FB(raiz->dir);
      

      return d-e;
}


No* InsereAVLRec(No* no, int chave)
{

    if (no == NULL)
        return(novoNo(chave));

    if (chave < no->chave)
        no->esq  = InsereAVLRec(no->esq, chave);
    else if (chave > no->chave)
        no->dir = InsereAVLRec(no->dir, chave);
    else
        return no;


    no->altura = 1 + max(altura(no->esq), altura(no->dir));


    int bal = FB(no);
  

    if (bal > 1 && chave < no->esq->chave) 
        return RotD(no);
  

    if (bal < -1 && chave > no->dir->chave) 
        return RotE(no);
  

    if (bal > 1 && chave > no->esq->chave)
    {
        no->esq =  RotE(no->esq);
        return RotD(no);
    }


    if (bal < -1 && chave < no->dir->chave)
    {
        no->dir = RotD(no->dir);
        return RotE(no);
    }

    return no;
}


int Maior(No *raiz, int n) 
{ 
    
    if (raiz == NULL) 
        return -1; 
  
    
    if (raiz->chave == n) 
        return raiz->chave; 
  
    
    if (raiz->chave < n)
    	return Maior(raiz->dir, n);
  
   
    int k = Maior(raiz->esq, n);
    return (k != -1) ? k : raiz->chave;
}


int Menor(No *raiz, int n) 
{ 
    
    if (raiz == NULL) 
        return -1; 
  
    
    if (raiz->chave == n) 
        return raiz->chave; 
  
    
    if (raiz->chave > n)
    	return Menor(raiz->esq, n);
  
   
    int k = Menor(raiz->dir, n);
    return (k != -1) ? k : raiz->chave;
}


int main()
{
	int valor;
	No *raizMaior= NULL;
	No *raizMenor= NULL;
	int a, l, c, b, j;
	int v;
	
	
	scanf("%i", &l);
	for(c=0;c<l;c++){
	scanf("%i", &a);
	InsereAVLRec(&*raizMenor, a);}

	scanf("%i", &l);
	for(c=0;c<l;c++){
	scanf("%i", &a);
	InsereAVLRec(&*raizMaior, a);}

	scanf("%i", &l);

	for(c=0;c<l;c++){
		scanf("%i", &v);
		b = Menor(raizMenor, v);
		j = Maior(raizMaior, v);
		if(b==-1||j==-1)
			printf("descartar\n");
		else
			printf("%i %i\n", b, j);
	}

  return 0; 
} 

