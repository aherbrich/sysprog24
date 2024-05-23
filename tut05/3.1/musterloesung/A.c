// WARNING: this is pseudo code and will not compile

// Task 3.1 a) (understanding MUTEXES)
//
// PROBLEM:
// we have a doener stand with 2 employees (two threads creating doeners)
// -> we have a global variable "nr_of_doener" (that should only be accessed by one thread at a time)
// -> we have a function "cut_meat" (that should only be executed by one thread at a time)
//


// SOLUTION:

// critical code
nr_of_doener = 0;
cut_meat() { /* simulate cutting meat */ }

// mutexe to wrap the critical code
nr_of_doener_mutex;
cut_meat_mutex;


void employee_thread(){
    // for a great doener, we need to cut ourselves some good doener fleisch
    // -> this should only be done by one employee at a time
    lock(cut_meat_mutex);    // lock the mutex for cutting meat
    cut_meat();
    pthread_mutex_unlock(cut_meat_mutex);  // unlock the mutex for cutting meat

    // add a little bit of salad and sauce to complete the doener
    // the doener is READY!

    // now we want to add the doener to the counter 
    // -> this should only be done by one employee at a time
    pthread_mutex_lock(&nr_of_doener_mutex);    // lock the mutex for adding doener to the counter
    nr_of_doener++;
    pthread_mutex_unlock(&nr_of_doener_mutex);  // unlock the mutex for adding doener to the counter
}
