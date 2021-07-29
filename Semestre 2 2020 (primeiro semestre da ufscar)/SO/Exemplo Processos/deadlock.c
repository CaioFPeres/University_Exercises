#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int compartilhada1 = 1;
int compartilhada2 = 2;
pthread_mutex_t bloqueio1, bloqueio2;

void* thread1(void *v) {
  while (1) {
    pthread_mutex_lock(&bloqueio1);
    pthread_mutex_lock(&bloqueio2);
    compartilhada1 += compartilhada2;
    printf("t1: c1 = %d, c2 = %d\n", compartilhada1, compartilhada2);
    pthread_mutex_unlock(&bloqueio2);
    pthread_mutex_unlock(&bloqueio1);
  }
}

void* thread2(void *v) {
  while (1) {
    pthread_mutex_lock(&bloqueio2);
    pthread_mutex_lock(&bloqueio1);
    compartilhada2 -= compartilhada1;
    printf("t2: c1 = %d, c2 = %d\n", compartilhada1, compartilhada2);
    pthread_mutex_unlock(&bloqueio1);
    pthread_mutex_unlock(&bloqueio2);
  }
}

int main() {
  pthread_t thr1, thr2;

  pthread_mutex_init(&bloqueio1, NULL);
  pthread_mutex_init(&bloqueio2, NULL);
  
  pthread_create(&thr1, NULL, thread1, NULL);
  pthread_create(&thr2, NULL, thread2, NULL);

  pthread_join(thr1, NULL); 
  pthread_join(thr2, NULL);

  return 0;
}
