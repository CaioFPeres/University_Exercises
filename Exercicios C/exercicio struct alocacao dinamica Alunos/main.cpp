#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct pinto{
	char nome[50];
	int matricula;
	int p1, p2;
	int media;
}penes;

int main(int argc, char** argv) {
	penes *p;
	int i;
	int n;
	printf("Digite o numero de alunos: ");
	scanf("%i", &n);
	p= (penes *)malloc(n*sizeof(penes));
	for(i=0;i<n;i++){
	printf("Seu nome: ");
	fflush(stdin);
	fgets((p+i)->nome, 50, stdin);
	printf("Sua matricula: ");
	scanf("%i", &(p+i)->matricula);
	printf("Digite suas notas: ");
	scanf("%i", &(p+i)->p1);
	scanf("%i", &(p+i)->p2);
	(p+i)->media= ((p+i)->p1 + (p+i)->p2)/2;
}

	for(i=0;i<n; i++){
	printf("Nome: %s\nMatricula: %i\nMedia: %i", (p+i)->nome, (p+i)->matricula, (p+i)->media);
	
}
	return 0;
}
