#include <stdio.h>
#include "avl.h"
#include "avl.c"

int main() {

	int a, p, e, g;
	
	avl pocoes, embalagens;
	inicializar(&pocoes);
	inicializar(&embalagens);
	
	int i = 0;
	
	scanf("%d", &p);
	for(i=0;i<p; i++) {
		scanf("%d", &a);
		inserir(&pocoes,a);
	}

	scanf("%d", &e);
	for(i=0;i<e; i++) {
		scanf("%d", &a);
		inserir(&embalagens, a);
	}
	
	scanf("%d", &g);
	for(i=0;i<g; i++) {
		scanf("%d", &a);
		int vpiso, vteto;
		if( piso(&pocoes, a, &vpiso) && teto(&embalagens, a, &vteto) )
			printf("%d %d\n", vpiso, vteto);
		else 
			printf("descartar\n");
	}
	
	destruir(&pocoes);
	destruir(&embalagens);
	
	return 0;
}
