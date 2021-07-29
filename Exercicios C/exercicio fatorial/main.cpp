#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
using namespace std;

int main(int argc, char** argv) {
	int x = 0, y = 1;
	printf("Informe numero fatorial: ");
	scanf("%i", &x);
		while(x>=1)
		{
			y= y*x;
			x--;
		}
		printf("%i\n",y);
	return 0;
}
