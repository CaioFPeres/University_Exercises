#include <stdio.h>
#include <stdlib.h>


int main (){

    int colunas, linhas = 3, maior = 0;

    //le colunas
    scanf("%i", &colunas);

    //declara matriz 1
    int matriz[linhas][colunas];

    //declara matriz 2
    int matrizAux[linhas][colunas];

    //le a entrada
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            scanf("%i", &matriz[i][j]);
        }
    }


    //coloca a primeira coluna na matriz aux
    for(int i = 0; i < linhas; i++){
        matrizAux[i][0] = matriz[i][0];
    }


    //calcula as possibilidades de soma e pega a maior e coloca na matrizAux
    for(int j = 1; j < colunas; j++){
        for(int i = 0; i < linhas; i++){

            if(matriz[i][j] + matrizAux[i][j-1] > matriz[i][j] + matrizAux[(i+1) % 3][j-1]){
                matrizAux[i][j] = matriz[i][j] + matrizAux[i][j-1];
            }
            else{
                matrizAux[i][j] = matriz[i][j] + matrizAux[(i+1) % 3][j-1];
            }

        }
    }


    //verifica qual é a maior soma da ultima coluna da matrizAux
    maior = matrizAux[0][colunas - 1];

    for(int i = 1; i < linhas; i++){
        if(maior < matrizAux[i][colunas - 1]){
            maior = matrizAux[i][colunas - 1];
        }
    }


    //a complexidade é O(n) pois precisa passar por todos os elementos da matriz original


    printf("%i\n", maior);




    return 0;
}