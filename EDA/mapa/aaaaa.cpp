#include <cstdio>
#include <algorithm>
#define MAXN 510
#define MAXM 124755
using namespace std;

int nodes,arestas;
int pai[MAXN];
int peso[MAXN];

int find(int x){
    if( pai[x] == x ) return x;
    return pai[x] = find(pai[x]);
}

int join(int a,int b){
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

bool comp(tipo_aresta a, tipo_aresta b){
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

    sort(edges+1,edges+arestas+1,comp);

    int resp = 0;

    for(int i = 1;i<=arestas;i++){

        if(find(edges[i].x) != find(edges[i].y)){
            resp += edges[i].dis;
            join(edges[i].x, edges[i].y);
        }
    }

    printf("%d\n",resp);

    return 0;
}
