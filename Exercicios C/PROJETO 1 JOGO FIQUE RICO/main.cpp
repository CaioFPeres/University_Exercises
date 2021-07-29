#include <iostream>
#include <stdlib.h>
#include <time.h>

int b;

int compara_aposta(int *aposta, int *sorteia, int n, int ns){
	int i;
	for(i=0;i<n;i++){
		if(*(aposta+i)==*(sorteia+i)){
			b++;
		}
	}
	return 0;
}

void sorteia_valores(int *sorteia, int ns){
	int i;
	int x;
	srand(time(NULL));
	for (i=0; i<15; i++)
    {
    	x= rand() % 60;
    	if(x!=0){
    	*(sorteia+i)= x;
		}
    }
}

void ler_aposta(int *aposta, int n){
	int i;
	for(i=0;i<n;i++){
		*(aposta+i)= 0;
	}
	for(i=0; i<n; i++){
			printf("\nDigite os numeros que deseja apostar: ");
			fflush(stdin);
			scanf("%i", aposta+i);
			while(*(aposta+i)<1 || *(aposta+i)>60){
				printf("Digite apenas numeros entre 1 e 60!\n Digite novamente para o %i elemento: ", i+1);
				fflush(stdin);
				scanf("%i", (aposta+i));
				}
			while(*(aposta+i-1) == *(aposta+i)){
				printf("Digite apenas numeros diferentes!\n Digite novamente para o %i elemento: ", i+1);
				fflush(stdin);
				scanf("%i", (aposta+i));
			}
			
			}
		}

int main(int argc, char** argv) {
	int n;
	int ns= 15;
	int i;
	int j;
	
	printf("Informe a quantidade de numeros que deseja apostar(entre 6 e 15): ");
	scanf("%i", &n);
	while(n<6 || n>15){
		printf("Quantidades de numeros a serem apostados nao pode ser menor que 6 ou maior que 15!\nDigite novamente: ");
		scanf("%i", &n);
	}
	int *aposta= (int*)malloc(sizeof(int)*n);
	int *sorteia= (int*)malloc(ns*sizeof(int));
	
	ler_aposta(aposta, n);
	sorteia_valores(sorteia, ns);
	compara_aposta(aposta, sorteia, n, ns);
	
	
	
	printf("\nNumeros Sorteados: ");
	for(j=0; j<15; j++){
	printf(" %i", *(sorteia+j));}
	printf("\nQuantidade de acertos: %i", b);
	
	return 0;
}
