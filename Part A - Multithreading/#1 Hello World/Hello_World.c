#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// thread callback function
static void * thread_fn_callback(void *arg){

    // fetching the passed argument
    char *input = (char*) arg;

    // infinite loop to print the input string
    while(1){
        printf("input string = %s\n", input);
        sleep(1);
    }
}

// function to create a new thread
void thread1_create(){

    // thread identifier
    pthread_t pthread1;

    // input string for thread
    static char *thread_input1 = "I am thread No: 1";

    // fork point 
    int rc = pthread_create(&pthread1, NULL, thread_fn_callback, (void *)thread_input1);

    // to check if the thread creation was successful
    if(rc != 0){
        printf("Error occured, thread could not be created, errno = %d\n", rc);
        exit(0); 
    }
}   

int main (int argc, char **argv){
    // creating the first thread
    thread1_create();

    // indicating that, the main function is paused
    printf("main functin paused \n ");

    // pause the main thread indefinitely
    pause();

    return 0;
}