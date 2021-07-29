#include <stdlib.h>
#include <stdio.h>

main(){
    int n;
    int i;
	char x, copia;

    FILE *arq_entrada;
    FILE *arq_saida;

    arq_entrada= fopen("decodificar.txt", "r");
    arq_saida= fopen("saida.txt", "w");

    if (arq_entrada == NULL)
  {
    printf("Um erro ocorreu ao tentar abrir o arquivo 'decodificar.txt'.\n");
  }
    if (arq_saida == NULL)
  {
    printf("Um erro ocorreu ao tentar abrir o arquivo 'saida.txt'.\n");
  }

else{
    fscanf(arq_entrada,"%d", &n);

    while(fscanf(arq_entrada,"%c", &x,) != EOF)
    {
    x= fgetc(arq_entrada);
      if(x == 'A')
	{
		copia= '#';
		fputc( copia, arq_saida);
	}
      if(x == 'E')
    {
        copia= '@';
       fputc( copia, arq_saida);
    }
      if(x == 'I')
    {
        copia= '$';
      fputc( copia, arq_saida);
    }
      if(x == 'O')
    {
        copia= '&';
      fputc( copia, arq_saida);
    }
      if(x == 'U')
    {
        copia= '*';
      fputc( copia, arq_saida);
    }
}
}
}

fclose(arq_entrada);
fclose(arq_saida);
