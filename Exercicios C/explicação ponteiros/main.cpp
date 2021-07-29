#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int j=5;
	int *k;
	k= &j;
	int **p;
	p= &k;
	printf("%i %i %i\n", p, &p, *p);
	printf("%i %i %i", k, &k, *k);
	
	return 0;
}
