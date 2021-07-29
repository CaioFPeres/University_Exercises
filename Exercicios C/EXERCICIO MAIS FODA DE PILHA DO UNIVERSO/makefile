
all: Atividade01

tests: Atividade01 
	./Atividade01 < input > output.tmp

Atividade01: main.o pilha.o
	gcc -o Atividade01 main.o pilha.o

main.o: main.c pilha.h
	gcc -o main.o main.c -c

pilha.o: pilha.c pilha.h
	gcc -o pilha.o pilha.c -c

clean:
	rm -f *.o Atividade* *.tmp