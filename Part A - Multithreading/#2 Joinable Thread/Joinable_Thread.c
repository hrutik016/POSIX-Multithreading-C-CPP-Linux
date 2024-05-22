#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>        // for POSIX threads
#include <unistd.h>         // for pause() and sleep() functions
#include <errno.h>          // for using global variable errno

/*
Functionality of this program is that, when our main thread creates child threads, then
at the time of creation of child threads, out main thread will supply an integer value 
as an argument to these child threads.

These child threads will simply compute the square of the integer value and 
return the result to the main thread.
*/

// Thread Callback Function
void *thread_fn_callback(void *arg){
    int th_id = *(int *)arg;
    free(arg);

    int rc = 0;

    while(rc != th_id) { 
        printf("Thread %d doing some work \n ", th_id);
        sleep(1);
        rc++;
    }

    int *result = calloc(1, sizeof(int));
    *result = th_id * th_id;

    return (void *)result;
}

// Thread_Create Function
void thread_create(pthread_t *pthread_handle, int th_id){

    pthread_attr_t attr;

    pthread_attr_init(&attr);

    int *_th_id = calloc(1, sizeof(int));
    *_th_id = th_id;

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_create(pthread_handle, &attr, thread_fn_callback, (void *)_th_id);

    pthread_attr_destroy(&attr);

}

pthread_t pthread2;         // thread handle  
pthread_t pthread3;         // thread handle  


/********************************************************************
Main Function
********************************************************************/
int main(int argc, char **argv){

    void *thread_result2;
    void *thread_result3;

    // first we will create one of the child thread.
    thread_create(&pthread2, 2);        //this is a UDF,and not a stnadard POSIX function
    
    //similar to the above one, we have another one
    thread_create(&pthread3, 10);

    printf("main function blocked on pthread join for thread with th_id = 2 \n");
    
    pthread_join(pthread2, &thread_result2);
    
    if(thread_result2){
        printf("Returned result from thread 2 = %d", *(int *)thread_result2);
        free(thread_result2);       // release child thread memory, (here dynamically allocated memory)
        thread_result2 = NULL;
    }


    printf("main function blocked on pthread join for thread with th_id = 3 \n");
    
    pthread_join(pthread3, &thread_result3);
    
    if(thread_result3){
        printf("Returned result from thread 2 = %d", *(int *)thread_result3);
        free(thread_result3);       // release child thread memory, (here dynamically allocated memory)
        thread_result3  = NULL;
    }

    return 0;
}