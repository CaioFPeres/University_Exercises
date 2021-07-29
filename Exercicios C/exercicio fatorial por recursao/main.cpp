#include <iostream>

	int y=1, x=0;
	int recursao(){
			y= y*x;
			x--;
		if(x>1){
		recursao(); 
		}
	}

int main(int argc, char** argv) {

    
    printf("Insira um valor para o qual deseja calcular seu fatorial: ");
    scanf("%d", &x);
	recursao();

    printf("\nFatorial calculado: %d", y);
	
	return 0;
}
