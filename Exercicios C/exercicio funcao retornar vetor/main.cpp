#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
	
	int vetor[5]={0};
	int x;
	int cont;
	int i;
		
		int funcao(int vetor[5], int x){
		for(i=0; i<5; i++){
		if(vetor[i]==x)
		cont++;}
		
		return(cont);}
	
	
int main(int argc, char** argv) {

	printf("Insira valor de X: ");
	scanf("%i", &x);
	
		for (i=0; i<5; i++){
		printf("Digite um valor para cada indice do vetor: ");
		scanf("%i", &vetor[i]);
	}
	
		printf("Numero de vezes que o numero apareceu no vetor: %i", 	funcao(vetor, x));
	
	return 0;
}
