
all: Atividade03

tests: Atividade03
	./Atividade03

Atividade03: main.o fila_prioridade.o
	gcc -o Atividade03 main.o fila_prioridade.o

main.o: main.c fila_prioridade.h
	gcc -o main.o main.c -c

pilha.o: fila_prioridade.c fila_prioridade.h
	gcc -o fila_prioridade.o fila_prioridade.c -c

clean:
	rm -f *.o Atividade0* *.tmp