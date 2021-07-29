//
//  reduzindo_detalhes_em_um_mapa.cpp
//  programas2
//
//  Created by Lucca Siaudzionis on 24/02/13.
//  Copyright (c) 2013 Luccasiau. All rights reserved.
//

#include <cstdio>
#include <algorithm>
#define MAXN 510
#define MAXM 124755
using namespace std;

int nodes,arestas;
int pai[MAXN];
int peso[MAXN];

int find(int x){ // função do Union Find
    if( pai[x] == x ) return x;
    return pai[x] = find(pai[x]);
}

int join(int a,int b){ // função do Union Find
    a = find(a);
    b = find(b);
    
    if(peso[a] < peso[b]) pai[a] = b;
    else if(peso[b] < peso[a]) pai[b] = a;
    else{
        pai[a] = b;
        peso[b]++;
    }
    
}

struct tipo_aresta{
    int x;
    int y;
    int dis;
};

bool comp(tipo_aresta a, tipo_aresta b){ // função para ordenação
    return a.dis < b.dis;
}

tipo_aresta edges[MAXM];

int main(){
    
    scanf("%d %d",&nodes,&arestas);
    
    for(int i = 1;i<=nodes;i++) pai[i] = i;
    
    for(int i = 1;i<=arestas;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        edges[i].x   = a;
        edges[i].y   = b;
        edges[i].dis = c;
    }
    
    sort(edges+1,edges+arestas+1,comp); // ordenar as arestas em ordem crescente
    
	for(int i=1;i<=arestas;i++){
		printf("\nx: %i dis: %i", edges[i].x, edges[i].dis);}
    
    int resp = 0;
    
    for(int i = 1;i<=arestas;i++){
        
        // só se usa uma arestas se seus dois vértices
        // estiverem em componentes distintas
        
        if(find(edges[i].x) != find(edges[i].y)){
            resp += edges[i].dis;
            join(edges[i].x, edges[i].y);
        }

    }
    
    printf("\n%d\n",resp);
    
    return 0;
}
