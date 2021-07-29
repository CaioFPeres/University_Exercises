#include "operacoes.h"

int multiplicacao(int x, int y){
	int i,soma=0;
	for(i=0;i<y;i++){
		soma= soma + x;}
	return soma;}

int fatorial(int x) {
	int i;
	int r=1;
	for(i=1;i<=x;i++){
		r= multiplicacao(i, r)+r;
	}
	return r;
}

int divi(int a, int b) {

    int c;
    while(a>=b)
    {
        c+=1;
    }
    return c;
}

