#include <iostream>

int vetor[5];
int i=0;
int k=0;
int posicao=0;

int recursao(){
	i<5;
	i++;
	
	if(vetor[i]!=k){
	recursao();}
	if(vetor[i]==k)
	posicao=i;
	}

int main(int argc, char** argv) {
	
	printf("Digite um valor a ser encontrado: ");
	scanf("%i", &k);
	
	for(i=0;i<5;i++){
		printf("Insira valores para o vetor: ");
		scanf("%i", &vetor[i]);}
	i=0;
	recursao();
	
	printf("O numero encontrado esta na posicao: %i", posicao);
	
		
	return 0;
}
