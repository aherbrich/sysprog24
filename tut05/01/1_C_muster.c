// WARNING: this file will not compile

// MUSTERLOESUNG:
// this is based on the signal and wait logic from the lectures
// in the lecture 
//      -> a signal() simply sets a cond to true (no matter if it is already true)
//      -> a wait() will block if the cond is false and
//         wake up if the cond is true and set the cond back to false
//      -> wait() ONLY blocks and has no other side effects (like unlocking a mutex)
//
// PROBLEM:
// we have a doener stand with 2 employees (which work thread safe now -> see 1_A_pthread.c
// we have customers that want to buy a doener (which work thread safe now -> see 1_B_pthread.c)
// now we want to only let employees produce doeners, if there are customers waiting
// -> we need to track a global variable "nr_of_customers" (that should only be accessed by one thread at a time)


int nr_of_doener = 0;
int nr_of_customers = 0;                                // new global variable
void cut_meat() { /* simulate cutting meat */ }

mutex_t only_one_customer_at_a_time_mutex;
mutex_t nr_of_doener_mutex;
mutex_t nr_of_customers_mutex;                          // new mutex
mutex_t only_one_responding_employee_at_a_time_mutex;   // new mutex
mutex_t cut_meat_mutex;

cond_t doener_ready;
cond_t customer_waiting;                                // new condition variable


void employee_thread(){
    // we should only prepare a doener if there is a customer waiting
    // hence, we have to check "nr_of_customers" before we start working

    // same logic like before, we have to lock the whole
    // "check & wait"-routine else if 2 customers signal,
    // while 2 employees are waiting we might accidentally "lose" a signal
    lock(only_one_responding_employee_at_a_time_mutex);
    lock(nr_of_customers_mutex);
    while(nr_of_customers == 0){
        unlock(nr_of_customers_mutex);
        wait(customer_waiting);
        lock(nr_of_customers_mutex);
    }
    nr_of_customers--;
    unlock(nr_of_customers_mutex);
    unlock(only_one_responding_employee_at_a_time_mutex);


    // this stays the same
    lock(cut_meat_mutex);    
    cut_meat();
    unlock(cut_meat_mutex);  

    lock(nr_of_doener_mutex);   
    nr_of_doener++;
    signal(doener_ready);        
    unlock(nr_of_doener_mutex); 
}

void customer_thread(){
    // if a customer thread is spawned, we have to increase the number of customers
    // and signal the employee threads that a customer is waiting

    // simple lock, signal, unlock
    lock(nr_of_customers_mutex);
    nr_of_customers++;
    signal(customer_waiting);
    unlock(nr_of_customers_mutex);

    // this stays the same
    lock(only_one_customer_at_a_time_mutex);
    lock(nr_of_doener_mutex);
    while(nr_of_doener == 0){
        unlock(nr_of_doener_mutex);
        wait(doener_ready);
        lock(nr_of_doener_mutex);  
    }
    nr_of_doener--;
    unlock(nr_of_doener_mutex);
    unlock(only_one_customer_at_a_time_mutex);
}