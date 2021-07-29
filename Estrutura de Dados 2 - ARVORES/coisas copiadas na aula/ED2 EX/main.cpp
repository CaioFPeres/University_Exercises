#include <iostream>



void imprimeVetorRec(int v[], int n){
if (n<=0) return; //checagem de instancia trivial (vazio);
printf("%i", v[0]);
imprimeVetorRec(v+1, n-1);
}







int main(int argc, char** argv) {
	return 0;
}
