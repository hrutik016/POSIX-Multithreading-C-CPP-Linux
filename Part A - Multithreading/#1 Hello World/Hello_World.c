#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void * thread_fn_callback(void *arg){

    // fetching the passed argument
    char *input = (char*) arg;

    while(1){
        printf("input string = %s\n", input);
        sleep(1);
    }
}

void thread1_create(){

    // main thread
    pthread_t pthread1;

    static char *thread_input1 = "I am thread No: 1";

    // fork point 
    int rc = pthread_create(&pthread1, NULL, thread_fn_callback, (void *)thread_input1);

    if(rc != 0){
        printf("Error occured, thread could not be created, errno = %d\n", rc);
        exit(0); 
    }
}   

int main (int argc, char **argv){

    thread1_create();
    printf("main functin paused \n ");
    pause();
    return 0;
}