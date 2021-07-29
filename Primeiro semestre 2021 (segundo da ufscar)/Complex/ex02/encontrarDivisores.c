#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// funcao otimizada
int proxPrimo(int p) {

    if(p == 0 || p == 1)
        return 2;

    if(p == 2)
        return 3;

    p = p + 1;

    if (p % 2 == 0)
        p++;

    for (int i = 3; i <= sqrt(p); i += 2) {
        if (p % i == 0) {
            p += 2;
            i = 1;
        }
    }

    return p;
}


int compareFunc(int* x, int* y){

    if(*x == *y)
        return 0;
    if(*x > *y)
        return 1;
    else
        return -1;
}


void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 

int partition (int arr[], int inicio, int fim)
{
    int pivot = arr[fim];
    int i = (inicio - 1);
 
    for (int j = inicio; j <= fim - 1; j++){

        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[fim]);

    return (i + 1);
}
 

void quickSort(int arr[], int inicio, int fim)
{
    if (inicio < fim)
    {

        // indice particionado
        int pi = partition(arr, inicio, fim);
 
        // ordenar antes e depois da particao
        quickSort(arr, inicio, pi - 1);
        quickSort(arr, pi + 1, fim);
    }
}


int main (){

    int tam, fator, divisao, divisorPrimo = 2, primoAnterior = 2, qtd_divisores = 1, qtd_primos_distintos = 0, num = 0, flag = 0, resultado = 0;
    int* search, search2;

    scanf("%i", &tam);
    scanf("%i", &fator);

    divisao = fator;


    // tamanhos um pouco arbitrários, porém calcular o tamanho do vetor de divisores acrescenta mais complexidade
    int* vetor1 = malloc(sizeof(int)*tam);
    int* vetor2 = malloc(sizeof(int)*tam);
    int* divisores = malloc(sizeof(int)*fator);
    
    // esse vetor guarda o numero de vezes que o divisor primo apareceu, em ordem de numeros primos. Exemplo: posicao 0 possui o numero de vezes que o numero 2 aparece, e assim por diante.
    int* divisoresPrimos = malloc(sizeof(int)*fator);


    //atribui 0 em tudo
    for(int i = 0; i < fator; i++){
        divisores[i] = 0;
        divisoresPrimos[i] = 0;
    }

    // o primeiro divisor de qualquer numero é o 1
    divisores[0] = 1;


    for(int i = 0; i < tam; i++){
        scanf("%i", &vetor1[i]);
    }


    for(int i = 0; i < tam; i++){
        scanf("%i", &vetor2[i]);
    }


    // organiza os vetores com o quicksort
    quickSort(vetor1, 0, tam-1);
    quickSort(vetor2, 0, tam-1);



    // esse trecho é responsavel por encontrar todos os divisores do fator

    // video utilizado como referencia para entender os processos matemáticos: https://www.youtube.com/watch?v=zXEoBoZiPsw

    //enquanto ainda não encontrou todos os divisores
    while (divisao != 1){

        //verifica se a divisao atual é divisivel pelo primo atual
        while(divisao % divisorPrimo == 0){
            
            //se for, divide e atribui na divisao
            divisao = divisao / divisorPrimo;

            //se o primo atual for igual ao anterior, é necessário fazer coisas especificas
            if(divisorPrimo == primoAnterior){

                //se for o primeiro numero primo possivel, ele só multiplica pelo divisor anterior
                if(primoAnterior == 2){
                    divisores[qtd_divisores] = divisorPrimo * divisores[qtd_divisores-1];
                    qtd_divisores++;
                }
                else{

                    //essa variavel representa a quantidade de divisores que um divisor primo pode acrescentar ao total de divisores.
                    //em outras palavras, nesse caso ele está aparecendo pela segunda vez ou mais e não é o numero dois, portanto 
                    //supondo que o primo atual seja o numero 3, se o 2 apareceu 3 vezes, o primo 3 acrescentará o numero de vezes que o 2 apareceu + 1, vezes a quantidade de primos distintos até então
                    // n3*(n2 + 1)...  n5*(n3*(n2 + 1))...   e assim vai
                    int qtd_divisores_numero = divisoresPrimos[0] + 1;
                    
                    for(int i = 1; i <= qtd_primos_distintos; i++){
                        qtd_divisores_numero = qtd_divisores_numero * divisoresPrimos[i];
                    }


                    int limite = qtd_divisores;

                    for(int i = qtd_divisores - qtd_divisores_numero; i < limite; i++){

                        divisores[qtd_divisores] = divisorPrimo * divisores[i];
                        qtd_divisores++;
                    
                    }
                
                }
            }
            //se o primo atual for um numero diferente do anterior:
            else{
                
                qtd_primos_distintos++;
                
                int limite = qtd_divisores;
                
                for(int i = 0; i < limite; i++){
                    divisores[qtd_divisores++] = divisorPrimo * divisores[i];
                }
            
            }

            divisoresPrimos[qtd_primos_distintos]++;

            primoAnterior = divisorPrimo;
        }

        divisorPrimo = proxPrimo(divisorPrimo);
    }



    // agora ja temos o vetor de divisores do numero fora de ordem (mas nao precisa ordenar)
    
    // agora precisamos procurar os divisores nos vetores
    // é possivel que ele encontre divisores em um dos vetores que não terão fatores correspondentes ( não compoem o numero dos quais pegamos todos os divisores)
    // portanto é necessário fazer o processo novamente, sem passar pelo elemento já investigado

    int i = 0;

    while(search2 == NULL && qtd_divisores != 0){

        search = NULL;

        while(qtd_divisores != 0){

            // faz busca binaria no vetor1
            if(divisores[i] > vetor1[0] && divisores[i] < vetor1[tam]){

                search = bsearch(&divisores[i], vetor1, tam, sizeof(int), compareFunc);

                if(search){

                    flag = 1;
                    resultado = *search;

                    divisores[i] = divisores[qtd_divisores - 1];
                    qtd_divisores--;

                    break;
                }

            }


            // faz busca binaria no vetor2
            if(divisores[i] > vetor2[0] || divisores[i] < vetor2[tam]){

                search = bsearch(&divisores[i], vetor2, tam, sizeof(int), compareFunc);

                if(search){

                    flag = 2;
                    resultado = *search;

                    divisores[i] = divisores[qtd_divisores - 1];
                    qtd_divisores--;
                    
                    break;
                }

            }


            divisores[i] = divisores[qtd_divisores - 1];
            qtd_divisores--;

        }

        
        if(search == NULL){
            printf("NAO");
            return 0;
        }


        //encontrou um divisor do numero em um dos vetores
        //agora precisa encontrar o numero do fator dividido pelo divisor encontrado (o outro fator)

        int key = fator/resultado;

        if(flag == 1){
            search2 = bsearch(&key, vetor2, tam, sizeof(int), compareFunc);
        }
        else{
            search2 = bsearch(&key, vetor1, tam, sizeof(int), compareFunc);
        }

    }
    

    if(search2 == NULL){
        printf("NAO");
    }
    else{
        printf("SIM");
    }


    return 0;
}