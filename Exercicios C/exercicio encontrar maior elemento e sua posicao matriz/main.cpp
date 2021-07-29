#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int matriz[4][4];
int i, j;
int maior;
int posicaoi;
int posicaoj;

int main(int argc, char** argv) {
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			printf("Digite um valor para preencher a matriz: ");
			scanf("%i", &matriz[i][j]);}}

	for (i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(matriz[i][j]>maior){
				maior= matriz[i][j];
				posicaoi= i;
				posicaoj= j;}}}
				
				
	printf("Maior valor da matriz: %i\n", maior);
	printf("Posicao do maior valor: \nLinha: %i, Coluna: %i\n", posicaoi+1, posicaoj+1);
	
	for (i=0;i<4;i++){
		for(j=0;j<4;j++){
	printf(" %i", matriz[i][0]);}}

	return 0;
}
