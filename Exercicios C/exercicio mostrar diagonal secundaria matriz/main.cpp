#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
	int i, j;
	int matriz[5][5];
	int vetor[5];
	
	
	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			printf("Digite um valor para preencher a matriz: ");
			scanf("%i", &matriz[i][j]);}}
			
	for(i=0; i<5; i++){
		for(j=5; j>=0; j--){
			vetor[i]= matriz[i][j];
		}
	}
	
	printf("Valores do vetor: ");
	for(i=0; i<5; i++){
		printf("%i ", vetor[i]);
		
}
	return 0;
}
