#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>

	int i;
	float maiornota1;
	char nomemaiornota1[50];
	char nomemaiormediageral[50];
	char nomemenormediageral[50];
	float mediageral[5];
	float maiormediageral;
	float menormediageral;
	
	
	typedef struct input{
	int	ra;
	char nome[50];
	float nota1, nota2, nota3;
	}alunos;
	
	alunos vetoralunos[5];

int main(int argc, char** argv) {
	printf("Digite os valores do aluno:\n");
	for(i=0;i<5;i++){
	fflush(stdin);
	printf("Nome: ");
	fgets(vetoralunos[i].nome, 50, stdin);
	printf("\nRA: ");
	scanf("%i", &vetoralunos[i].ra);
	printf("\nNota 1, 2 e 3: ");
	scanf("%f", &vetoralunos[i].nota1);
	scanf("%f", &vetoralunos[i].nota2);
	scanf("%f", &vetoralunos[i].nota3);
	}
	for(i=0;i<5;i++){
		if(vetoralunos[i].nota1>maiornota1){
			maiornota1= vetoralunos[i].nota1;
			strcpy(nomemaiornota1, vetoralunos[i].nome);}}
	printf("Aluno com maior nota da P1: %s", nomemaiornota1);
	
		for(i=0;i<5;i++){
			mediageral[i]= (vetoralunos[i].nota1+vetoralunos[i].nota2+vetoralunos[i].nota3)/3;}
			
		for(i=0;i<5;i++){
			if(mediageral[i]>maiormediageral){
				maiormediageral= mediageral[i];
				strcpy(nomemaiormediageral, vetoralunos[i].nome);}}
	printf("Aluno com maior media geral: %s", nomemaiormediageral);
		for(i=0;i<5;i++){
			if(mediageral[i]<menormediageral){
				menormediageral= mediageral[i];
				strcpy(nomemenormediageral, vetoralunos[i].nome);}}
	printf("Aluno com menor media geral: %s", nomemenormediageral);
	
		for(i=0;i<5;i++){
			if(mediageral[i]<6){
				printf("Aluno %s reprovado.", vetoralunos[i].nome);}
			else{
				printf("Aluno %s aprovado.", vetoralunos[i].nome);}}
	
		
	return 0;
}
