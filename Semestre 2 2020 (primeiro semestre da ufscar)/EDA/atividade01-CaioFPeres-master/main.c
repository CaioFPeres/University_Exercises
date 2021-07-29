#include <stdio.h>
#include "pilha.h"

#define TAMANHO_MAXIMO 100000

int verifica(char exp[]) {

	pilha bal = inicializa();
    int i = 0, erro = 0;
	while(!erro && exp[i] != '\0') {
		if( exp[i] == '(' || exp[i] == '[' ||exp[i] == '{' )
			empilha(bal, exp[i]);
		else {
            char t;
			if(topo(bal,&t)) {
                if( t == '(' && exp[i] == ')' )
				    desempilha(bal);
			    else if( t == '[' && exp[i] == ']' )
				    desempilha(bal);
			    else if( t == '{' && exp[i] == '}' )
				    desempilha(bal);
			    else
                    erro = 1;
            } else
                erro = 1;
		}
        i++;
	}
	if( !erro && vazia(bal) ) {
        destroi(bal);
		return 1;
    }
    destroi(bal);
	return 0;
}



int main() {

	char entrada[TAMANHO_MAXIMO+1];
	int nentradas;

	scanf("%d", &nentradas);
	fflush(stdin);
	
	while( nentradas-- ) {
		scanf("%s", &entrada);
		fflush(stdin);
		
		if( verifica(entrada) )
			printf("S\n");
		else
			printf("N\n");
	
	
	}
	
	return 0;


}





