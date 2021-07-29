#include <iostream>
#include <math.h>
#include <cmath>


int main(int argc, char** argv) {
	float i=0;
	float x=0;
	float soma=0;
	
	
	printf("Digite um numero a ser elevado a -i, i++: ");
	scanf("%f", &x);
	for(i=0; i<20; i++){
		soma= soma + (float)1/(pow(x,i));
	}
	printf("Somatorio de 1/(x elevado a i): %f", soma);
	
	return 0;
}
