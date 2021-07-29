#include <iostream>
#include <math.h>

float role(float x){
	float resul;
	resul= (x/60)/60;
	
	return resul;
}

int main(int argc, char** argv) {
	float x;
	float resul;
	float resul2;
	printf("Tempo de duracao em segundos: ");
	scanf("%f", &x);
	
	role(x);
	resul= role(x);
	resul2= floor(role(x));
	resul= resul*60.0 - (floor(resul)*60.0);
	
	printf("O tempo de duracao em horas eh: %f\n", resul2);
	printf("O tempo em minutos eh: %f", resul);
	
	
	
	return 0;
}
