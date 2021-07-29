CC = gcc
#CFLAGS = -g
CFLAGS = -Wall -g -pthread
#LDFLAGS = -lm

PROGRAMS = shell pthread \
           prod-cons-nao-sincronizado \
	   prod-cons-nao-consistente \
           disputa peterson semaforo \
           prod-cons-semaforo prod-cons-bloqueio-cond \
           deadlock

all: $(PROGRAMS)

clean:
	rm -f *.o *~ $(PROGRAMS)
