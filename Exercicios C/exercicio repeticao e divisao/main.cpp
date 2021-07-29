#include <iostream>
#include <unistd.h>


int main(int argc, char** argv) {
	int i;
	int numero=0;
	
	for(i=1000; i<1999; i++){
		if(i%11==5){
			sleep(1);
			printf("%i\n", i);}}
	return 0;
}
