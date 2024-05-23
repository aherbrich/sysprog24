#include <pthread.h>
#include <stdio.h>

// Task 3.1 b) (understanding SIGNAL & WAIT)
//
// compile with: gcc -o 1_B_pthread_naive 1_B_pthread_naive.c -lpthread
// execute with: ./1_B_pthread_naive
//
//
// PROBLEM:
// we have a doener stand with 2 employees (which work thread safe now -> see 1_A_pthread.c)
// now we also have customers that want to buy a doener
// -> we have a global variable "nr_of_doener" (that should only be accessed by one thread,
//                                              customer or employee, at a time)                                          

int nr_of_doener = 0;
void cut_meat() { /* simulate cutting meat */ }

// NAIVE SOLUTION:

pthread_mutex_t nr_of_doener_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cut_meat_mutex = PTHREAD_MUTEX_INITIALIZER;

void employee_thread(){
    
    pthread_mutex_lock(&cut_meat_mutex);    
    cut_meat();
    pthread_mutex_unlock(&cut_meat_mutex);  
    // the doener is READY!
    pthread_mutex_lock(&nr_of_doener_mutex);   
    nr_of_doener++;
    pthread_mutex_unlock(&nr_of_doener_mutex); 
}

void customer_thread(){
    pthread_mutex_lock(&nr_of_doener_mutex);
    while(nr_of_doener == 0){
        pthread_mutex_unlock(&nr_of_doener_mutex);
        pthread_mutex_lock(&nr_of_doener_mutex);
        // this will work(!) but it's not the best solution
        // we are essentially busy waiting (but in a thread safe way)
        // -> we should use a condition variable instead
        // -> advantage: we can sleep until the condition is met
        //               in our case, that "nr_of_doener" changed 
        //               (we are not wasting CPU cycles)
        // -> see 1_B_pthread.c for a better solution
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