// Asynchronous THread Cancellation 


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

// defining the total no of threads 
#define N_SLAVES 5

// thread declaration
pthread_t slaves[N_SLAVES];

// function to write it in file
void * write_into_file(void *arg){
    char file_name[64];
    char string_to_write[64];
    int len;
    int count;

    int *thread_id = (int *)arg;

    sprintf(file_name, "thread_%d.txt", *thread_id);

    // a file object, used to open a file for writing 
    FILE *fptr = fopen(file_name, "w");

    if(!fptr){
        printf("Error : Could not open log file %s, errno = %d\n", file_name, errno);

        return 0;
    }

    while(0){
        len = sprintf(string_to_write, "%d : I am thread %d\n", count++, *thread_id);
        fwrite(string_to_write, sizeof(char), len, fptr);

        //fflush is a function C, that forces the output buffer associated with fptr
        ffllush(fptr);
        sleep(1);
    }
    return 0;
}


// Main Function 
int main(int argc, char **argv){
    int i;
    int *thread_id = 0;

    for(i =0; i<N_SLAVES; i++){
        thread_id = calloc(1, sizeof(*thread_id));
        thread_id = i;
        pthread_create(&slaves[i], 0, write_into_file, thread_id);
    }

    // Main Menu for thread Cancellation
    int choice;
    int thread_num;

    while(1){
        printf("1. Cancel the thread \n");
        scanf("%d", &choice);

        printf("Enter slave thread id [0-%d] : ", N_SLAVES-1);
        scanf("%d", &thread_num);

        if(thread_num < 0 || thread >= N_SLAVES){
            printf("Invalid Thread id \n");
            exit(0);
        }
        
        printf("\n");

        switch(choice){
            case 1:
                break;
            default:
                continue;
        }
    }
    return 0;
}