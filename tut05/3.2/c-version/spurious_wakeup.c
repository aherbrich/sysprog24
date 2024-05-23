#include <pthread.h>
#include <stdio.h>

// Task 3.2 b) (understanding SPURIOUS WAKEUPS)
//
// compile with: gcc -o spurious_wakeup tut05/3.2/c-version/spurious_wakeup.c -lpthread
// execute with: ./spurious_wakeup
//
// Run the code and observe the output.



int nr_of_doener = 0;
pthread_mutex_t nr_of_doener_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t doener_ready = PTHREAD_COND_INITIALIZER;

void employee_thread(){
    pthread_mutex_lock(&nr_of_doener_mutex);   
    nr_of_doener++;

    // pthread_cond_signal(&doener_ready);

    // contrary to what one might believe
    // pthread_cond_signal() wakes up ATLEAST one thread
    // but can wake up more than one thread.
    // in that case only one thread will get the doener
    // and all other threads woke up for nothing
    // i.e. spurious wakeups

    // to trigger spurious wakeups (reliably) we use broadcast instead of signal
    // broadcast wakes up ALL threads waiting on the condition variable
    pthread_cond_broadcast(&doener_ready);                  
                                   
    pthread_mutex_unlock(&nr_of_doener_mutex); 
}


void customer_thread(){
    pthread_mutex_lock(&nr_of_doener_mutex);
    while(nr_of_doener == 0){
        pthread_cond_wait(&doener_ready, &nr_of_doener_mutex);
        if (nr_of_doener != 0){
            printf("I'm customer %lld and I got THE doener!!!\n", (long long) pthread_self());
        } else {
            printf("I'm customer %lld and I got woke up for nothing :(\n", (long long) pthread_self());
        }
    }
    nr_of_doener--;
    pthread_mutex_unlock(&nr_of_doener_mutex);
}

int main(){
    pthread_t employee;
    pthread_t customers[10];

    // let 10 customers wait for a doener
    for (int i = 0; i < 10; i++){
        pthread_create(&customers[i], NULL, (void *)customer_thread, NULL);
    }

    // let the employee produce a doener
    pthread_create(&employee, NULL, (void *)employee_thread, NULL);

    pthread_join(employee, NULL);
    for (int i = 0; i < 10; i++){
        pthread_join(customers[i], NULL);
    }

    return 0;
}