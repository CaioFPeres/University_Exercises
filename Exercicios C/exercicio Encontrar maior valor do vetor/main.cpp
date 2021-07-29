#include <iostream>


//encontrar maior valor de um vetor

int main(int argc, char** argv) {
	int vetor[5]={0};
	int i;
	int maior=0;
	
	for (i=0;i<5;i++){
		printf("Digite um valor para cada indice do vetor: ");
		scanf("%i", &vetor[i]);
	}
	
	for (i=0;i<5;i++){
		if(vetor[i]>maior)
		maior=vetor[i];
	}
	printf("Maior valor do vetor: %i", maior);
	
	
	return 0;
}
