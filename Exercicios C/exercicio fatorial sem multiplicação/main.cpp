#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
using namespace std;

int i, soma=0, a, b;
int x;
int y;
int r;

int multiplicacao(int x, int y){
	for(i=0;i<y;i++){
		soma= soma + x;}
	return soma;}

int fatorial(int x) {
		for(i=0;i<x;i++)
		{
			r=multiplicacao(i, r);
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

int main(int argc, char** argv){
		
	printf("Digite um numero e seu fator multiplicador: ");
	scanf("%i", &x);
	scanf("%i", &y);
	printf("Multiplicacao: %i\n", multiplicacao(x, y));
	
	printf("Informe numero fatorial: ");
	scanf("%i", &x);
	printf("Fatorial: %i\n", fatorial(x));
	
	printf("Informe dividendo e divisor: ");
	scanf("%i%i",&a,&b);
	printf("Quociente: %i", div(a, b));
}
