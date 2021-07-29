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
   for(unsigned v = 0; v < G->V; v++)
      G->adj[v] = NULL;
}



void destroi (Graph *G){
   for(unsigned v = 0; v < G->V; v++){
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



void dfs_private(Graph *G, int vis[], unsigned v){
   vis[v] = 1;
   
   printf("%u ", v);

   for(Node* n = G->adj[v]; n!= NULL; n = n->next)
      if(vis[n->w] == 0)
         dfs_private(G, vis, n->w);
}



void dfs(Graph *G){
   
   int vis[G->V];
   
   for(unsigned v = 0; v < G->V; v++)
      vis[v] = 0;
   
   for(unsigned v = 0; v < G->V; v++)
      if(vis[v] == 0)
         dfs_private(G, vis, v);
}



void bfs(Graph *G){
   int vis[G->V];

   int i = 0;

   for(unsigned v = 0; v < G->V; v++)
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

            for(Node* n = G->adj[v]; n != NULL; n = n->next)
               if(vis[n->w] == 0){
                  vis[n->w] = 1;
                  push(&f, n->w);
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
