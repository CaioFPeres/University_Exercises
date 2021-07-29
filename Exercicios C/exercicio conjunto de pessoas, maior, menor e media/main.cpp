#include <iostream>


int main(int argc, char** argv) {
	float alturah;
	float maiorAH;
	float menorAH;
	float alturam;
	float maiorAM;
	float menorAM;
	float media;
	float somatorio=0;
	int o=0;
	int i=0;
	
	for(i=0; i<50; i++){
	printf("Digite 1 para digitar altura dos homens, e 2 para digitar a altura das mulheres: ");
	scanf("%i", &o);
	switch(o){
		case 1:
			printf("Digite a altura dos homens: ");
			scanf("%f", &alturah);
			if(alturah>maiorAH)
				maiorAH= alturah;
			if(alturah<maiorAH)
				menorAH= alturah;
		break;
		case 2:
			printf("Digite a altura das mulheres: ");
			scanf("%f", &alturam);
			if(alturam>maiorAM)
				maiorAM= alturam;
			if(alturam<menorAM){
				menorAM= alturam;}
			somatorio= somatorio + alturam;
		break;}}
		media= somatorio/50;
		if(menorAH<menorAM)
			printf("A menor altura eh dos homens, e eh: %f\n", menorAH);
		else
			printf("A menor altura eh das mulheres, e eh: %f\n", menorAM);
		if(maiorAH>maiorAM)
			printf("A maior altura eh dos homens, e eh: %f\n", maiorAH);
		else
			printf("A maior altura eh das mulheres, e eh: %f\n", maiorAM);
		printf("A media das alturas das mulheres eh: %f\n", media);

	return 0;
}
