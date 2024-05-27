#include <stdio.h>
#include <stdlib.h>

//
// Task 3.3 b) (practicing SYNCHRONIZATION)
//
// compile with: gcc -o 3_3_b_vorgabe ./tut06/3.4/ping_pong_vorgabe.c -lpthread
// execute with: ./3_3_b_vorgabe
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
    enum action *nextAction = malloc(sizeof(enum action));
    *nextAction = PING;
    
    thread_ping(nextAction);
    thread_pong(nextAction);

    // execute the following code
    // you will see that "ping" is printed forever
    // but "pong" is never printed (because its waiting for "ping" to finish)
    
    free(nextAction);
}