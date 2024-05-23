// WARNING: this is pseudo code and will not compile

// WHY SIGNAL WAIT?
//
// PROBLEM:
// we have a doener stand with multiple employees (which work thread safe now -> see tut05/3.1/musterloesung/A.c)
// now we also have multiple customers that want to buy a doener
// -> we have a global variable "nr_of_doener" 
//    (that should only be accessed by one thread, customer or employee, at a time)
//                                          

// NAIVE SOLUTION (WITHOUT SIGNAL & WAIT):

nr_of_doener = 0;
cut_meat() { /* simulate cutting meat */ }

nr_of_doener_mutex;
cut_meat_mutex;

void employee_thread(){
    lock(cut_meat_mutex);    
    cut_meat();
    unlock(cut_meat_mutex);  
    // the doener is READY!
    lock(nr_of_doener_mutex);   
    nr_of_doener++;
    unlock(nr_of_doener_mutex); 
}

void customer_thread(){
    lock(&nr_of_doener_mutex);
    while(nr_of_doener == 0){
        unlock(&nr_of_doener_mutex);
        lock(&nr_of_doener_mutex);
    }
    nr_of_doener--;
    unlock(&nr_of_doener_mutex);

    // this will work(!) but it's not the best solution
    // we are essentially busy waiting (but in a thread safe way)
    // -> we should use a condition variable (a.k.a signal/wait) instead
    // -> advantage: we can sleep (a.k.a. wait) until the condition is met
    //               in our case, that "nr_of_doener" changed (a.k.a when a signal is sent)
    // -> advantage: we are not wasting CPU cycles for busy waiting
    // -> see tut05/3.1/musterloesung/B.c for the solution with signal/wait
}
