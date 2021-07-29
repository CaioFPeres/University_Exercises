#include <iostream>

int soma(int v[], int ini, int fim){
	if(ini>fim)
	return 0;
	
	int meio= (ini+fim)/2;
	
	return v[(ini+fim)/2] + soma (v, ini, meio-1) + soma(v, meio+1, fim);
	
}

int main(int argc, char** argv) {
	return 0;
}
