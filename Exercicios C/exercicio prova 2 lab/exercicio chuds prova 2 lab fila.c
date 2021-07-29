#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int chave;
	int passa;
	struct no *prox;
} No;

No *alocaNo(int k, int p){
	No *aux=(No *)malloc(sizeof(No));
	if(aux==NULL){
		return NULL;
		}
	aux->chave=k;
	aux->passa=p;
	aux->prox=NULL;
}

No *insereNo(int k,int p, No *prim){
	if(prim==NULL){
		No *aux=alocaNo(k,p);
		prim->prox=aux;
		return prim;		
		}else{
		No *noAux=prim->prox;		
		No *aux=alocaNo(k,p);
		prim->prox=aux;
		aux->prox=noAux;
		return prim;	
		}
}

No* removeNo(No *prim){
	int i=1;		
	while(i!=0){
		if(prim->prox->prox==NULL){
			prim->prox=NULL;
			i=0;
			return prim;		
			}else{
			prim=prim->prox;			
			}
				
		}

}

int buscaMaior(No *prim){
	int i=1,mp=0;		
	while(prim->prox!=NULL){
		if(prim->passa>mp){
			mp=prim->passa;
			}else{
			prim=prim->prox;			
			}	
		}
	return mp;
}

No* criaf2(int maior,No **prim){
	int i=1;
	No *primf2=(No* )malloc(sizeof(No));		
	while(i!=0){
		if((*prim)->prox->passa==maior){
			primf2=(*prim)->prox->prox;
			(*prim)->prox=NULL;
			i=0;
			return primf2;		
			}else{
			(*prim)=(*prim)->prox;			
			}
				
		}

}

int main(){
	No *prim=alocaNo(-1,0);
	No *auxPrim,*auxPrimR,*f2;
	int sw,k,p,count=0,i=0,qtd=0,maior=0;
	printf("Bem vindo ao programa!\n\n");
	
	do{

	printf("Opções:\n1- Listar o numero de avioes aguardando na fila de decolagem;\n2- Autorizar a decolagem do primeiro aviao da fila;\n3- Adicionar um aviao a fila de espera;\n4- Listar todos os avioes na lista de espera;\n5- Abrir pista auxiliar;\n0- Sair.\n\n");
	printf("Escolha sua opção: ");
	scanf("%d",&sw);
	printf("\n");
	switch(sw){
			case 3:
				printf("Insira o identificador do avião: ");
				scanf("%d",&k);
				printf("Insira o numero de passageiros no avião: ");
				scanf("%d",&p);
				insereNo(k,p,prim);
				i++;
				break;	
			case 4:
				auxPrim=prim;
				auxPrim=auxPrim->prox;
				for(count=0;count<i;count++){
					printf("Aviao: %d\n",auxPrim->chave);
					auxPrim=auxPrim->prox;				
				}
				printf("\n");
				break;
			case 2:
				if(prim->prox==NULL){
					printf("Não tem avioes para decolar!!\n");
					printf("\n");				
				}else{
					auxPrimR=prim;
					prim=removeNo(prim);
					prim=auxPrimR;
					i--;
				}
				break;
			case 1:
				auxPrim=prim;
				while(prim->prox!=NULL){
					qtd++;
					prim=prim->prox;				
				}
				prim=auxPrim;
				printf("Numeros de avioes: %d\n",qtd);
				qtd=0;
				printf("\n");
				break;
			case 5: 
				if(prim->prox==NULL){
					printf("Não tem avioes para necessarios para abrir a pista auxiliar!!\n");
					printf("\n");				
				}else{
				auxPrim=prim;
				maior=buscaMaior(prim);
				prim=auxPrim;
				f2=criaf2(maior,&prim);
				prim=auxPrim;
				printf("\n");
				}
				break;
			case 0:
				printf("Obrigado!\n");
				printf("\n");
				sw=0;
				break;
			default: 
				printf("Inválido!\n");
				printf("\n");
				break;

	}
		
	}while(sw!=0);
}
