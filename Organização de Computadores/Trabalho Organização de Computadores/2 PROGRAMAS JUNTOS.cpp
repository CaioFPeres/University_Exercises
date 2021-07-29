#include <stdio.h>
#include <time.h>
#define TAM 10000

struct pix {
unsigned int r, g, b;
};

struct pix color [TAM][TAM];



double programa1(int tamanho){
		int i,j;
		clock_t t;
    	t = clock();

	for(i=0;i<tamanho;i++){
		for(j=0;j<tamanho;j++){
			color[i][j].r=
			(
				color[i][j].r +
				color[i][j].g +
				color[i][j].b
			)/3;
		}
	}
	
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
	return time_taken;
	
}

double programa2(int tamanho){
		int i,j;
		clock_t t;
    	t = clock();
	
	for(i=0;i<tamanho;i++){
		for(j=0;j<tamanho;j++){
			color[j][i].r=
			(
				color[j][i].r +
				color[j][i].g +
				color[j][i].b
			)/3;
		
		}
	}

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    return time_taken;
	
}



int main() {
	
	
	int tamanho = 1000;
	FILE *arq = fopen("cache.csv", "w");
	fprintf(arq, "TAMANHO;PROGRAMA 1;PROGRAMA 2\n");
	
	while(tamanho<=TAM){
	double tempo1 = programa1(tamanho);
	double tempo2 = programa2(tamanho);
	
	
    fprintf(arq, "%d;%f;%f\n", tamanho, tempo1, tempo2);
	
    tamanho = tamanho + 1000;
}

	return 0;
}
