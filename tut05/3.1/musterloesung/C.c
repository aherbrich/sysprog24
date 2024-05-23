// WARNING: this is pseudo code and will not compile

// MUSTERLOESUNG:
// this is based on the signal and wait logic from the lectures
// -> a signal() simply sets a cond to true (no matter if it is already true)
// -> a wait() will block if the cond is false,
//    and wake up if the cond is true and set the cond back to false
// -> wait() ONLY blocks and has no other side effects (like unlocking a mutex)
//
// PROBLEM:
// we have a doener stand with multiple employees (which work thread safe now -> see tut05/3.1/musterloesung/A.c)
// we have multiple customers that want to buy a doener (which work thread safe now -> see tut05/3.1/musterloesung/B.c)
// now we want to only let employees produce doeners, if there are customers waiting
// -> we need to track an extra global variable "nr_of_customers" (that should only be accessed by one thread at a time)


// SOLUTION:

// critical code
nr_of_doener = 0;
nr_of_customers = 0;                                
cut_meat() { /* simulate cutting meat */ }              // new global variable

// mutexes
only_one_customer_at_a_time_mutex;
nr_of_doener_mutex;
cut_meat_mutex;
nr_of_customers_mutex;                                  // new mutex
only_one_responding_employee_at_a_time_mutex;           // new mutex

// cond/signal variables
doener_ready;
customer_waiting;                                       // new condition variable


void employee_thread(){
    // for a great doener, it has to be prepared fresh
    // hence, we have to check if there are customers waiting
    // or else the doeners will get cold :(

    // same logic like before, we have to lock the whole
    // "check & wait"-routine else if 2 customers signal that they are there,
    // while 2 employees are waiting we might accidentally "lose" a signal
    // see /tut05/3.1/musterloesung/B.c for more information
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

    // same structure like in /tut05/3.1/musterloesung/B.c
    // (lock, work, signal, unlock)
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
