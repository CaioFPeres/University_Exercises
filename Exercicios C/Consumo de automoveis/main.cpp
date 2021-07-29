#include <iostream>

int main(int argc, char** argv) {
	float x, y, z, u;
	printf("Insira consumo do Carro (rodoviario ou urbano): ");
	scanf("%f", &x);
	printf("Insira preco do combustivel(use ponto ao inves de virgula): ");
	scanf("%f", &y);
	printf("Insira percurso a ser feito em Km(use ponto ao inves de virgula): ");
	scanf("%f", &z);
	u= (z/x)*y;
	printf("\nPreco a ser gasto: %f reais\n", u);
	printf("\n*******Beijo no cu*******\n\n");
	
	system("pause");
	return 0;
}
