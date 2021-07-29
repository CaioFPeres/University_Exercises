#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100
#define MAX_PESSOAS 5

int main(int argc, char** argv) {
	struct dados {
		int codigo;
		char nome[TAM_NOME];
		char endereco[TAM_NOME];
		float salario;
		int idade;
	};
	struct dados pessoas[MAX_PESSOAS];
	int quant_pessoas = 0;
	char continuar;
	
	do {
		printf("Digite o nome do cliente: ");
		scanf("%[^\n]%*c", &pessoas[quant_pessoas].nome);
		printf("Digite o Endereco do cliente: ");
		scanf("%[^\n]%*c", &pessoas[quant_pessoas].endereco);
		printf("Digite o salario do cliente: ");
		scanf("%[^\n]%*c", &pessoas[quant_pessoas].salario);
		printf("Digite a idade do cliente: ");
		scanf("%[^\n]%*c", &pessoas[quant_pessoas].idade);
		quant_pessoas++;
		printf("Deseja continuar?");
		scanf("%[^\n]%*c", &continuar);
		fflush(stdin);
	} while (continuar == 'S' || continuar == 's');
	return 0;
}
