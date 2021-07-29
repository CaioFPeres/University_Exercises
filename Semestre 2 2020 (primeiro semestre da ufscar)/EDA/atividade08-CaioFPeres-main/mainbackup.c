#include <stdio.h>
#include <stdlib.h>
#include "queue.c"

struct node { 
   int w; 
   struct node *next; 
};
typedef struct node Node;

struct graph {
   int V; 
   int A; 
   Node **adj;
};
typedef struct graph Graph;



void inicializar(Graph *G, unsigned nvertices) {
   G->V = nvertices;
   G->A = 0;
   G->adj = (Node**)malloc(sizeof(Node*)*G->V);
   unsigned v;
   for(v = 0; v < G->V; v++)
      G->adj[v] = NULL;
}



void destroi (Graph *G){
	unsigned v;
   for(v = 0; v < G->V; v++){
      while( G->adj[v]){
         Node* l = G->adj[v];
         G->adj[v] = G->adj[v]->next;
         free(l);
      }
   }
   free(G->adj);
   G->V = G->A = 0;
}



void adiciona_arco(Graph *G, unsigned v, unsigned w) {
   Node* l = (Node*)malloc(sizeof(Node));
   l->w = w;
   l->next = G->adj[v];
   G->adj[v] = l;
   G->A++;
}



void dfs_private(Graph *G, int vis[], unsigned v, queue *q){
   vis[v] = 1;

   Node* n;
   for(n = G->adj[v]; n!= NULL; n = n->next)
      if(vis[n->w] == 0)
         dfs_private(G, vis, n->w, q);
      
   push(q, v);
}



queue* dfs(Graph *G){
   int vis[G->V];

   queue *q = (queue*)malloc(sizeof(queue));
   initialize(q);
	unsigned v;
   	
	for(v = 0; v < G->V; v++)
      vis[v] = 0;

   for(v = 0; v < G->V; v++)
      if(vis[v] == 0)
         dfs_private(G, vis, v, q);
   
   return q;
}



void printar(queue *q){

   queue *aux = q;
   
   while(!empty(aux)){
      printf("%i ", aux->first->data);
      aux->first = aux->first->next;
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

	//  w -> v
	while(i < A){
		adiciona_arco(G, w[i], v[i]);
      i++;
   }
	
	fclose(arq);

	return G;
}



int main(int argc, char *argv[]) { // você pode passar o nome do arquivo durante a execução do programa!

   Graph *G = leitura(argv[1]);
   queue *q = dfs(G);
   
   printar(q);

   destroi(G);
   destroy(q);

   free(G);

	return 0;
}
