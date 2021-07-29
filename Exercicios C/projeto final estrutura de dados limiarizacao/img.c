   /*
    *Autores: Gustavo M. Correa RA:1923870
    *         Caio F. Peres     RA: 2000784
    *   Descrição: Funções:
    *               main()
    *                   cria uma cabeça pra lista, que armazenará o n° max de linhas e colunas da imagem, o primeiro e ultimo 
    *                   elementos da lista (o ultimo para não precisar percorrer toda a lista para adicionar um elemento ao fim).
    *                   Pede o nome do arquivo (assume-se extensão .pgm) e faz a chamada dos metodos para processar a imagem
    *                   e para criação da saida.
    *               leImg(char nome[], cabeca *c)
    *                   faz a leitura do tipo da imagem, n° de linhas e colunas, tom maximo de cinza, e armazena as posições dos
    *                   digitos abaixo da limiar para armazenar na lista alocada dinamicamente.
    *               alocaPxl(int linha, int coluna)
    *                   faz a alocação dinamica de img, nas linhas e colunas passadas no parametro, retorna o ponteiro dessa 
    *                   struct.
    *               geraImg(cabeca *c)
    *                   percorre as colunas e linhas, valores que não constarem na matriz esparsa serão preenchidos na saida 
    *                   com 1(branco) e os que estiverem, serão impressos como 0 na saida, passando para o proximo valor na 
    *                   matriz, e desalocando os ja utilizados.
    *               histograma(char nome[])
    *                   retorna o inteiro que deve ser o limiar. Conta o n° de pixels dentro da tonalidade de cinza [0, 255]
    *                   e procura os picos e vales, e encontra a maior diferença entre eles.
    *               
    */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *arq;

typedef struct imagem img;

struct imagem
{
    int linha;
    int coluna;
    img *prox;
};

typedef struct cabeca
{
    int linha;
    int coluna;
    img *prox;
    img *ult;
}cabeca;

void leImg(char nome[], cabeca *c);
img *alocaPxl(int linha, int coluna);
void geraImg(cabeca *c);
int histograma(char nome[]);

int main()
{
    cabeca *c = (cabeca *) malloc(sizeof(cabeca));
    c -> linha = 0;
    c -> coluna = 0;
    c -> prox = NULL;
    c -> ult = NULL;
    
    char nome[20], ext[] = ".pgm", op;
    do
    {
        printf("Digite o nome do arquivo sem a extensão: ");
        scanf("%[^\n]", nome);
        fflush(stdin);
        strcat(nome, ext);
        leImg(nome, c);
        geraImg(c);
        printf("Deseja gerar a saida de uma nova imagem?\n\ts - Sim.\n\tn - Não.\n");
        scanf("%c", &op);
        fflush(stdin);
    }while(op != 'n');
}

void geraImg(cabeca *c)
{
    int n = 0, m = 0;
    img *aux = c -> prox, *s;
    arq = fopen("saida.pgm", "w");
    fprintf(arq, "P2\n%i %i\n1\n", c -> linha, c -> coluna);
    while(n < c -> linha)
    {
        for(m = 0; m < c->coluna; m++)
        {
            if(aux != NULL)
            {
                if(n == aux -> linha && m == aux -> coluna)
                {
                    s = aux;
                    aux = aux -> prox;
                    c -> prox = aux;
                    free(s);
                    fprintf(arq, "0\n");
                }else
                    fprintf(arq, "1\n");
            }else
            	fprintf(arq, "1\n");
        }
        n++;
    }
    fclose(arq);
}

int histograma(char nome[])
{
    int i, b, n, max = 0, pico, vale;
    char tipo[10];
    
    arq = fopen(nome, "r");
    
    if(arq == NULL)
    {
        printf("Arquivo não encontrado\n");
        return 0;
    }
    fgets(tipo, 10, arq); //captura o tipo de arquiv
    fgets(tipo, 10, arq);//num de linhas e colunas
    fscanf(arq, "%i\n", &b);//num max de cinza
    
    int v[b+1];
    for(i = 0; i < b+1; i++)
        v[i] = 0;
    
    while(!feof(arq))
    {
        fscanf(arq, "%i\n", &i);
        v[i]++;
    }
    
    for(i = 1; i < b-5; i++)
    {
       pico = v[i] - v[i+2] + v[i+1];
        if(i> 60)
            if(pico>max)
            {
                max = v[i];
                n = i;
            }
        /*pico = v[i] - v[i+1]; //metodo 2 para limiarização
        vale = v[i+2] - v[i+1];
        if(vale > 0 && pico - vale > max)
        {
            max = pico - vale;
            n = i;
        }*/
    }
    fclose(arq);
    return n;
}

void leImg(char nome[], cabeca *c)
{
    char tipo[3];
    int a, m = 0, n = 0, limiar;
    limiar = histograma(nome);
    printf("Limiar: %i\n", limiar);
    arq = fopen(nome, "r");
    if(arq == NULL)
    {
        printf("%s não encontrado.\n", nome);
        return;
    }
    
    fgets(tipo, 3, arq); //captura o tipo de arquivo
    if(strcmp(tipo, "P2"))
    {
        printf("Tipo de arquivo ainda não suportado.\n");
        return;
    }
    
    getc(arq);//captura o \n
    fscanf(arq, "%i %i\n", &(c -> linha), &(c -> coluna));//n de linhas e colunas
    fscanf(arq, "%i\n", &a);//captura intensidade max de cinza
    if(limiar == 0)
        limiar = a/2;
    while(n < c -> linha )
    {
        fscanf(arq, "%i\n", &a);
        if(a < limiar)
        {
            if(c -> prox == NULL)
            {
                c -> prox = alocaPxl(n, m);
                c -> ult = c -> prox;
            }else
            {
                c-> ult -> prox = alocaPxl(n, m);
                c -> ult = c -> ult -> prox;
            }
        }
        m++;
        if(m == c -> coluna)
        {
            m = 0;
            n++;
        }
    }
    fclose(arq);
}

img *alocaPxl(int linha, int coluna)
{
    img *n = (img *) malloc(sizeof(img));
    n -> linha = linha;
    n -> coluna = coluna;
    n -> prox = NULL;
    return n;
}


