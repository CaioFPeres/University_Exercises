#include <iostream>
int s, soma, soma2, soma3;

int serie1(){
	int s;
	s= 2/(1-2);
	return s;
}

int serie2(){
	int i;
	
	for(i=1;i<=10; i++){
		if(i%2==0){
			soma2= soma2 -  (float)1/i;}
		if(i%2!=0){
			soma= soma + (float)1/i;}}
		soma3= soma+soma2;
	return soma;
}



int main(int argc, char** argv) {
	printf("Resultado Serie1: %i\n", serie1());
	
	serie2();
	printf("Resultado Serie2: %i\n", soma);
	
	return 0;
}
