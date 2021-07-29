#include "..\series\series.c"

int main(){	

	int a,r;
	printf("Digite a quantidade de termos do somatorio: ");
	scanf("%d",&a);
	r = serie(a);
	printf("Resultado da Serie1 = %d\n",serie(a));
	
	serie2();
	printf("Resultado da Serie2: %i\n", soma);
	
	return 0;
}
