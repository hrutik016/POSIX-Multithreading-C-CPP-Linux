#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include "Queue.h"

static int new_int() {

	static int a = 0;
	a++;
	return a;
}

struct Queue_t *Q;

static const char *prod1 = "TP1";
static const char *prod2 = "TP2";
static const char *cons1 = "TC1";
static const char *cons2 = "TC2";

static void *prod_fn(void *arg) {

	char *th_name = (char *)arg;    // this line casts the void* argument 'arg' to ' char*', allowing to treat it as string. Now 'th_name' contains the thread name (' "TP1", "TP2", "TC1", "TC2" ')

    /* Code Producer Logic here */
    printf("Thread %s waiting tolock the Queue \n", th_name);
    pthread_mutex_lock(&Q -> q_mutex);
    printf("Thread %s wakes up, checking the Queue status again \n", th_name);

    while(is_queue_full(Q)){
        printf("Thread %s blocks itself, Q is already full \n", th_name);
        pthread_cond_wait(&Q->q_cv, &Q->q_mutex);       // since Q is full, we wait for CV->signal and the mutex is freed here
        printf("Thread %s wakes up, checking the Q status again \n", th_name);
    }

    // Start of Critial Section of the Producer. Producermust start pushing elements in the empty Queue only
    assert(is_queue_empty(Q));

	int i;
    while(!is_queue_full(Q)){
        i = new_int();
        printf("Thread %s produces new integer %d\n", th_name, i);
        enqueue(Q, (void *)(intptr_t)i);
        printf("Thread %s pushed integer in Queue %d, Queue size=%d\n", th_name, i, Q->count);
    }

    printf("Thread %s has filled up the Queue, signalling and releasing lock\n", th_name);
    pthread_cond_broadcast(&Q->q_cv);

    // End of Critical Section of the producer
    pthread_mutex_unlock(&Q->q_mutex);
    printf("Thread %s finished, and exit \n", th_name);
	return NULL;
}

static void *cons_fn(void *arg) {

	char *th_name = (char *)arg;

	/* Code Consumer Logic here */
    printf("Thread %s waiting to lock the Queue\n", th_name);
    pthread_mutex_lock(&Q->q_mutex);
    printf("Thread %s locks the Queue\n", th_name);

    while(is_queue_empty(Q)){
        printf("Thread %s blocks itself, Q is already empty \n", th_name);
        thread_cond_wait(&Q->q_cv, &Q->q_mutex);
        printf("Thread %s wakes up, checking the Queue status again\n", th_name);
    }

    // Start of the Critical Section of the Consumer
    assert(is_queue_full(Q));

    int i;
    while(!is_queue_empty(Q)){
        i = (int)deque(Q);
        printf("Thread %s consumes as integer %d, Queue size = %d\n", th_name, i, Q->count);
    }

    printf("Thread %s drains the entire Queue, sending signal to blocking threads \n", th_name);
    pthread_cond_broadcast(&Q->q_cv);

    printf("thread %s releasing the lock \n", th_name);

    //end of the critical section of consumer
    pthread_mutex_unlock(&Q->q_mutex);
    printf("thread %s finished, and exit\n", th_name);
	return NULL;
}

int main(int argc, char **argv) {

	/* initialize the Queue and its Mutex + CV */
	Q = initQ();
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_t prod_th1, prod_th2; /*  Two producer threads */
	pthread_t cons_th1, cons_th2; /*  Two consumer threads */

	pthread_create(&prod_th1, &attr, prod_fn, (void *)prod1);
	
	pthread_create(&prod_th2, &attr, prod_fn, (void *)prod2);
	
	pthread_create(&cons_th1, &attr, cons_fn, (void *)cons1);
	
	pthread_create(&cons_th2, &attr, cons_fn, (void *)cons2);

	pthread_join(prod_th1, 0);
	pthread_join(prod_th2, 0);
	pthread_join(cons_th1, 0);
	pthread_join(cons_th2, 0);

	printf("Program Finished\n");
	pthread_exit(0);
	return 0;
}