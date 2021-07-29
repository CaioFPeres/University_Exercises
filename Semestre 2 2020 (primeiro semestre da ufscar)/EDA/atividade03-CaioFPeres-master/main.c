#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fila_prioridade.h"


#define NUMEROS 1000
#define MIN 1000
#define MAX 8999

int main() {
	
    srand (time(NULL));

    fp ordenar;
    inicializa(&ordenar, NUMEROS );

    printf("Desordenados:\n");

    while(!cheia(&ordenar)) {
        int p = MIN + rand() % (MAX+1);
        insere(&ordenar, 'A', p );
        printf("%d ", p);
    }

    printf("\n\n\n%u elementos ordenados:\n", tamanho(&ordenar));


    while(!vazia(&ordenar)) {
        char removido;
        int prioridade = 0;
        maiorPrioridade(&ordenar, &removido, &prioridade );
        printf("%d ", prioridade);
        removeMaiorPrioridade(&ordenar);
	}

    printf("\n");

    destroi(&ordenar);
    
    
    return 0;
}
