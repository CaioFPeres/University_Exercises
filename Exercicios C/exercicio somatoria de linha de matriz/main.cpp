#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int matriz [7][5]={0};
int cont=0;
int soma[7]={0};
int i;
int j;

int main(int argc, char** argv) {
	
	for(i=0; i<7; i++){
		for(j=0; j<5; j++){
			printf("Digite um valor para preencher a matriz: ");
			scanf("%i", &matriz[i][j]);}}
	
	for(i=0; i<7; i++){
		for(j=0; j<5; j++){
			soma[i]= matriz[i][j] + soma[i];}}
			
	for(i=0; i<7; i++){
		printf("\nSomatorio: %i\n", soma[i]);}
	
	
	return 0;
}
