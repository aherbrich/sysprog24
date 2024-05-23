#include <pthread.h>
#include <stdio.h>

// Task 3.1 c) (understanding SIGNAL & WAIT & cross-thread communication)
//
// compile with: gcc -o 3_1_c ./tut05/3.1/c-version/C.c -lpthread
// execute with: ./3_1_c
//
// PROBLEM:
// we have a doener stand with multiple employees (which work thread safe now -> see tut05/3.1/c-version/A.c)
// we have multiple customers that want to buy a doener (which work thread safe now -> see tut05/3.1/c-version/B.c)
// now we want to only let employees produce doeners, if there are customers waiting
// -> we need to track an extra global variable "nr_of_customers" (that should only be accessed by one thread at a time)

// SOLUTION:

// critical code
int nr_of_doener = 0;
void cut_meat() { /* simulate cutting meat */ }
int nr_of_customers = 0;                                            // new global variable

// mutexes
pthread_mutex_t nr_of_doener_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cut_meat_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t nr_of_customers_mutex = PTHREAD_MUTEX_INITIALIZER;  // new mutex

// cond/signal variables
pthread_cond_t doener_ready = PTHREAD_COND_INITIALIZER;
pthread_cond_t customer_waiting = PTHREAD_COND_INITIALIZER;         // new condition variable

void employee_thread(){
    // for a great doener, it has to be prepared fresh
    // hence, we have to check if there are customers waiting
    // or else the doeners will get cold :(

    // same structure like in /tut05/3.1/c-version/B.c
    // (lock, wait, work, unlock)
    pthread_mutex_lock(&nr_of_customers_mutex);
    while(nr_of_customers == 0){
        pthread_cond_wait(&customer_waiting, &nr_of_customers_mutex);
    }
    nr_of_customers--;
    pthread_mutex_unlock(&nr_of_customers_mutex);

    // this stays the same
    pthread_mutex_lock(&cut_meat_mutex);    
    cut_meat();
    pthread_mutex_unlock(&cut_meat_mutex);  

    pthread_mutex_lock(&nr_of_doener_mutex);   
    nr_of_doener++;
    pthread_cond_signal(&doener_ready);         
    pthread_mutex_unlock(&nr_of_doener_mutex); 
}


void customer_thread(){
    // if a customer thread is spawned, we have to increase the number of customers
    // and signal the employee threads that a customer is waiting

    // same structure like in /tut05/3.1/c-version/B.c 
    // (lock, work, signal, unlock)
    pthread_mutex_lock(&nr_of_customers_mutex);
    nr_of_customers++;
    pthread_cond_signal(&customer_waiting);
    pthread_mutex_unlock(&nr_of_customers_mutex);

    // this stays the same
    pthread_mutex_lock(&nr_of_doener_mutex);
    while(nr_of_doener == 0){
        pthread_cond_wait(&doener_ready, &nr_of_doener_mutex); 
    }
    nr_of_doener--;
    pthread_mutex_unlock(&nr_of_doener_mutex);
}

int main(){
    pthread_t employees[1000];
    pthread_t customers[1000];
    for (int i = 0; i < 1000; i++){
        pthread_create(&employees[i], NULL, (void *)employee_thread, NULL);
        pthread_create(&customers[i], NULL, (void *)customer_thread, NULL);
    }

    for (int i = 0; i < 1000; i++){
        pthread_join(employees[i], NULL);
        pthread_join(customers[i], NULL);
    }

    printf("Expected:\t\t 0\nNumber of doener:\t %d\n", nr_of_doener);
    return 0;
}
