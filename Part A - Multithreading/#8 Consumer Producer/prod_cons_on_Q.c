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

    printf("Thread %s waiting tolock the Queue \n", th_name);
    pthread_mutex_lock(&Q -> q_mutex);
    printf("Thread %s wakes up, checking the Queue status again \n", th_name);

    
	/* Code Producer Logic here */
	return NULL;
}

static void *cons_fn(void *arg) {

	char *th_name = (char *)arg;
	

	/* Code Consumer Logic here */
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