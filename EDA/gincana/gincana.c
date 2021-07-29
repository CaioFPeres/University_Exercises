#include <stdio.h>
#define MAXN 1100


int pai[MAXN], peso[MAXN];



int find(int x){ //funcao do Union-Find para encontrar patriarca

	if(pai[x]==x)
		return x;

	return pai[x]=find(pai[x]);
}



int join(int x, int y){ // funcao do Union-Find para unir conjuntos


	x=find(x);
	y=find(y);


	if(x==y) return;


	if(peso[x]>peso[y])
		pai[y]=x;

	if(peso[x]<peso[y])
		pai[x]=y;

	if(peso[x]==peso[y]){

		pai[x]=y;
		peso[y]++;
	}

}



int main(){

	int a, b, i, n, m, resp=0;


	scanf("%i %i", &n, &m);

	for(i=1;i<=n;i++){

		pai[i]=i;
	}

	for(i=1;i<=m;i++){

		scanf("%i %i", &a, &b);
		join(a, b);
	}

	for(i=1;i<=n;i++){
		if(find(i)==i)
			resp++;
	}

	printf("%i\n", resp);

	return 0;
}
