#include <stdio.h>
#include <stdlib.h>

int main(){
	int *x,*p,*i,c,e,a=0,b=0,d=0,m=0;
	printf("Digite o tamanho do vetor: \n");
	scanf("%i",&e);
	x = (int*)malloc(e*sizeof(int));
	for(c=0;c<e;c++){
		printf("Digite um valor para a %i posicao: ",c+1);
		scanf("%i",&x[c]);
	}
	for(c=0;c<e;c++){
		if(x[c]%2==0){
			a++;
		}else{
			b++;
		}
	}
		p=(int*)malloc(a*sizeof(int));
		i=(int*)malloc(b*sizeof(int));
	for(c=0;c<e;c++){
		if(x[c]%2==0){
				p[d]=x[c];
				d++;
		}else{
				i[m]=x[c];
				m++;
		}
	}
	printf("Vetor dos pares: ");
	for(d=0;d<a;d++){
		printf("%d ",p[d]);
	}
	printf("\n");
	printf("Vetor dos impares: ");
	for(m=0;m<b;m++){
		printf("%d ",i[m]);
	}
	free(x);
	free(p);
	free(i);
	return 0;
}
