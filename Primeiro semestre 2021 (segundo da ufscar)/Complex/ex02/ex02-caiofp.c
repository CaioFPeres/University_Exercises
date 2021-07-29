#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void merge(int vetor[], int e, int m, int d)
{
    int i, j, k;
    int tam1 = m - e + 1;
    int tam2 = d - m;
 
    //cria vetor temporario
    int E[tam1], D[tam2];
 
    //copia
    for (i = 0; i < tam1; i++)
        E[i] = vetor[e + i];

    for (j = 0; j < tam2; j++)
        D[j] = vetor[m + 1 + j];
 
    //juncao
    i = 0;
    j = 0;
    k = e;

    while (i < tam1 && j < tam2) {
        if (E[i] <= D[j]) {
            vetor[k] = E[i];
            i++;
        }
        else {
            vetor[k] = D[j];
            j++;
        }
        k++;
    }
 

    while (i < tam1) {
        vetor[k] = E[i];
        i++;
        k++;
    }
 

    while (j < tam2) {
        vetor[k] = D[j];
        j++;
        k++;
    }
}


void mergeSort(int vetor[], int e, int d)
{
    if (e < d) {

        int m = e + (d - e) / 2;
 
        // ordena as metades
        mergeSort(vetor, e, m);
        mergeSort(vetor, m + 1, d);

        merge(vetor, e, m, d);
    }
}


int buscaBinariaDiferente(int vetor1[], int vetor2[], int fator, int tam){

    int i = 0;
    int j = tam - 1;
    int achou = 0;

    while(i < tam && j >= 0){

        if(vetor1[i] * vetor2[j] == fator){
            achou = 1;
            break;
        }
        
        if(vetor1[i] * vetor2[j] < fator){
            i++;
        }
        else{
            j--;
        }

    }

    return achou;
}


int main (){

    int tam, fator, achou = 0;

    scanf("%i", &tam);
    scanf("%i", &fator);


    int vetor1[tam];
    int vetor2[tam];


    for(int k = 0; k < tam; k++){
        scanf("%i", &vetor1[k]);
    }

    for(int k = 0; k < tam; k++){
        scanf("%i", &vetor2[k]);
    }


    // organiza os vetores com o mergesort
    mergeSort(vetor1, 0, tam-1);
    mergeSort(vetor2, 0, tam-1);

    
    if(vetor1[0] < vetor2[0]){
        achou = buscaBinariaDiferente(vetor1, vetor2, fator, tam);
    }
    else{
        achou = buscaBinariaDiferente(vetor2, vetor1, fator, tam);
    }


    if(achou == 1)
        printf("SIM\n");
    else
        printf("NAO\n");



    return 0;
}