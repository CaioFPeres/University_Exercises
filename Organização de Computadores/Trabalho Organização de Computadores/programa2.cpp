#include <iostream>
#include <stdio.h>
#include <time.h> 

struct pix {
unsigned int r, g, b;
};

#define TAM 10

struct pix color [TAM][TAM];


int main(int argc, char** argv) {
	
	int i,j;
	clock_t t; 
    t = clock(); 
    
	for(i=0;i<TAM;i++){
		for(j=0;j<TAM;j++){
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
    printf(" took %f seconds to execute \n", time_taken);
	
	return 0;
}
