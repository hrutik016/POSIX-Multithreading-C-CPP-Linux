#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>

int arr[] = {1,2,3,4,5};

pthread_mutex_t arr_mutex;

void print_array(){
    
    int i = 0;
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    for(; i < arr_size; i++){
        printf("%d", arr[i]);
    }
    printf("%d\n", arr[i]);
}

static void * thread_fn_callback_sum(void *arg){
    int i;
    int sum;

    int arr_size = sizeof(arr) / sizeof(arr[0]);

    do{
        sum = 0;
        i = 0;

        pthread_mutex_lock(&arr_mutex);
        while(i < arr_size){
            sum += arr[i];
            i++;
        }
        printf("sum = %d\n", sum);
        print_array();
        assert(sum == 15);
        pthread_mutex_unlock(&arr_mutex);
    }while(1);
}

static void *thread_fn_callback_swap(void * arg){
    int temp;
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    do{
        pthread_mutex_lock(&arr_mutex);
        temp = arr[0];
        arr[0] = arr[arr_size - 1];
        arr[arr_size - 1] = temp;
        printf("swap : \n");
        print_array();
        pthread_mutex_unlock(&arr_mutex);
    }while(1);
}

void sum_thread_create(){
    /* opaque object, dont bother about its internal
	* members */
	
    pthread_t pthread1;

	int rc = pthread_create(&pthread1, 
				   NULL, 
				   thread_fn_callback_sum,
				   NULL);
	if(rc != 0) {

		printf("Error occurred, thread could not be created, errno = %d\n", rc);
		exit(0);
	}
}

void swap_thread_create() {
	/* opaque object, dont bother about its internal
	 * members */
	
    pthread_t pthread2;

	int rc = pthread_create(&pthread2, 
				   NULL, 
				   thread_fn_callback_swap,
				   NULL);
	if(rc != 0) {

		printf("Error occurred, thread could not be created, errno = %d\n", rc);
		exit(0);
	}
}

int main(int argc, char **argv){

    pthread_mutex_init(&arr_mutex, 0);

	sum_thread_create();
	swap_thread_create();
    
	pthread_exit(0);
	return 0;
}