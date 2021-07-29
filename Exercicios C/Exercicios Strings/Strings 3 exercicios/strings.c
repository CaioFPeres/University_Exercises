#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

char nome[1000]={0};
int quantidade;
char n1[1000], n2[1000];
char nome1[1000], nome2[1000], nomeconca[1000]={'0'};
int j=0;


int comparar(){
	int i;
	for (i = 0; i < 1000; i++)
	{
		if (n1[i] == n2[i])
		{
			printf("Os nomes sao iguais.\n");
			return 0;
		}
		else if (n1[i] != n2[i])
		{
			printf("Os nomes nao sao iguais.\n");
			return 0;
		}
}}

int comprimento(){
    while(nome[quantidade] != '\0'){
    	quantidade++;
}
return 0;}

int concatenar(){
        int i = 0;
        int i2 = 0;

        while(nome1[i] != '\0') {
             nomeconca[i] = nome1[i];
             i++;
            }
            
        while(nome2[i2] != '\0') {
              nomeconca[i] = nome2[i2];
              i2++;
              i++;
            }

    return 0;
}

int main()
{
    printf("Digite seu nome: ");
    gets(nome);
    comprimento();
    printf("Comprimento do nome: %i\n", quantidade);
    
    printf("Insira um nome: ");
	gets(n1);
	printf("Insira outro nome: ");
	gets(n2);
	comparar();
	
	printf("Primeiro nome: ");
	scanf("%s", nome1);
	printf("Segundo nome: ");
    scanf("%s", nome2);
	concatenar();
    printf("Nome Concatenado: %s", nomeconca);
    return 0;
}
