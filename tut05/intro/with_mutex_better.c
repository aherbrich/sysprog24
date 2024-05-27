#include <pthread.h>
#include <stdio.h>

// Version Nr. 2 (WITH MUTEX, but better)
//
// compile with: gcc -o with_mutex_better tut05/intro/with_mutex_better.c -lpthread
// execute with: ./with_mutex_better
//

int global_counter = 0;

// you can ignore the syntax, it's just creating a mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// WHY IS THIS THE BETTER VERSION?
// we dont need two seperate functions for the threads
// we can use one function and let it be called by both threads
// every thread will have its own stack and therefore its own local variables (like i in the for loop)

void increment_thread() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);         
        global_counter++;
        pthread_mutex_unlock(&mutex);    
    }
}

int main() {
    pthread_t thread1, thread2;

    // you can ignore the syntax, it's just creating two threads
    pthread_create(&thread1, NULL, (void *)increment_thread, NULL);
    pthread_create(&thread2, NULL, (void *)increment_thread, NULL);

    // when we call pthread_join the main thread
    // will wait for the specified thread to finish
    pthread_join(thread1, NULL);        // will wait here until thread1 finishes
    pthread_join(thread2, NULL);        // will wait here until thread2 finishes

    printf("Expected:\t2000000\nGot:\t\t%d\n", global_counter);

    // just some goofy output
    if (global_counter != 2000000) {
        printf("Huh? That's not right!\n");
    } else {
        printf("Yay! That's correct!\n");
    }

    return 0;
}