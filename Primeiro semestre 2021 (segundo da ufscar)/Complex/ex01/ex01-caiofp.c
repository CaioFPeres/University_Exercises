#include <stdio.h>


int main(){

    int somaAteAqui = 0, proxSoma = 0;
    int tam, elem;

    scanf("%i", &tam);
 
    for (int i = 0; i < tam; i++){
        
        scanf("%i", &elem);

        proxSoma = proxSoma + elem;

        if (proxSoma > somaAteAqui)
            somaAteAqui = proxSoma;
 
        if (proxSoma < 0)
            proxSoma = 0;

    }

    printf("%i\n", somaAteAqui);

    return 0;

}