#include <iostream>

int r;
int n;
float i;
float pot;
float resul;


int main(int argc, char** argv) {
	
	printf("Deseja calcular qual raiz? ");
	scanf("%i", &r);
	printf("De qual numero? ");
	scanf("%i", &n);
	pot = 1/r;
	resul= n;
	
	if(pot<0){
	for(i=-1; i>pot; i--){
		resul= resul*n;}}
	else{
	for(i=1; i<pot; i++){
		resul= resul*n;}}
	printf("Valor: %f", resul);
	
	return 0;
}
