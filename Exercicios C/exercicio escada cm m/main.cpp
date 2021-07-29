#include <iostream>
#include <math.h>

int main(int argc, char** argv) {
	float x, y, z;
	printf("Insira tamanho do degrau em cm: ");
	scanf("%f", &x);
	printf("Insira altura que deseja subir em m: ");
	scanf("%f", &y);
	z= (100*x)/y;
	printf("%f", z);
	
	return 0;
}
