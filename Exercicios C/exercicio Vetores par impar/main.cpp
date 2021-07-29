#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


	int vetor[5]={0};
	int P[15]={0};
	int IM[15]={0};
	int i;

	void parimpar(){
		for(i=0; i<5; i++){
			if(vetor[i]%2==0){
			P[i]=vetor[i];}
			else{
			IM[i]=vetor[i];
		}
		}
		for(i=0; i<5; i++){
			if(P[i]!=0)
			printf("Valores pares: %i\n", P[i]);}
		for(i=0; i<5; i++){
			if(IM[i]!=0)
			printf("Valores impares: %i\n", IM[i]);}
}



int main(int argc, char** argv) {
	
	for (i=0;i<5;i++){
		printf("Digite um valor para cada indice do vetor: ");
		scanf("%i", &vetor[i]);
	}
	
	parimpar();
	
	return 0;
}
