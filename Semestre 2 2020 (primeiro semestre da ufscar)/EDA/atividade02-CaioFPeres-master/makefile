
all: Atividade02

tests: Atividade02 
	./Atividade02 < input > output.tmp

Atividade02: main.o lista.o
	gcc -o Atividade02 main.o lista.o

main.o: main.c lista.h
	gcc -o main.o main.c -c

pilha.o: lista.c lista.h
	gcc -o lista.o lista.c -c

clean:
	rm -f *.o Atividade02* *.tmp