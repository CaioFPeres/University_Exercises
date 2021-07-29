#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int i;
	int *array=NULL;
	array=(int*)malloc(5*sizeof(int));
	for(i=0; i<5; i++){
		printf("insira valor da posicao %i: ", i+1);
		scanf("%i", &*(array+i));}
	for(i=0; i<5; i++){
		printf("\nDobro do Valor da posicao %i: %i", i+1, *(array+i)*2);
	}
	
	
	return 0;
}
