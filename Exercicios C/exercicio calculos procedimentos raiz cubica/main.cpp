#include <iostream>
#include <math.h>


float x, y, z, w, cu;

void cubo(){
	cu= pow(x, 3);
	printf("O cubo do numero e: %f", cu);
}

void raizquadrada(){
	w= sqrt(x);
	printf("A raiz quadrada e: %f\n", w);
}

void raizcubica() {
	z= pow(x, 0.33333333);
	printf("A raiz cubica e: %f\n", z);
}


void quadrado() {
	y= x*x;
	printf("Elevado ao quadrado: %f\n", y);
}

int main(int argc, char** argv) {
	printf("Digite um numero positivo maior que 0: ");
	scanf("%f", &x);
	do{
	if(x<=0){
		printf("Positivo maior que 0 seu demente! ");
		scanf("%f", &x);
	}
		if(x>0)
	{
		quadrado();
		raizcubica();
		raizquadrada();
		cubo();
		
	}}while(x<=0);
	return 0;
}
