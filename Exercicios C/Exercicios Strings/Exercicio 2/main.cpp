#include <iostream>
#include <stdlib.h>

char nome[50];
int x=0;

int funcao(){
	printf("Digite seu nome: ");
	gets(nome);
	
	if(nome[0]== 'a' || nome[0]== 'A'){
		printf("Bom dia, %s", nome);}
	
	return 0;
}

int main(int argc, char** argv) {
	funcao();
	
	
	return 0;
}
