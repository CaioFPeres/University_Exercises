#include <stdio.h>
#define MAXN 500
#define MAXM 124750

typedef struct tipo_aresta{

    int x;
    int y;
    int dis;

}tipo_aresta;


int no,arestas;
int pai[MAXN];
int tamanho[MAXN];
tipo_aresta vetArestas[MAXM];


int find(int x){ // função do Union Find para encontrar patriarca

    if( pai[x] == x )
		return x;

    return pai[x] = find(pai[x]);
}


void join(int a, int b){ // função do Union Find para unir 2 conjuntos

    a = find(a);
    b = find(b);

    if(tamanho[a] < tamanho[b])
		pai[a] = b;

    else if(tamanho[b] < tamanho[a])
		pai[b] = a;

    else{
        pai[a] = b;
        tamanho[b]++;
    }

}





void quick_sort(tipo_aresta *vetor, int prim, int ulti) {
    int i, j, x, k;
    tipo_aresta aux[ulti];
     
    i = prim;
    j = ulti;
    k = (prim + ulti) / 2;
    x = vetor[k].dis;

    while(i <= j) {
        while(vetor[i].dis < x && i < ulti) {
            i++;
        }
        while(vetor[j].dis > x && j > prim) {
            j--;
        }
        if(i <= j) {
            aux[i] = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux[i];
            i++;
            j--;
        }
    }
     
    if(j > prim) {
        quick_sort(vetor, prim, j);
    }
    if(i < ulti) {
        quick_sort(vetor, i, ulti);
    }
}



int main(){

	int a, b, c, i, resp=0;

    scanf("%d %d", &no, &arestas);

    for(i=1;i<=no;i++)
		pai[i] = i;

    for(i=1;i<=arestas;i++){

        scanf("%d %d %d", &a, &b, &c);
        vetArestas[i].x   = a;
        vetArestas[i].y   = b;
        vetArestas[i].dis = c;
    }



	quick_sort(vetArestas, 0, arestas);

    for(i=1;i<=arestas;i++){

        if( find(vetArestas[i].x) != find(vetArestas[i].y) ){

		    resp = resp + vetArestas[i].dis;
            join(vetArestas[i].x, vetArestas[i].y);
        }

    }

    printf("%d\n", resp);

    return 0;
}
