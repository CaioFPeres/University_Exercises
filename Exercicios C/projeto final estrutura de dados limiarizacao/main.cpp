#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct img{
	int pixel;
	int linha;
	int coluna;
	struct img *prox;
}img;

img* aloca(img **p, int pixel, int linha, int coluna){
	if(*p==NULL){
	*p=(img*)malloc(sizeof(img));
	if(*p==NULL){
		return NULL;
	}
	(*p)->coluna=coluna;
	(*p)->linha=linha;
	(*p)->pixel=pixel;
	(*p)->prox=NULL;
	
}
else{
	img *aux=(img*)malloc(sizeof(img));
	(*p)->prox= aux;
	
	aux->coluna=coluna;
	aux->linha=linha;
	aux->pixel=pixel;
	aux->prox=NULL;
	
	(*p)=(*p)->prox;
	
}
}

img* lerarquivo(img **prim){
	FILE *arq;
	arq= fopen("img.pgm", "r");
	if(arq==NULL){
		return NULL;
	}
	char st[3];
	int dimensaoL;
	int dimensaoR;
	int maiorpixel;
	fscanf(arq,"%s", st);
	fscanf(arq,"%d %d", &dimensaoL, &dimensaoR)
	fscanf(arq,"%d", &maiorpixel);
	
	while( != EOF){
		
	};
	
}

int main(int argc, char** argv) {
	img *prim=NULL;
	
	return 0;
}
