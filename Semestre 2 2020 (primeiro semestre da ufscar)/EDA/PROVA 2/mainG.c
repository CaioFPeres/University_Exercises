#include <stdio.h>
#include <stdlib.h>
#include "queue.c"

struct graph {
	int V; 
	int A; 
	int **adj; 
};
typedef struct graph Graph;


void limpa(Graph *G){
	
	int i = 0;
	int j = 0;

	for(i = 0; i<G->V; i++){
		for(j = 0; j<G->V; j++){
			G->adj[i][j] = 0;
		}
	}

}


void inicializar(Graph *G, unsigned nvertices){
	G->V = nvertices;
	G->A = 0;
	G->adj = (int**)malloc(sizeof(int*)*G->V);
	unsigned v = 0;
	for(v = 0; v< G->V; v++)
		G->adj[v] = (int*)malloc(sizeof(int)*G->V);

	limpa(G);
}


void destroi(Graph *G){
	unsigned v=0;
	for(v=0;v<G->V; v++)
		free(G->adj[v]);
	free(G->adj);
	G->V = G->A = 0;
}


void adiciona_arco(Graph *G, unsigned v, unsigned w){
	if( G->adj[v][w] == 0){
		G->adj[v][w] = 1;
		G->A++;
	}
}


void dfs_private(Graph *G, int vis[], unsigned v){
	vis[v] = 1;
	printf("%u ", v);
	
	unsigned w = 0;
	for(w = 0; w < G->V; w++){
		if(G->adj[v][w] == 1)
			if(vis[w] == 0)
				dfs_private(G, vis, w);
	}

}


void dfs(Graph *G){
	int vis[G->V];

	unsigned v = 0;
	for(v = 0; v < G->V; v++)
		vis[v] = 0;
	for(v = 0; v < G->V; v++)
		if(vis[v] == 0)
			dfs_private(G, vis, v);
}


void bfs(Graph *G){
	int vis[G->V];

	unsigned v = 0;
	int i = 0;

	for(v = 0; v < G->V; v++)
		vis[v] = 0;

	queue f;
	initialize(&f);
	

	while(i < G->V){

		if(vis[i] == 0){
			push(&f, i);
			vis[i] = 1;

			while( !empty(&f)){
				unsigned v = front(&f);
				pop(&f);

				printf("%u ", v);
				unsigned w = 0;
				for(w = 0; w < G->V; w++)
					if(G->adj[v][w] == 1)
						if(vis[w] == 0){
							vis[w] = 1;
							push(&f, w);
						}
			}

		}

		i++;
	}

}


Graph* leitura( char nome[] ) {
   
	FILE *arq;
	arq = fopen(nome, "r");
	int V;
	int A;

	fscanf(arq, "%i", &V);
	fscanf(arq, "%i", &A);

	unsigned v[A];
	unsigned w[A];

	int i = 0;

	Graph *G = (Graph*)malloc(sizeof(Graph));

	inicializar(G, V);
	
	
	while(fscanf (arq, "%u", &v[i]) > 0){
		fscanf (arq, "%u", &w[i]);
		i++;
	}

	i = 0;

	//  v -> w
	while(i < A){
		adiciona_arco(G, v[i], w[i]);
		i++;
	}

	i = 0;

	//  w -> v
	while(i < A){
		adiciona_arco(G, w[i], v[i]);
		i++;
	}

	G->A = G->A/2;
	
	
	fclose(arq);

	return G;

}




int main(int argc, char *argv[]) { // você pode passar o nome do arquivo durante a execução do programa!

   	Graph *G = leitura(argv[1]);


	dfs(G);
	printf("\n");
	printf("\n");
	bfs(G);


	printf("\n%i ", G->A);

	destroi(G);
	free(G);

	return 0;
}