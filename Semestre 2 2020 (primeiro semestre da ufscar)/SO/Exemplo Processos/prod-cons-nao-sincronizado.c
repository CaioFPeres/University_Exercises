#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_ITENS 10
int buffer[N_ITENS];

int inicio = 0, final = 0;

void* produtor(void *v) {
  int i;

  for (i = 0; i < N_ITENS; i++) {
    final = (final + 1) % N_ITENS;
    buffer[final] = i;
    printf("Produtor, item = %d, posição = %d.\n", i, final);     
    sleep(random() % 3);   /* Permite que a outra thread execute */
  }
  return NULL;
}

void* consumidor(void *v) {
  int i, aux;

  for (i = 0; i < 2 * N_ITENS; i++) {
    inicio = (inicio + 1) % N_ITENS;
    aux = buffer[inicio]; /* Item é consumido */
    printf("Consumidor, item = %d, posição = %d.\n", aux, inicio);
    sleep(random() % 3);   /* Permite que a outra thread execute */
  }
  return NULL;
}

int main() {
  int i;
  
  pthread_t thr_produtor, thr_consumidor;

  /* Limpa o buffer */
  for (i = 0; i < N_ITENS; i++)
    buffer[i] = -1;
  
  pthread_create(&thr_produtor, NULL, produtor, NULL);
  pthread_create(&thr_consumidor, NULL, consumidor, NULL);

  pthread_join(thr_produtor, NULL); 
  pthread_join(thr_consumidor, NULL);

  return 0;
}
