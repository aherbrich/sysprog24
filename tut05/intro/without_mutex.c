#include <pthread.h>
#include <stdio.h>

// Version Nr. 1 (NO MUTEX)
//
// compile with: gcc -o without_mutex tut05/intro/without_mutex.c -lpthread
// execute with: ./without_mutex
//


int global_counter = 0;

// thread one
void incremment_thread1() {
    for (int i = 0; i < 1000000; i++) {
        global_counter++;
    }
}

// thread two
void incremment_thread2() {
    for (int i = 0; i < 1000000; i++) {
        global_counter++;
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

    // two threads each incrementing the global_counter by 1,000,000
    // so we expect the global_counter to be 2,000,000?
    // try running the program and see if that's the case 
    printf("Expected:\t2000000\nGot:\t\t%d\n", global_counter);

    // just some goofy output
    if (global_counter != 2000000) {
        printf("Huh? That's not right!\n");
    } else {
        printf("Yay! That's correct!\n");
    }

    return 0;
}