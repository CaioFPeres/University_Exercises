#include <stdio.h>
#include <stdlib.h>

int cave[10][10];

//num de linhas e colunas eh menor ou igual a 10


int duende(int inix, int iniy){
	int i, j, dist = 0;
	
	
	
	//caso base saida
	if(cave[inix+1][iniy] == 0){
		dist = dist + 1;
		return dist;}
	if(cave[inix][iniy+1] == 0){
		dist = dist + 1;
		return dist;}
	if(cave[inix][iniy-1] == 0){		
		dist = dist + 1;
		return dist;}
	if(cave[inix-1][iniy] == 0){	
		dist = dist + 1;
		return dist;}
		
		
	//pra baixo
	if(cave[inix+1][iniy] == 1 ){
		cave[inix+1][iniy] = 3;
		cave[inix][iniy] = 1;
		inix = inix + 1;
		dist = dist + 1;
	duende(inix, iniy);
}
	
	//pra direita
	if(cave[inix][iniy+1] == 1){
		cave[inix][iniy+1] = 3;
		cave[inix][iniy] = 1;
		iniy = iniy + 1;
		dist = dist + 1;
	duende(inix, iniy);
}

	//para cima
	if(cave[inix-1][iniy] == 1){
		cave[inix-1][iniy] = 3;
		cave[inix][iniy] = 1;
		inix = inix - 1;
		dist = dist + 1;
	duende(inix, iniy);	
}
		
	//para esquerda
	if(cave[inix][iniy-1] == 1){
		cave[inix][iniy-1] = 3;
		cave[inix][iniy] = 1;
		iniy = iniy - 1;
		dist = dist + 1;
	duende(inix, iniy);
}
		

}




int main(int argc, char** argv) {
	int cave[10][10];
	int i, j, N, M, inix, iniy;
	
	
	
	scanf("%i", &N);
	scanf("%i", &M);
	
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			scanf("%i", &cave[i][j]);
			if(cave[i][j] == 3){
				inix = i;
				iniy = j;}
		}
	}

	
	
	
//PRA PRINTAR
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			printf("\n%i ", cave[i][j]);
		}
		printf("\n");
	}
	
	duende(inix, iniy);
	
	
	
	return 0;
}
