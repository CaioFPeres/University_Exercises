
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nomes{
	char nome[50];
	int idade;
}pessoas;

int funcao(pessoas *a){
	int s, v, k;
	s = strcmp(a->nome, (a+1)->nome);
	v = a->idade;
	k = (a+1)->idade;
	
	if(s==0 && v==k){
		return 0;}
	else {
		return 1;}
}

int main(int argc, char** argv) {
	int i;
	pessoas *p= (pessoas *)malloc(2*sizeof(pessoas));
		for(i=0;i<2;i++)
    {
        printf("\nDigite o nome do usuario %d e sua idade: ",i+1);
        setbuf(stdin,NULL);
        fgets((p+i)->nome,50,stdin);
        scanf("%i", &(p+i)->idade);
    }
    
    if(funcao(p)==0){
    	printf("Sao iguais!");
	}
	else{
		printf("Sao Diferentes!");
	}
    
	return 0;
}
