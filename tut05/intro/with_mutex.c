#include <pthread.h>
#include <stdio.h>

// Version Nr. 2 (WITH MUTEX)
//
// compile with: gcc -o with_mutex tut05/intro/with_mutex.c -lpthread
// execute with: ./with_mutex
//

int global_counter = 0;

// you can ignore the syntax, it's just creating a mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 


// thread one (THREAD SAFE)
void incremment_thread1() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);         // lock the mutex
        // under the hood:
        // if mutex is already locked by another thread
        // -> this thread will wait until, the mutex is unlocked 
        //    (or even more accurate: the scheduler will put this thread
        //     to sleep, until the mutex is unlocked)
        // -> then the thread will lock the mutex itself 
        //    (or even more accurate: the scheduler will wake this thread
        //     up and let it lock the mutex)
                                    
        // critical section start                  
        global_counter++;
        // critical section end

        pthread_mutex_unlock(&mutex);       // unlock the mutex
    }
}

// thread two (THREAD SAFE)
void incremment_thread2() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);         // lock the mutex, same as above
        // critical section start
        global_counter++;
        // critical section end
        pthread_mutex_unlock(&mutex);       // unlock the mutex, same as above
    }
}

int main() {
    pthread_t thread1, thread2;

    // you can ignore the syntax, it's just creating two threads
    pthread_create(&thread1, NULL, (void *)incremment_thread1, NULL);
    pthread_create(&thread2, NULL, (void *)incremment_thread2, NULL);

    // when we call pthread_join the main thread
    // will wait for the specified thread to finish
    pthread_join(thread1, NULL);        // will wait here until thread1 finishes
    pthread_join(thread2, NULL);        // will wait here until thread2 finishes

    // Surprise! The global_counter is now 2,000,000
    printf("Expected:\t2000000\nGot:\t\t%d\n", global_counter);

    // just some goofy output
    if (global_counter != 2000000) {
        printf("Huh? That's not right!\n");
    } else {
        printf("Yay! That's correct!\n");
    }

    return 0;
}