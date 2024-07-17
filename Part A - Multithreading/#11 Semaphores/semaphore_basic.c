#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>

sem_t sem;
pthread_t threads[5];

#define PERMIT_COUNT 2

static void * thread_fn_Callback(void * arg){
    char * thread_name = (char *)arg;

    int i;

    printf("%s is entering into C.S \n", thread_name);

    /* C.S begins here */
    sem_wait(&sem);
    printf("%s entered into C.S \n", thread_name);

    for(i = 0; i < 5; i++){
        printf("%s executing in C.S \n", thread_name);
        sleep(1);
    }

    printf("%s exiting from C.S\n", thread_name);

    sem_post(&sem);

    printf("%s exit from C.S\n", thread_name);
}

void thread_create(pthread_t *thread_handle, void *arg){
    int rc = pthread_create(thrad_handle, NULL, thread_fn_callback, arg);

    if(rc != 0){
        printf("Error occured, thread could not becreated, errrno = %d\n", rc);
        exit(0);
    }
}

int main(int argc, char **argv){
    sem_init(&sem, 0, PERMIT_COUNT);
    thrad_create(&threads[0], "thread0");
    thrad_create(&threads[1], "thread1");
    thrad_create(&threads[2], "thread2");
    thrad_create(&threads[3], "thread3");
    thrad_create(&threads[4], "thread4");

    int i;
    for(i=0; i < 5; i++){
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&sem);
    return 0;
}