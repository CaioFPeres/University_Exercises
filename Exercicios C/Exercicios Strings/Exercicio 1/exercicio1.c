#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome[1000]={0};
    int i=0;
    int quantidade;
        printf("Digite seu nome: ");
    gets(nome);
    
    while(nome[quantidade] != '\0'){
    	quantidade++;}
    printf("Comprimento do nome: %i", quantidade);
    
return 0;
}