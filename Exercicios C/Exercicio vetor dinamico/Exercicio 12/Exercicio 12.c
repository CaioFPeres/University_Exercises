#include <stdio.h>
#include <stdlib.h>

int main(){
	int n1,n2,i,*v1,*v2,*r;
	printf("Digite o numero de componentes do primeiro vetor: ");
	scanf("%i",&n1);
	v1 = (int*)malloc(n1*sizeof(int));
	for(i=0;i<n1;i++){
		printf("Escreva um valor para a posicao %i do vetor: ",i+1);
		scanf("%i",&v1[i]);
	}
	printf("Digite o numero de componentes do segundo vetor: ");
	scanf("%i",&n2);
	v2 = (int*)malloc(n2*sizeof(int));
	for(i=0;i<n2;i++){
		printf("Escreva um valor para a posicao %i do vetor: ",i+1);
		scanf("%i",&v2[i]);
	}
	r = (int*)malloc((n1+n2)*sizeof(int));
	for(i=0;i<n1+n2;i++){
		if(i<n1){
			r[i] = v1[i];
			
		if(r[i]==v2[i])
			v2[i]= NULL;}
		
		else{
			r[i] = v2[i-n1];
		}}
	for(i=0;i<n1+n2;i++)
		printf("%i ",r[i]);
	free(v1);
	free(v2);
	free(r);
return 0;	
}
