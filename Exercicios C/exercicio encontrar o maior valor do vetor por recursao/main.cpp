#include <iostream>

int vetor[15];
int maior;
int i=0;


int recursao(){
	i++;
		
	if(vetor[i]>maior){
		maior=vetor[i];}
	if(i!=15)
	recursao();
	
}


int main(int argc, char** argv) {
	
	for (i=0;i<15;i++){
		printf("Digite um valor para cada indice do vetor: ");
		scanf("%i", &vetor[i]);}
	i=0;
	recursao();
	
	printf("Maior valor do vetor: %i", maior);
	return 0;
}
