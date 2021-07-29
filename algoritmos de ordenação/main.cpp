#include <stdio.h>

void bubblesort(){
	
	 int vetor[5],i,j,temp;
    
    for(i=0;i<5;++i)
    {
        printf("\n\n%d. Elemento: ",i+1);
        scanf("%d",&vetor[i]);
    }

    for(j=0;j<5-1;++j)
    for(i=0;i<5-j-1;++i)
    {
        if(vetor[i]>vetor[i+1])
        {
            temp=vetor[i];
            vetor[i]=vetor[i+1];
            vetor[i+1]=temp;
        }
    }
    printf("\nVetor: ");
    for(i=0;i<5;++i)
         printf("%d  ",vetor[i]);
    return;
}

void insertsort(){
	int vetor[5],i,j,temp;
	
    for(i=0;i<5;++i)
    {
        printf("\n\n%d. Elemento: ",i+1);
        scanf("%d",&vetor[i]);
    }
    
	for(i=1;i<5;i++)
	{
		temp = vetor[i];
		j=i-1;
		while(temp<vetor[j] && j>=0)
		{
			vetor[j+1] = vetor[j];
			--j;
		}
		vetor[j+1]=temp;
	}
	printf("\nVetor: ");
	for(i=0; i<5; i++)
		printf("%d  ",vetor[i]);
    return;
}

void quick_sort(tipo_aresta vetor[], int left, int right) {
    int i, j, x, k;
    tipo_aresta y[right];
     
    i = left;
    j = right;
    k = (left + right) / 2;
    x = vetor[k].dis;

    while(i <= j) {
        while(vetor[i].dis < x && i < right) {
            i++;
        }
        while(vetor[j].dis > x && j > left) {
            j--;
        }
        if(i <= j) {
            y[i] = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = y[i];
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick_sort(vetor, left, j);
    }
    if(i < right) {
        quick_sort(vetor, i, right);
    }
}

void selectionsort(){
	int vetor[5],i,j,temp;
	
    for(i=0;i<5;++i)
      {
       printf("\n\n%d. Elemento: ",i+1);
       scanf("%d",&vetor[i]);
    }
    for(j=0;j<5;++j)
    for(i=j+1;i<5;++i)
     {
         if(vetor[j]>vetor[i])  
          {
             temp=vetor[j];
             vetor[j]=vetor[i]; 
             vetor[i]=temp;
         }
    }
    printf("\nVetor: ");
    for(i=0;i<5;++i)
        printf("%d  ",vetor[i]);
    return;
}



int main()
{
    bubblesort();
    insertsort();
    selectionsort();
//  quick_sort(vetArestas, 0, arestas);
    
}

