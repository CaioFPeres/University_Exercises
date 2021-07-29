#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100
#define MAX_PESSOAS 300

struct dados {
    int nsocio;
    char nome[TAM_NOME];
    char endereco[TAM_NOME];
    char estcivil[TAM_NOME];
    char dependentes[TAM_NOME];
    float salario;
};

int main(int argc, char** argv) {

	struct dados pessoas[MAX_PESSOAS];
	int quant_pessoas = 0;
	int j; //Usado no for para percorrer o vetor
	int verificacao = 0, achou = 0; // Variaveis booleanas
	int numeroInserido;
	char continuar = 's';

	do {
		printf("Digite o nome da pessoa: ");
		fflush(stdin);
		gets(pessoas[quant_pessoas].nome);
		printf("Digite o numero do socio: ");
        while (verificacao == 0){
            scanf("%d", &pessoas[quant_pessoas].nsocio);
            if(quant_pessoas != 0){
                for(j = 0; j< quant_pessoas; j++){
                    if(pessoas[j].nsocio == pessoas[quant_pessoas].nsocio) {
                        printf("Digite um numero valido: ");
                        verificacao = 0;
                    }
                    else{
                        verificacao = 1;
                    }
                }
            }else verificacao = 1;
        }
		printf("Digite o Estado Civil da pessoa: ");
		fflush(stdin);
		gets(pessoas[quant_pessoas].estcivil);
		printf("Digite os Dependentes da pessoa: ");
		fflush(stdin);
		gets(pessoas[quant_pessoas].dependentes);
		fflush(stdin);
		printf("Digite o Endereco da pessoa: ");
		fflush(stdin);
		gets(pessoas[quant_pessoas].endereco);
		printf("Digite o salario da pessoa: ");
		fflush(stdin);
		scanf("%f", &pessoas[quant_pessoas].salario);
		printf("Deseja continuar?");
		fflush(stdin);
		scanf("%c", &continuar);
		fflush(stdin);
		printf("\n");

        verificacao = 0;
        quant_pessoas = quant_pessoas + 1;

	}while (continuar == 'S' || continuar == 's');

	//Escrita dos funcionarios

	printf("\nDigite o Numero do funcionario que voce deseja saber os dados: ");
	fflush(stdin);
	scanf("%d", &numeroInserido);
	for(j = 0; j< quant_pessoas;j++){
        if(numeroInserido == pessoas[j].nsocio){
            printf("\n\nInformacoes do socio com numero: %d", pessoas[j].nsocio);
            printf("\nNome: %s", pessoas[j].nome);
            printf("\nEstado civil: %s", pessoas[j].estcivil);
            printf("\nDependentes: %s", pessoas[j].dependentes);
            printf("\nEndereco: %s", pessoas[j].endereco);
            printf("\nSalario: R$%.2f", pessoas[j].salario);
            achou = 1;
        }
	}
	if(achou == 0){
        printf("Numero de socio nao cadastrado");
	}

	return 0;
}
