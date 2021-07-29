#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS     5

int ids[NUM_THREADS];

void *hello(void *threadid) {
  //sleep(random() % 2);
  printf("Hello World! It's me, thread %d!\n", *((int *) threadid));
  pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
   pthread_t threads[NUM_THREADS];
   int t, rc;
   for(t = 0; t < NUM_THREADS; t++) {
     ids[t] = t;
     printf("In main: creating thread %d\n", t);
     rc = pthread_create(&threads[t], NULL, hello, (void *) &ids[t]);
     if (rc) {
       printf("Erro código %d\n", rc);
       return -1;
     }
   }
   pthread_exit(NULL);
   //exit(0);
}
