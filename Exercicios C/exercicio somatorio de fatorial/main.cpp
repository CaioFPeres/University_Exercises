#include <iostream>
#include <math.h>



int main(int argc, char** argv) {
	float somapar=0;
	float somaimpar=0;
	float somatorio=0;
	int x, y, z, n;
	int i=0;
	int j=0;
	int fat;
	
	printf("Insira X(termo a ser elevado a um numero) e N(quantidade de termos): ");
	scanf("%i", &x, &n);
	for(i=1; i<n; i++){
		fat=i+(i-1);
		fat=fat;
		y=fat;
		while(y>1){
		y--;
		fat= fat*y;}}
		if(i%2==0){
			if(i==1 && i==2){
				somapar= somapar - pow(x,i)/fat;}
			if(i>2){
				somapar= somapar - pow(x,i+(i-2))/fat;}}
		else{
			if(i==1 && i==2){
				somaimpar= somaimpar + pow(x,i)/fat;}
			if(i>2){
				somaimpar= somaimpar + pow(x,i+(i-2))/fat;}}
			somatorio= somapar + somaimpar;
			printf("O somatorio eh: %i", somatorio);
	
	return 0;
}
