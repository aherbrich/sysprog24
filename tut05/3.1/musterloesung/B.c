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
// now we also have multiple customers that want to buy a doener
// -> we have a global variable "nr_of_doener" 
//    (that should only be accessed by one thread, customer or employee, at a time)
//

// SOLUTION:

// critical code
nr_of_doener = 0;
cut_meat() { /* simulate cutting meat */ }

// mutexes
only_one_customer_at_a_time_mutex;
nr_of_doener_mutex;
cut_meat_mutex;

// cond/signal variables
doener_ready;


void employee_thread(){
    lock(cut_meat_mutex);    
    cut_meat();
    unlock(cut_meat_mutex);  
    // the doener is READY!
    lock(nr_of_doener_mutex);   
    nr_of_doener++;
    signal(doener_ready); // following the logic of the lectures, this is like setting "doener_ready" to true
    unlock(nr_of_doener_mutex); 
}

void customer_thread(){
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

    // we need to lock this whole routine (Z. 46-54)
    // with 'only_one_customer_at_a_time_mutex', because:
    //
    // imagine we have 2 customers and 2 employees
    // 1. both customers, enter the store but there are no doeners
    // 2. both customers will wait (on some cond "doener_ready")
    // 3. now BOTH employees finish their doener and signal the cond "doener_ready"
    //    (following the logic of the lectures, the "doener_ready" is set to true
    //     and then true again by the second signal)
    // 4. now the first customer wakes up from wait() and sets the cond "doener_ready" to false
    // 5. the second customer will not wake up, because the cond "doener_ready" is false again 
    //
    // summary:
    // -> two or more doeners can not be represented by the binary true/false of a cond
    // -> hence, we need to lock this whole routine (such that only one customer can wait at a time)
    //    and all other customer threads block on lock(only_one_customer_at_a_time_mutex)
}
