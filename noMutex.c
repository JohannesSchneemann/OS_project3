/*
 Johannes Schneemann
 November 5, 2019
 
 *** C program without a mutual exclusion algorithm ***
 
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

void *ConsumerAndProducer(void* order);

int main() {
    long t;
    pthread_t* tid = malloc(THREADS*sizeof(pthread_t));
    
    printf("This C program does not use a mutual exclusion algorithm \n");
    printf("to print 10 blocks of 'A' or 'B' on the screen. \n\n");
    
    // create the threads
    for (t = 0; t < THREADS; ++t) {
        pthread_create(&tid[t], NULL, ConsumerAndProducer, (void *)t);
    }
    
    // join the threads
    for (t = THREADS - 1; t > 0; --t) {
        pthread_join(tid[t], NULL);
    }
    
    // deallocate memory
    free(tid);
    return 0;
}

void *ConsumerAndProducer(void* order) {
    register int i, j;
    long my_order = (long)order;
    for (i = 0; i < MAX; ++i) {
        for (j = 0; j < LINES; ++j) {
            if (my_order == 0) {
                fprintf(stdout,"%d: AAAAAAAAA\n", i+1);
            }
            else {
                fprintf(stdout, "%d: BBBBBBBBB\n", i+1);
            }
        }
        fprintf(stdout, "\n");
    }
    return NULL;
}
