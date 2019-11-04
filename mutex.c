/*
 Johannes Schneemann
 November 5, 2019
 
 *** C program with a mutual exclusion algorithm ***
 
 Simulates the concurrent execution of two threads using a single
 program:
        Thread A: prints five subsequent lines of letter A on the printer and
        keeps looping (about 10 times).
        Thread B: prints five subsequent lines of letter B on the printer and
        keeps looping (about 10 times).
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREADS 2
#define LINES 5
#define MAX 10


enum{
    state1, state2
} volatile status = state1;

void *ConsumerAndProducer(void* order);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int main() {
    
    pthread_t* tid = malloc(THREADS*sizeof(pthread_t));

    printf("This C program uses a mutual exclusion algorithm \n");
    printf("to print 10 blocks of 'A' or 'B' on the screen. \n\n");
  
    for (long i = 0; i < THREADS; ++i) {
        pthread_create(&tid[i], NULL, ConsumerAndProducer, (void *)i);
    }
    
    for (long i = THREADS - 1; i > 0; --i) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    free(tid);
    return 0;
}

void* ConsumerAndProducer(void* order) {
    // dereferencing protection
    register int i,j;
    long my_order = (long) order;

    for (i = 0; i < MAX; ++i) {
        switch (my_order) {
            case 0:
                pthread_mutex_lock(&mutex);
                while (status != state1) {
                    pthread_cond_wait(&cond, &mutex);
                }
                pthread_mutex_unlock(&mutex);
                break;
            case 1:
                pthread_mutex_lock(&mutex);
                while (status != state2) {
                    pthread_cond_wait(&cond, &mutex);
                }
                pthread_mutex_unlock(&mutex);
                break;
        }

        // critical section
        for (j = 0; j < LINES; ++j) {
            switch (my_order) {
                case 0:
                    fprintf(stdout, "%d: AAAAAAAAA\n", i+1);
                    break;
                case 1:
                    fprintf(stdout, "%d: BBBBBBBBB\n", i+1);
                    break;
            }
        }
        // Depending on rank & state, set the state to the vice-versa
        // and unblock the other thread
        switch (my_order) {
            case 0:
                pthread_mutex_lock(&mutex);
                status = state2;
                pthread_cond_signal(&cond);
                pthread_mutex_unlock(&mutex);
               break;
            case 1:
                pthread_mutex_lock(&mutex);
                status = state1;
                pthread_cond_signal(&cond);
                pthread_mutex_unlock(&mutex);
                break;
        }
        fprintf(stdout, "\n");
    }
    return NULL;
}
