#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct usuario
{
   int numeroamigos,pop;
   char nome[16],amigos[5][16];

}User;

int main()
{
    int n,i,j,k=0;
    User *usuarios;
    printf("\nDigite o numero de usuarios: ");
    scanf("%d",&n);
    usuarios=(User *)malloc(n*sizeof(User));
    for(i=0; i<n; i++) 
        {
         (usuarios+i)->pop = 0;
        }
    for(i=0;i<n;i++)
    {
        printf("\nDigite o nome do usuario %d: ",i+1);
        setbuf(stdin,NULL);
        fgets((usuarios+i)->nome,16,stdin);
    }
    for(i=0;i<n;i++)
       {
        
	do{
        	printf("\nDigite qtd de amigos (max. 5) Usuario(%d): ",i+1);
        	scanf("%d",&(usuarios+i)->numeroamigos);
        
	}while((usuarios+i)->numeroamigos<0 ||(usuarios+i)->numeroamigos>5);
            
	for(j=0;j<(usuarios+i)->numeroamigos;j++)
                {
                    printf("\nDigite o nome do seu amigo %d: ",j+1);
                    setbuf(stdin,NULL);
                    fgets(((usuarios+i)->amigos[j]),16,stdin);
                    for(k=0;k<n;k++)
                    {
                        if(strcmp((usuarios+j)->amigos[j],(usuarios+k)->nome)==0)
                            (usuarios+i)->pop+=1;
                    }
                }
       }


    for(i=0;i<n;i++)
    {
            printf("\nPopularidade: %s(%d) ",(usuarios+i)->nome,(usuarios+i)->pop);
    }


return 0;
}
