#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//
// Task 3.3 b) (practicing SYNCHRONIZATION)
//
// compile with: gcc -o 3_3_b_lsg ./tut06/3.4/ping_pong_lsg.c -lpthread
// execute with: ./3_3_b_lsg
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

pthread_mutex_t next_action_mutex;                                              // new mutex
pthread_cond_t  next_action_switched;                                           // new cond/signal

void *thread_ping(void *nAction) {
    enum action *nextAction = (enum action *) nAction;
    while(1) {
        printf("%sPing%s\n", CYAN, RESET);

        pthread_mutex_lock(&next_action_mutex);                                 // lock mutex
        *nextAction = PONG;
        pthread_cond_signal(&next_action_switched);                             // signal other thread that it can continue

        while(*nextAction != PING) {                                            
            pthread_cond_wait(&next_action_switched, &next_action_mutex);       // unlock mutex, wait for signal, lock mutex on return
        }
        pthread_mutex_unlock(&next_action_mutex);                               // unlock mutex
    }
}

void *thread_pong(void *nAction) {
    enum action *nextAction = (enum action *) nAction;
    while(1) {
        pthread_mutex_lock(&next_action_mutex);                                 // lock mutex
        while(*nextAction != PONG) {
            pthread_cond_wait(&next_action_switched, &next_action_mutex);       // unlock mutex, wait for signal, lock mutex on return
        }
        pthread_mutex_unlock(&next_action_mutex);                               // unlock mutex

        printf("%s%sPong%s\n", BOLD, RED, RESET);

        pthread_mutex_lock(&next_action_mutex);                                 // lock mutex
        *nextAction = PING;
        pthread_cond_signal(&next_action_switched);                             // signal other thread that it can continue
        pthread_mutex_unlock(&next_action_mutex);                               // unlock mutex
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