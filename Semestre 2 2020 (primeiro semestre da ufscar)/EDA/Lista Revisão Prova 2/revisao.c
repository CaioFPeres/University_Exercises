#include <stdio.h>
#include <stdlib.h>
#include "queue.c"
#define INT_MAX 2147483647

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
			G->adj[i][j] = INT_MAX;
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


void adiciona_arco(Graph *G, unsigned v, unsigned w, int peso){
	if( G->adj[v][w] == INT_MAX){
		G->adj[v][w] = peso;
		G->A++;
	}
}



int minPeso(int key[], int mstSet[]) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < 9; v++) 
        if (mstSet[v] == 0 && key[v] < min) 
            min = key[v], min_index = v; 
  
    return min_index; 
} 


void primMSTFila(Graph *G) 
{ 
    // Create a priority queue to store vertices that 
    // are being preinMST. This is weird syntax in C++. 
    // Refer below link for details of this syntax 
    // http://geeksquiz.com/implement-min-heap-using-stl/ 
    queue pq;
    initialize(&pq);
    // Taking vertex 0 as source 
  
    // Create a vector for keys and initialize all 
    // keys as infinite (INF) 
    int key[9];
    for( int i = 0; i < 9; i++)
        key[i] = 0; 
  
    // To store parent array which in turn store MST 
    int parent[9]; 
    for( int i = 0; i < 9; i++)
        parent[i] = 0; 

    // To keep track of vertices included in MST 
    int inMST[9]; 
    for( int i = 0; i < 9; i++)
        inMST[i] = 0;
  
    // Insert source itself in priority queue and initialize 
    // its key as 0. 
    pushBack(&pq, 0); 
    key[0] = 0; 
  
    /* Looping till priority queue becomes empty */
    while (!empty(&pq)) 
    { 
        // The first vertex in pair is the minimum key 
        // vertex, extract it from priority queue. 
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted key (key must be first item 
        // in pair) 
        int u = front(&pq);  //aqui eh front mesmo
        popBack(&pq); 
  
        inMST[u] = 1;  // Include vertex in MST 
  
        // 'i' is used to get all adjacent vertices of a vertex 
        for (int i = 0; i != G->V; i++) 
        { 

            // Get vertex label and weight of current adjacent 
            // of u. 
            int v = G->adj[u][i];
            int weight = G->adj[u][i];

            printf("%i ", v);
  
            //  If v is not in MST and weight of (u,v) is smaller 
            // than current key of v 
            if (inMST[v] == 0 && key[v] > weight) 
            { 
                // Updating key of v 
                key[v] = weight; 
                pushBack(&pq, key[v]); 
                parent[v] = u; 
            } 
        } 
    } 
  
 /*   // Print edges of MST using parent array 
    for (int i = 1; i < 9; ++i) 
        printf("%d - %d\n", parent[i], i); 
*/

} 








void primMST(Graph *G) 
{ 
    // Array to store constructed MST
    int MST[9];
    // To represent set of vertices included in MST 
    int visitados[9]; 
    // Key values used to pick minimum weight edge in cut 
    int key[9]; 
  
    for (int i = 0; i < 9; i++){
        visitados[i] = 0; 
        MST[i] = 0;
        key[i] = INT_MAX;
    }
  
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0; 
    MST[0] = -1; // First node is always root of MST
  
    // The MST will have V vertices 
    for (int count = 0; count < 9 - 1; count++) { 
        // Pick the minimum key vertex from the 
        // set of vertices not yet included in MST
        int u = minPeso(key,visitados); 
  
        // Add the picked vertex to the MST Set 
        visitados[u] = 1;
  
        // Update key value and parent index of 
        // the adjacent vertices of the picked vertex. 
        // Consider only those vertices which are not 
        // yet included in MST 
        for (int v = 0; v < 9; v++){
            // graph[u][v] is non zero only for adjacent vertices of m 
            // mstSet[v] is false for vertices not yet included in MST 
            // Update the key only if graph[u][v] is smaller than key[v] 
            if (G->adj[u][v] && visitados[v] == 0 && G->adj[u][v] < key[v]) 
                MST[v] = u, key[v] = G->adj[u][v]; 
        }
    }

    // print the constructed MST 
    printf("Edge \tWeight\n"); 
    for (int i = 1; i < 9; i++) 
        printf("%d - %d \t%d \n", MST[i], i, G->adj[i][MST[i]]); 



/*
    for(int i = 0; i < 9; i++){
        printf("%i ", MST[i]);
    }
*/
} 



int main(int argc, char *argv[]){

    Graph *G = (Graph*)malloc(sizeof(Graph));

    inicializar(G, 9);

    adiciona_arco(G, 0, 1, 4);
    adiciona_arco(G, 0, 7, 8);
    adiciona_arco(G, 1, 7, 11);
    adiciona_arco(G, 1, 2, 8);
    adiciona_arco(G, 2, 8, 2);
    adiciona_arco(G, 8, 7, 7);
    adiciona_arco(G, 8, 6, 6);
    adiciona_arco(G, 7, 6, 1);
    adiciona_arco(G, 6, 5, 2);
    adiciona_arco(G, 5, 2, 4);
    adiciona_arco(G, 2, 3, 7);
    adiciona_arco(G, 3, 5, 14);
    adiciona_arco(G, 3, 4, 9);
    adiciona_arco(G, 4, 5, 10);


    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(G->adj[i][j] != INT_MAX);
            adiciona_arco(G, j, i, G->adj[i][j]);
        }
    }


    //primMST(G);


    queue *q = (queue*)malloc(sizeof(queue));
    initialize(q);


/*
    pushFrontPrioridade(q, 10);
    pushFrontPrioridade(q, 9);
    pushFrontPrioridade(q, 8);
    pushFrontPrioridade(q, 7);
    pushFrontPrioridade(q, 6);
*/    pushFrontPrioridade(q, 2);
    pushFrontPrioridade(q, 3);
//    pushFrontPrioridade(q, 4);
//    pushFrontPrioridade(q, 5);
//    pushFrontPrioridade(q, 0);

/*
    while(q->first != q->last){
        printf("%i ", q->first->data);
        q->first = q->first->next;
    }
    printf("%i  ", q->last->data);
*/


/*
    int i = 0;
    while(i != 11){
        printf("%i ", q->first->data);
        q->first = q->first->next;
    
        i++;
    }

    */

/*
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){

            printf("\ni: %i, j: %i, G: %i ", i, j, G->adj[i][j]);

        }
    }
*/


}