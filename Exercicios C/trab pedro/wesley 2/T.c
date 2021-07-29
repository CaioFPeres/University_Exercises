#include<stdio.h>
#include<stdlib.h>

void main()
{	
	char letra,lixo;
	// A variavele lixo foi criada para salvar o que não me interessa no arquivo, como espaçoes e \n (pula-linha).
	// Se fosse um valor inteiro a função fscanf iria direto para o proximo valor, ignorando tudo que exista entre um e outro

	FILE *arq_entrada = fopen("arquivo.txt","r");// é necessário ser arquivos e ponteiros diferentes
	FILE *arq_saida = fopen("novo.txt","w");
	
	if(arq_entrada == NULL) printf("Não foi possivel ler o arquivo\n");
	else if(arq_saida == NULL) printf("Não foi possivel escrever no arquivo.\n");
	else
	{	
		while(fscanf(arq_entrada,"%c%c", &letra,&lixo) != EOF) //Ao chegar no final do arquivo, a função fscanf retornará EOF
		{	
			if(letra == 'A')
			{
				fprintf(arq_saida,"#\n");	
			}
			if(letra == 'E')
			{
				fprintf(arq_saida,"@\n");
			}
			if(letra == 'I')
			{
				fprintf(arq_saida,"$\n");
			}
			if(letra == 'O')
			{
				fprintf(arq_saida,"&\n");
			}
			if(letra == 'U')
			{
				fprintf(arq_saida,"*\n");
			}
		}
	fclose(arq_entrada);
	fclose(arq_saida);
	}
}
