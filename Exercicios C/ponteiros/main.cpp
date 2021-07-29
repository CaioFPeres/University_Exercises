#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int x = 10;
	int *p;
	p=&x;
	printf("x %i\n", x);
	printf("&x = %i\n", &x);
	printf("p = %i\n", p);
	
	system("pause");
	return 0;
}
