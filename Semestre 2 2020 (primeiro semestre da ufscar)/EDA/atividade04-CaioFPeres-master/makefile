all: Atividade04

Atividade04: main.o queue.o
	gcc -o Atividade04 main.o queue.o

main.o: main.c queue.h
	gcc -o main.o -c main.c

queue.o: queue.c queue.h
	gcc -o queue.o -c queue.c

clean:
	rm *.o Atividade*