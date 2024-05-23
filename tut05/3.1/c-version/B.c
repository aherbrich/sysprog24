#include <pthread.h>
#include <stdio.h>

// Task 3.1 b) (understanding SIGNAL & WAIT)
//
// compile with: gcc -o 3_1_b ./tut05/3.1/c-version/B.c -lpthread
// execute with: ./3_1_b 
//
// PROBLEM:
// we have a doener stand with multiple employees (which work thread safe now -> see tut05/3.1/c-version/A.c)
// now we also have multiple customers that want to buy a doener
// -> we have a global variable "nr_of_doener" 
//    (that should only be accessed by one thread, customer or employee, at a time)
//


// SOLUTION:

// critical code
int nr_of_doener = 0;
void cut_meat() { /* simulate cutting meat */ }

// mutexes
pthread_mutex_t nr_of_doener_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cut_meat_mutex = PTHREAD_MUTEX_INITIALIZER;

// cond/signal variables
pthread_cond_t doener_ready = PTHREAD_COND_INITIALIZER;

void employee_thread(){
    pthread_mutex_lock(&cut_meat_mutex);    
    cut_meat();
    pthread_mutex_unlock(&cut_meat_mutex);  
    // the doener is READY!
    pthread_mutex_lock(&nr_of_doener_mutex);   
    nr_of_doener++;
    pthread_cond_signal(&doener_ready);         
    // signal that a doener is ready
    // under the hood (a lot happens here):
    // 1. does not simply set some cond to true (like how we learned it in our lectures)
    // 2. rather, it tells the scheduler to wake up a thread that is waiting on this cond
    // 3. the scheduler has a list of threads that are waiting on this cond
    //      -> it will wake up (one) of them, by some scheduling policy
    // 4. subsequent calls to signal() will wake up another thread (if there is still one waiting on the cond)                  
    pthread_mutex_unlock(&nr_of_doener_mutex); 
}


void customer_thread(){
    pthread_mutex_lock(&nr_of_doener_mutex);
    while(nr_of_doener == 0){
        pthread_cond_wait(&doener_ready, &nr_of_doener_mutex); 
        // wait until a doener is ready 
        // under the hood (a lot happens here):
        // 1. wait() unlocks the mutex for us
        // 2. wait() blocks the thread 
        //    (or even more accurate: the scheduler will put this thread to sleep
        //    and remember that it is waiting for some cond to be met, in our case,
        //    that "doener_ready" was signaled (which happens in employee_thread
        //    after "nr_of_doener" was incremented))
        // 3. on exit of wait() the thread gets woken up
        // 4. on exit of wait(), the mutex gets locked again 
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
