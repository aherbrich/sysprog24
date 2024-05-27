#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//
// Task 3.3 b) (practicing SYNCHRONIZATION)
//
// compile with: gcc -o 3_3_b_lsg_naive ./tut06/3.4/ping_pong_lsg_naive.c -lpthread
// execute with: ./3_3_b_lsg_naive
//
// SETTING:
// we have two functions "thread_ping" and "thread_pong" 
// -> "thread_ping" prints "ping" forever
// -> "thread_pong" prints "pong" forever
//
// PROBLEM:
// -> run each function on an own thread, such that both functions are executed in parallel
// -> synchronize the threads in a way that they print "ping" and "pong" alternately
//

// ignore the following defines
#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define BOLD "\033[1m"
#define RESET "\033[0m"


enum action{PING, PONG};

void *thread_ping(void *nAction) {
    enum action *nextAction = (enum action *) nAction;
    while(1) {
        printf("%sPing%s\n", CYAN, RESET);
        *nextAction = PONG;
    }
}

void *thread_pong(void *nAction) {
    enum action *nextAction = (enum action *) nAction;
    while(1) {
        printf("%s%sPong%s\n", BOLD, RED, RESET);
        *nextAction = PING;
    }
}

int main() {
    pthread_t t_ping;                                       // new pthread handle
    pthread_t t_pong;                                       // new pthread handle

    enum action *nextAction = malloc(sizeof(enum action));
    *nextAction = PING;

    pthread_create(&t_ping, 0, thread_ping, nextAction);    // start function ping in first thread
    pthread_create(&t_pong, 0, thread_pong, nextAction);    // start function pong in second thread

    pthread_join(t_ping, NULL);
    pthread_join(t_pong, NULL);

    // execute the following code
    // are 'ping' and 'pong' printed simultaneously?
    // are 'ping' and 'pong' printed ALTERANTIVELY?
    
    free(nextAction);
}