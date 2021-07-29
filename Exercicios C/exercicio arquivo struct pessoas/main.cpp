#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct nomes{
	char nome[50];
	int idade;
}pessoas;

int main(int argc, char** argv) {
	int i;
	int n;
	
	printf("Digite o numero de pessoas a serem registradas: ");
	scanf("%i", &n);
	pessoas *p= (pessoas *)malloc(n*sizeof(pessoas));
	
		for(i=0;i<n;i++)
    {
        printf("\nDigite o nome do usuario %i e sua idade: ",i+1);
        setbuf(stdin,NULL);
        fgets((p+i)->nome,50,stdin);
        scanf("%i", &(p+i)->idade);
    }
    
    
    FILE *f = fopen("arquivo.txt", "w+");
	if (f == NULL)
	{
    	printf("Erro ao abrir arquivo!\n");
    	exit(1);
	}

	for(i=0;i<n;i++)
	{
	fprintf(f, "Usuario: %s Idade: %i\n\n", (p+i)->nome, (p+i)->idade);
	}
	fclose(f);
}

