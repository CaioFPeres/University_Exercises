#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct n_inteiros{

        int vetor[100];
        int qtd;

}Ninteiros;

void Adicionar(Ninteiros *a);
int nElementos(Ninteiros *a);
void Remover(int n, Ninteiros *a);
void Imprimir(Ninteiros *a);

int main()
{
    int i,op,n;
    Ninteiros *lista=(Ninteiros *)malloc(sizeof(Ninteiros));

    printf("\nQuantos valores voce quer armazenar? ");
    scanf("%d",&lista->qtd);
    lista->qtd += 1;                                      

    for(i=0;i<lista->qtd-1;i++)
    {
        printf("\nDigite um numero inteiro para V[%d]: ",i+1);
        scanf("%d",&*lista->vetor+i);
    }
    *(lista->vetor+i)=-12;                                


    do{
    printf("\nDigite: \n1-Adicionar elemento\n2-Saber a qtd de elementos\n3-Remover um elemento\n4-Imprimir os elementos\n0-Sair\n");
    scanf("%d",&op);
    switch(op){

        case 1: Adicionar(lista);
        break;
        case 2: nElementos(lista);
        break;
        case 3:     printf("\nDigite o elemento que quer remover: ");
                    scanf("%d",&n);
                    Remover(n,lista);
        break;
        case 4: Imprimir(lista);
        break;
    }
    }while(op!=0);

return 0;
}

void Adicionar(Ninteiros *a)
{
    int num,i,j;

    if(a->qtd-1 == 100)
    {
        printf("\nERRO: LISTA CHEIA!\n");
    }
    else
    {

        printf("\nDigite o numero que quer adicionar: ");
        scanf("%d",&num);
        for(i=0;i<a->qtd;i++)
        {
            if(*(a->vetor+i)==-12)
                {
                    j=i+1;
                    *(a->vetor+i)= num;
                    *(a->vetor+j) = -12;
                }
        }
        a->qtd+=1;
    }
}
int nElementos(Ninteiros *a)
{
    printf("\nA qtd de elementos guardada na lista eh: %d\n",a->qtd-1);
 return a->qtd-1;
}
void Remover(int n, Ninteiros *a)
{
   int i=0,j;

    while(*(a->vetor+i)!= -12)      
    {
        if(*a->vetor+i == n)        
        {
            j=i+1;
            *(a->vetor+i) = *(a->vetor+j);     
            if (*a->vetor+i!=-12)               
                *(a->vetor+j)= n;               
        }
        i++;
    }
}
void Imprimir(Ninteiros *a)
{
    int i;

    for(i=0;*(a->vetor+i)!=-12;i++)
    {
        printf("\nV[%d]: %d",i+1,*(a->vetor+i));
    }
}

