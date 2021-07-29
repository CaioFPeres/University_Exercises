#include <stdio.h>
#include <stdlib.h>
#include "fila_prioridade.h"

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
   for(v = 0; v < G->V; v++){
      G->adj[v] = NULL;
   }
}



void destroiG(Graph *G){
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



void adiciona_arco(Graph *G, unsigned v, unsigned w, int indegree[]) {
   Node* l = (Node*)malloc(sizeof(Node));
   l->w = w;
   indegree[w]++;
   l->next = G->adj[v];
   G->adj[v] = l;
   G->A++;
}



void TopologicalSortKahn(Graph *G, int indegree[]){

   fp q;
   inicializa(&q, G->V);
   int v;
   int prioridade;
   Node *n;
   int vetor[G->V];
   int count = 0;


   while(count != G->V){
      vetor[count++] = 0;
   }


   for( v = 0; v < G->V; v++){
      if(indegree[v] == 0){
         insere(&q, v, G->V - v);
      }
   }

   count = 0;

   while(!vazia(&q)){

      maiorPrioridade(&q, &v, &prioridade);
      removeMaiorPrioridade(&q);

      vetor[count++] = v;

      for(n = G->adj[v]; n != NULL; n = n->next){
         indegree[n->w]--;
      
         if(indegree[n->w] == 0)
            insere(&q, n->w, G->V - n->w);
      }

   }


   if(count != G->V){
      printf("*");
      return;
   }

   count = 0;

   while(count != G->V){
      printf("%i\n", vetor[count++]);
   }




   //salvar em arquivo para facilitar a verificacao de igualdade

   count = 0;

   FILE *arq;
   arq = fopen("saida.txt", "w");

   while(count != G->V){
      fprintf(arq, "%i\n", vetor[count++]);
   }


   destroi(&q);

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
   int indegree[V];

   for(j = 0; j < V; j++){
      indegree[j] = 0;
   }

	inicializar(G, V);

	while(fscanf (arq, "%u", &v[i]) > 0){
		fscanf (arq, "%u", &w[i]);
		i++;
	}

	i = 0;

	//  v -> w
	while(i < A){
		adiciona_arco(G, v[i], w[i], indegree);
      i++;
   }

   TopologicalSortKahn(G, indegree);
	
	fclose(arq);

	return G;
}



int main(int argc, char *argv[]) { // você pode passar o nome do arquivo durante a execução do programa!

   Graph *G = leitura(argv[1]);
   
   destroiG(G);
   
   free(G);

	return 0;
}
