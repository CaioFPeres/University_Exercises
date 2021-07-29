#include <iostream>
#define T 10

void inserir(float v[]){
	
	float valor;
	int i;
	
	for(i=0; i<T;i++){
		scanf("%f", &valor);
		v[i] = valor;
	}
}


void imprimir(float v[], int att){
	int i;
	
	printf("\nVetor: ");
    for(i=0;i<att;++i)
    printf("%2.f  ",v[i]);
    
}

void bubblesort(float v[]){
	
	 int i=0,j=0,aux=0;

    for(j=0;j<T-1;++j){
    for(i=0;i<T-j-1;++i){
    	
        if(v[i]>v[i+1])
        {
            aux=v[i];
            v[i]=v[i+1];
            v[i+1]=aux;
        }
    }
}

}


void remocao(float v[], float elemento){
	
	int meio = T/2;
	int i, j;
	
	
	
	if(v[meio] > elemento){
		
		for(i=meio;i>=0;i--){
			
			if(v[i]==elemento){
    			for (j=i; j<T;j++){
         			v[j] = v[j+1];}
         		return;
			}
			
		}
	}
	
	else{
		
		for(i=meio;i<T;i++){
			
			if(v[i]==elemento){
    			for (j=i; j<T;j++){
         			v[j] = v[j+1];}
         	return;
         	
			}
		}
	}
	
	
	printf("Elemento nao encontrado!");

}

void mediana(float v[]){
	
	int mediana;
	mediana = v[T/2-1];
	printf("Mediana: %i", mediana);
	
}

void media(float v[], int att){
	float soma=0;
	float media=0;
	int i;
	
    for(i=0;i<att;++i){
    	soma = soma + v[i];
	}
	
	media = soma/att;
	printf("Media: %.2f", media);
	
}

int main(int argc, char** argv) {
	
	float v[T];
	float elemento;
	int o;
	int att=T;
	
	while(1==1){
	printf("\nDigite:\n");
	printf("1 - para inserir\n2 - para ordenar\n3 - para remover\n4 - para imprimir\n5 - para calcular moda\n6 - para calcular media\n7 - para calcular mediana\n8 - para sair\n");
	scanf("%i", &o);
	switch(o){
		case 1:
		printf("Digite valores para o vetor: ");
		inserir(v);
		att=T;
	break;
		case 2:
		bubblesort(v);
	break;
		case 3:
		printf("\nEscolha o elemento a ser removido: ");
		scanf("%f", &elemento);
		remocao(v,elemento);
		att= att-1;
	break;
		case 4:
		imprimir(v, att);
	break;
		case 5:
	//	moda();
	break;
		case 6:
	  media(v, att);
	break;
		case 7:
	  mediana(v);
	break;
		case 8:
		return 0;
	break;
	}
	}
	
}
