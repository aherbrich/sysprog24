#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Task 3.2 c) (SYNCHRONIZING buffer access)
//
// compile with: gcc -o 3_2_c tut05/3.2/c-version/C.c -lpthread
// execute with: ./3_2_c 
//
// PROBLEM:
// The sensor_thread and controller_thread are working on the same buffer.
// The sensor_thread is gathering data into the buffer 
// and the controller_thread is copying the data from the buffer.
// -> only one thread should access the buffer at a time
//

// SOLUTION:

// ignore these definitions
#define GATHERING 0
#define COPYING 1
typedef int state_t;

// critical code
char buffer[1024];
state_t state = GATHERING;
void gather_data_into_buffer() { printf("Gathering data\n"); sleep(3); }
void copy_buffer() { printf("Copying data\n"); sleep(3); printf("Data copied\n"); }

// non-critical code
void calculate_forecast() { /* simulate calculating forecast */ }

// mutexes
pthread_mutex_t access_buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

// cond/signal variables
pthread_cond_t buffer_filled = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_copied = PTHREAD_COND_INITIALIZER;


void sensor_thread(){
    while(1) {
        pthread_mutex_lock(&access_buffer_mutex);

        gather_data_into_buffer();
       
        state = COPYING;                        // now we switch to state COPYING 
        pthread_cond_signal(&buffer_filled);    // signal that other thread can start copying
        
        pthread_mutex_unlock(&access_buffer_mutex);

        // now we loop here until the other thread is done copying
        pthread_mutex_lock(&access_buffer_mutex);
        while(state == COPYING){
            printf("Finished gathering data - waiting for data to be copied\n");
            pthread_cond_wait(&buffer_copied, &access_buffer_mutex);
        }
        pthread_mutex_unlock(&access_buffer_mutex);
    }
}

void controller_thread(){
    while(1) {
        pthread_mutex_lock(&access_buffer_mutex);

        // we loop here until the sensor thread is done gathering
        while(state == GATHERING){
            printf("Waiting for data to be gathered\n");
            pthread_cond_wait(&buffer_filled, &access_buffer_mutex);
        }

        copy_buffer();
        state = GATHERING;                      // now we switch to state GATHERING 
        pthread_cond_signal(&buffer_copied);    // signal that other thread can start gathering again

        pthread_mutex_unlock(&access_buffer_mutex);

        calculate_forecast();                  // this can happen outside of the critical section
    }
}

int main(){
    pthread_t sensor_thread_id;
    pthread_t controller_thread_id;

    pthread_create(&sensor_thread_id, NULL, (void*)sensor_thread, NULL);
    pthread_create(&controller_thread_id, NULL, (void*)controller_thread, NULL);

    pthread_join(sensor_thread_id, NULL);
    pthread_join(controller_thread_id, NULL);

    return 0;
}