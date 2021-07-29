#include "series.h"
#include "..\operacoes\operacoes.c"
#include <stdio.h>
int soma, soma2, soma3;

int potencia(int x,int y){
	if(y==1)
		return x;
	else
		return multiplicacao(x,potencia(x,y-1));}

int serie(int n){
	if(n==1)
		return 2;
	else
		return (potencia(2,n)+serie(n-1));
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


