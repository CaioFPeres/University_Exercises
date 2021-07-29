#include <stdio.h>

typedef struct tipo_aresta{
    int x;
    int y;
    int dis;
}tipo_aresta;


tipo_aresta *bubble_sort (tipo_aresta vetor[], int n) {
    int k, j;
	tipo_aresta aux[n];
	
		for (k = 1; k < n; k++) {
        for (j = 0; j < n-1; j++) {

            if (vetor[j].dis > vetor[j + 1].dis) {
                aux[j]  = vetor[j];
                vetor[j]   = vetor[j + 1];
                vetor[j + 1] = aux[j];
            }
        }
	}
	return vetor;
}


int main(){
	tipo_aresta vetor[10];
	int a, i;
	
	for(i=0;i<=10;i++){
		scanf("%i", &a);
		vetor[i].dis = a;
		vetor[i].x = i+1;
	}
	
	int n = sizeof(vetor)/sizeof(vetor[10]);
	bubble_sort(vetor, n);
	
	
	for(i=0;i<=10;i++){
		printf("x: %i dis: %i\n", vetor[i].x, vetor[i].dis);
}
	
}
