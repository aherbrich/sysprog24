#include <pthread.h>
#include <stdio.h>

// Task 3.1 a) (understanding MUTEXES)
//
// compile with: gcc -o 1_A_pthread 1_A_pthread.c -lpthread
// execute with: ./1_A_pthread
//
//
// PROBLEM:
// we have a doener stand with 2 employees (two threads creating doeners)
// -> we have a global variable "nr_of_doener" (that should only be accessed by one thread at a time)
// -> we have a function "cut_meat" (that should only be executed by one thread at a time)
//

int nr_of_doener = 0;
void cut_meat() { /* simulate cutting meat */ }

// SOLUTION:

pthread_mutex_t nr_of_doener_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cut_meat_mutex = PTHREAD_MUTEX_INITIALIZER;


void employee_thread(){
    // for a great doener, we need to cut ourselves some good doener fleisch
    // -> this should only be done by one employee at a time
    pthread_mutex_lock(&cut_meat_mutex);    // lock the mutex for cutting meat
    cut_meat();
    pthread_mutex_unlock(&cut_meat_mutex);  // unlock the mutex for cutting meat

    // add a little bit of salad and sauce to complete the doener
    // the doener is READY!

    // now we want to add the doener to the counter 
    // -> this should only be done by one employee at a time
    pthread_mutex_lock(&nr_of_doener_mutex);    // lock the mutex for adding doener to the counter
    nr_of_doener++;
    pthread_mutex_unlock(&nr_of_doener_mutex);  // unlock the mutex for adding doener to the counter
}

int main(){
    pthread_t employee1, employee2;
    pthread_create(&employee1, NULL, (void *)employee_thread, NULL);
    pthread_create(&employee2, NULL, (void *)employee_thread, NULL);

    pthread_join(employee1, NULL);
    pthread_join(employee2, NULL);

    printf("Number of doener: %d\n", nr_of_doener);
    return 0;
}

