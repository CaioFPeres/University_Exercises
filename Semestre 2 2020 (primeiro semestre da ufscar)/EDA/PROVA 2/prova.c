#include <stdio.h>
#include <stdlib.h>
#include "fila_prioridade.c"
#include "queue.c"

#define INT_MAX 2147483647


struct graph {
	int V; 
	int A; 
	int **adj; 
};
typedef struct graph Graph;


typedef struct {
	 int V; 
	 int A;
	int **adj; 
} G_matrix;



typedef struct node *link;

struct node { 
	int v; 
	link next; 
}; 


typedef struct { 
	int V; 
	int A; 
	link *adj; 
} G_list;



void matrix2list(G_matrix *m, G_list *l){

	l->V = m->V;
	l->A = 0;
	l->adj = (link*)malloc(sizeof(link)*m->V);
	for(unsigned v = 0; v < m->V; v++)
		m->adj[v] = NULL;


	for(int i = 0; i < m->V; i++){
		for(int j = 0; j < m->V; j++){
			if(m->adj[i][j] != 0){
				link li = (link)malloc(sizeof(struct node)*m->V);
				li->v = j;
				li->next = l->adj[i];
				l->adj[i] = li;
				l->A++;
			}
		}
	}


}


void bfs(G_list *g){
   int vis[g->V];

   int i = 0;

   for(unsigned v = 0; v < g->V; v++)
      vis[v] = 0;

   queue f;
   initialize(&f);
   

   while(i < g->V){

		if(vis[i] == 0){
			push(&f, i);
			vis[i] = 1;

			while( !empty(&f)){
            unsigned v = front(&f);
            pop(&f);

            printf("%u ", v);

            for(link n = g->adj[v]; n != NULL; n = n->next)
               if(vis[n->v] == 0){
                  vis[n->v] = 1;
                  push(&f, n->v);
               }
			   
         }

    }

	i++;

   }

}



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


void destroiG(Graph *G){
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



int minDistance(Graph *G, int dist[], int sptSet[]) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < G->V; v++) 
        if (sptSet[v] == 0 && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 



void dijkstra(Graph *G) 
{ 
    int dist[G->V]; // The output array.  dist[i] will hold the shortest 
    // distance from src to i 
  
    int sptSet[G->V]; // sptSet[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 
  
    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < G->V; i++) 
        dist[i] = INT_MAX, sptSet[i] = 0; 
  
    // Distance of source vertex from itself is always 0 
    dist[0] = 0; 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < G->V - 1; count++) { 
        // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration. 
        int u = minDistance(G, dist, sptSet); 
  
        // Mark the picked vertex as processed 
        sptSet[u] = 1; 

        // Update dist value of the adjacent vertices of the picked vertex. 
        for (int v = 0; v < G->V; v++)
            // Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to  v through u is 
            // smaller than current value of dist[v] 
            if (!sptSet[v] && G->adj[u][v] && dist[u] != INT_MAX && dist[u] + G->adj[u][v] < dist[v]) 
                dist[v] = dist[u] + G->adj[u][v];
  
  
    } 

 
    // print the constructed distance array 
    printf("Vertex   Distance from Source\n"); 
    for (int i = 0; i < G->V; i++) 
        printf("%d tt %d\n", i, dist[i]);


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
    int j = 0;

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
    
    //dijkstra(G);
	
	fclose(arq);

	return G;
}



int main(int argc, char *argv[]) { // você pode passar o nome do arquivo durante a execução do programa!

    G_list *G = leitura(argv[1]);



	//matrix2list(G, GList);
/*

	for(int i = 0; i<G->V; i++){
		for(int j = 0; j<G->V; j++){
			if(G->adj[i][j] != NULL)
				printf("%i ", GList->adj[i][j]);
		}
	}
*/
   
    destroiG(G);
   
    free(G);

	return 0;
}
