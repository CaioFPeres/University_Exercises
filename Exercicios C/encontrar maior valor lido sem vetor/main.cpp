#include <iostream>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
	
	int i=0, n, v, aux, controle=0;
	
	printf("Digite valores: ");
	
	for(i=0;i<5;i++){
		
		scanf("%i", &aux);
		scanf("%i", &n);
		
		if(controle<aux){
			controle= aux;
		}
		if(controle<n){
			controle= n;
		}
		if(aux>n){
			controle= aux;
		}
		else{
			controle= n;
		}
		
	}
	printf("Maior: %i", controle);
	
	
	return 0;
}
