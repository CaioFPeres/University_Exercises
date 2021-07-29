#include <iostream>


int main(int argc, char** argv) {
	
	float soma=0;
	float soma2=0;
	float soma3=0;
	int i;
	
	
	
	for(i=1;i<=10; i++){
		if(i%2==0){
			soma2= soma2 -  (float)1/i;}
		if(i%2!=0){
			soma= soma + (float)1/i;}}
		soma3= soma+soma2;
			
		printf("Soma dos termos: %f", soma3);
		
			
	return 0;
}
