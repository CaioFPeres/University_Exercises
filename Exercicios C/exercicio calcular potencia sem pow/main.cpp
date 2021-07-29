#include <iostream>



int n=0, pot=0;
int i=0;
float resul=0;


int main(int argc, char** argv) {
	printf("Digite um numero a ser calculada a potencia: ");
	scanf("%i", &n);
	printf("Digite a potencia: ");
	scanf("%i", &pot);
	resul= n;
	
	if(pot<0){
	for(i=-1; i>pot; i--){
		resul= resul*n;}}
	else{
	for(i=1; i<pot; i++){
		resul= resul*n;}}
	
	if(pot<0)
	printf("Resultado: %f", 1/resul);
	else
	printf("Resultado: %f", resul);	
	
	return 0;
}
