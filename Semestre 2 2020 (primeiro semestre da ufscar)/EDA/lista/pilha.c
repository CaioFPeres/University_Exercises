#include <stdio.h>
#include <stdlib.h>

struct No
{
  int chave;
  /* outros campos */
  struct No *prox;
};

typedef struct No No;


No* insereInicio(No *prim, int k)
{
	if(prim==NULL){
		prim=(No*)malloc(sizeof(No));
		prim->chave=k;
		prim->prox=NULL;
		return prim;
	}else{
		No *aux=prim;
		prim=(No*)malloc(sizeof(No));
		prim->chave=k;
		prim->prox=aux;
		return prim;
	}
}

No* removeInicio(No *prim)
{
//assert(prim);
	if(prim==NULL){
		return prim;
	}else if(prim->prox==NULL){
		prim=NULL;
		return prim;
	}else{
		No *aux;
		aux=prim;
		prim=prim->prox;
		aux=NULL;
	  	free(aux);
		return prim;
	}
	
}

No* buscarElem(No *prim)
{
  //assert(prim);

  	if (prim == NULL){
		return prim;
	}else{
		return prim;
	}
}

void imprimeLista(No *prim)
{
  //assert(prim);
  No *aux;
  if (prim == NULL) printf("\nLista vazia!");
  while(prim != NULL)
  {
      printf("%d - ", prim->chave);
      prim=prim->prox;
  }
      printf("NULL\n");
}

int main(){
	int o,k;
	No *p=NULL;
	do{
		printf("1=inserir\n2=retirar\n3=topo\n4=imprimir\n5=sair\n");
		scanf("%d",&o);
		switch(o){
			case 1:
				printf("digite o valor da chave: ");
				scanf("%d",&k);
				p=insereInicio(p,k);
				break;	
			case 2:
				p=removeInicio(p);
				break;	
			case 3:
				p=buscarElem(p);
				if(p==NULL){
					printf("topo=nenhum\n");
				}else{
					printf("topo=%d\n",p->chave);
				}
				break;	
			case 4:
				imprimeLista(p);
				break;
			case 5:
				printf(".");
				break;	
			default:
				printf("NA opcao\n");
				break;	
		}
	}while(o!=5);
	return 0;
}
