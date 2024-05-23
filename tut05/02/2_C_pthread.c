#include <pthread.h>
#include <stdio.h>

// Task 3.2 c) (SYNCHRONIZING buffer access)
//
// compile with: gcc -o 2_C_pthread 2_C_pthread.c -lpthread
// execute with: ./2_C_pthread
//

#define GATHERING 0
#define COPYING 1

typedef int state_t;

char buffer[1024];
state_t state = GATHERING;
void gather_data_into_buffer() { /* simulate gathering data */ }
void copy_buffer() { /* simulate copying data */ }
void calculate_forecast() { /* simulate calculating forecast */ }

pthread_mutex_t access_buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_filled = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_copied = PTHREAD_COND_INITIALIZER;


void sensor_thread(){
    while(1) {
        pthread_mutex_lock(&access_buffer_mutex);

        printf("Gathering data\n");
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

        printf("Copying data\n");
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