#include <pthread.h>
#include <stdio.h>

// WHY SIGNAL WAIT?
//
// compile with: gcc -o why_signal_wait ./tut05/3.1/c-version/why_signal_wait.c -lpthread
// execute with: ./why_signal_wait
//
//
// PROBLEM:
// we have a doener stand with multiple employees (which work thread safe now -> see tut05/3.1/c-version/A.c)
// now we also have multiple customers that want to buy a doener
// -> we have a global variable "nr_of_doener" 
//    (that should only be accessed by one thread, customer or employee, at a time)
//                                          

// NAIVE SOLUTION (WITHOUT SIGNAL & WAIT):

int nr_of_doener = 0;
void cut_meat() { /* simulate cutting meat */ }

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
    }
    nr_of_doener--;
    pthread_mutex_unlock(&nr_of_doener_mutex);

    // this will work(!) but it's not the best solution
    // we are essentially busy waiting (but in a thread safe way)
    // -> we should use a condition variable (a.k. signal/wait) instead
    // -> advantage: we can sleep (a.k.a. wait) until the condition is met
    //               in our case, that "nr_of_doener" changed (a.k.a when a signal is sent)
    // -> advantage: we are not wasting CPU cycles for busy waiting
    // -> see tut05/3.1/c-version/B.c for the solution with signal/wait
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
