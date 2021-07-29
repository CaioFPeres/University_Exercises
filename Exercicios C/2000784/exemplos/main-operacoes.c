#include "..\operacoes\operacoes.c"
#include <stdio.h>

int main(int argc, char** argv){
	int x,y;
	int a,b;
	printf("Digite um numero e seu fator multiplicador: ");
	scanf("%i", &x);
	scanf("%i", &y);
	printf("Soma: %i\n", multiplicacao(x, y));
	
	printf("Informe numero fatorial: ");
	scanf("%i", &x);
	printf("Fatorial: %i\n", fatorial(x));
	
	printf("Informe dividendo e divisor: ");
	scanf("%i%i",&a,&b);
	printf("Quociente: %i", div(a, b));
}
