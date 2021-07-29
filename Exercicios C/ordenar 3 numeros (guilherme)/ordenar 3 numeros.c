#include <iostream>


int ordena(int *pa, int *pb, int *pc){
	int maior=0, menor=0, i, meio=0;
	maior=*pa;
	menor=*pc;
	
	if((*pa==*pb)&&(*pa==*pc)){
		return 1;}
	else{
		if(maior<*pb){
			maior=*pb;
		}
		if(maior<*pc){
			maior=*pc;
		}
		if(menor>*pb){
			menor=*pb;
		}
		if(menor>*pa){
			menor=*pa;
		}
		if((menor<*pa)&&(*pa<maior)){
			meio=*pa;
		}
		if((menor<*pb)&&(*pb<maior)){
			meio=*pb;
		}
		if((menor<*pc)&&(*pc<maior)){
			meio=*pc;
		}
		*pa=menor;
		*pb=meio;
		*pc=maior;
		return 0;
	}
	}
	

int main(int argc, char** argv) {
	int a=0, b=0, c=0, comp=0;
	printf("Valor de a: ");
	scanf("%i", &a);
	printf("\nValor de b: ");
	scanf("%i", &b);
	printf("\nValor de c: ");
	scanf("%i", &c);
	comp= ordena(&a,&b,&c);
	if(comp==1){
		printf("\n Nao sao iguais!\nValores em ordem decrescente: %i, %i, %i\n", c, b, a);
	}
	else{
		printf("\nNao sao iguais!\nValores em ordem decrescente: %i, %i, %i\n", c, b, a);
	}
	
	
	
	
	return 0;
}
