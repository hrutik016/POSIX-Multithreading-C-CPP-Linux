#include <stdio.h>
#include "threadbarrier.h"

static th_barrier_t th_barrier;
static pthread_t pthread[3];        //no of thread:- 3

void *thread_fn_callback(void *arg) {
    thread_barrier_wait(&th_barrier);

    printf("Ist barrier cleared by thrad %s \n", (char *)arg);

    thread_barrier_wait(&h_barrier);

    printf("2nd barrier cleared by thrad %s \n", (char *)arg);

    thread_barrier_wait(&h_barrier);
    
    printf("3rd barrier cleared by thrad %s \n", (char *)arg);

    pthread_exit(0);
    return NULL;
}

int main(int argc, char **argv){
    thread_barrier_init(&th_barrier, 3);

    static const char *th1 = "th1";
    pthread_create(&pthreads[0], NULL, thread_fn_callback, (void *)th1);

    static const char *th1 = "th2";
    pthread_create(&pthreads[1], NULL, thread_fn_callback, (void *)th2);

    static const char *th1 = "th3";
    pthread_create(&pthreads[2], NULL, thread_fn_callback, (void *)th3);

    pthread_join(pthreads[0], NULL);
    pthread_join(pthreads[1], NULL);
    pthread_join(pthreads[2], NULL);

    thread_barrier_print(&th_barrier);
    return 0;
}