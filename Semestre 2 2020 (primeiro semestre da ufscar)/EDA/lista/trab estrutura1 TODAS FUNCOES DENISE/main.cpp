#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
	int matricula;
	char nome[50];
}tipoAluno;

typedef struct lista{
	tipoAluno dado;
	struct lista *prox;
}tipoLista;


tipoLista* alocaNo(int matricula, char nome[]){
    tipoLista *aux = (tipoLista *) malloc(sizeof(tipoLista));
    aux->prox = NULL;
    aux->dado.matricula = matricula;
    strcpy(aux->dado.nome,nome);
    return aux;
}


void insereInicio(tipoLista **lista, int matricula, char nome[]){
    if((*lista)==NULL){ //lista vazia
        *lista = alocaNo(matricula, nome);
    }
    else { //lista ja contem Elementos
        tipoLista *aux = alocaNo(matricula, nome);
        if((aux) == NULL) return;
        aux->prox = (*lista);
        *lista = aux;
    }
}

tipoLista* insereFinal(tipoLista **lista, int matricula, char nome[]){
	
	
    if(*lista == NULL){ //lista vazia
        *lista = alocaNo(matricula, nome);
    }
    else { //lista ja contem elementos
        tipoLista *aux = alocaNo(matricula, nome);
        if((aux) == NULL) return 0;


        (*lista)->prox = aux;
        aux->prox= NULL;
        
        
        *lista = (*lista)->prox;
    }
}


void removeInicio(tipoLista **lista){
    tipoLista *aux = (*lista)->prox;
    free((*lista));
    (*lista) = aux;
}

tipoLista removeFinal(tipoLista **lista){
    if((*lista)->prox != NULL)
    	removeFinal(&(*lista)->prox);
    free((*lista)->prox);
}

void removeChave(tipoLista **lista, int matricula){
    if((*lista) == NULL) return;    //lista vazia
    if((*lista)->dado.matricula == matricula) removeInicio(&(*lista)); return;//primeiro Elemento
    tipoLista *aux = (*lista);
    if(aux->prox->dado.matricula == matricula){
        tipoLista *maisUmAux;
        maisUmAux = aux->prox;
        if(maisUmAux->prox->prox == NULL){
            free(maisUmAux);
            aux->prox == NULL;
        }
        else{
            aux->prox == maisUmAux->prox;
            free(maisUmAux);
            maisUmAux == NULL;
        }
    }else   removeChave(&(*lista)->prox, matricula);
}

tipoLista *buscaChave(tipoLista *lista, int matricula){
    if(lista == NULL) return NULL;
    if(lista->dado.matricula == matricula) return lista;
    buscaChave(lista->prox, matricula);
}

int printaLista (tipoLista **lista){
	
	while((*lista) != NULL){
	printf("%s\n", (*lista)->dado.nome);
	*lista= (*lista)->prox;

}
return 0;
}



int main(int argc, char** argv) {
	tipoLista *lista = NULL;
	tipoLista *lista2 = NULL;
	tipoLista **busca;
	
	int matricula;
	char nome[50];
	int r;
	int o;

	while(1==1){
	printf("Selecione uma opcao: \n1 para buscar matricula, 2 para remover um aluno da lista, 3 para inserir novo aluno e 4 para imprimir lista:\n");
	scanf("%i", &o);
    switch(o){

    	case 1:
	printf("Digite a matricula a ser buscada: ");
	scanf("%i", &matricula);
	if(buscaChave(lista, matricula) != NULL)
		printf("Matricula encontrada!");
	else
		printf("Matricula nao encontrada!");
	break;

    	case 2:
    printf("Digite a matricula a ser removida: ");
    scanf("%i", &matricula);
    removeChave(&lista, matricula);
    break;

		case 3:
	printf("Digite a matricula e o nome a serem inseridos: ");
    scanf("%i", &matricula);
    scanf("%s", nome);
    insereFinal(&lista, matricula, nome);
    break;

    	case 4:
    if(printaLista(&lista) == 0)
    printf("Fim da lista.\n\n");
    break;

}
}
	return 0;
}
