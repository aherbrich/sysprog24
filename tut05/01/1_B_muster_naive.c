// WARNING: this file will not compile

// NOT A MUSTERLOESUNG, but a naive solution to the problem
//
// PROBLEM:
// we have a doener stand with 2 employees (which work thread safe now -> see 1_A_pthread.c)
// now we also have customers that want to buy a doener
// -> we have a global variable "nr_of_doener" (that should only be accessed by one thread,
//                                              customer or employee, at a time)   

int nr_of_doener = 0;
void cut_meat() { /* simulate cutting meat */ }

mutex_t nr_of_doener_mutex;
mutex_t cut_meat_mutex;


cond_t doener_ready;

// the employee thread is the same -> see 1_A_pthread.c
void employee_thread(){
    lock(cut_meat_mutex);    
    cut_meat();
    unlock(cut_meat_mutex);  
    // the doener is READY!
    lock(nr_of_doener_mutex);   
    nr_of_doener++;    
    unlock(nr_of_doener_mutex); 
}

void employee_thread(){
    lock()
    cut_meat()
    // salat machen
    nr_of_doener++
    unlock()
}

// new logic HERE!
void customer_thread(){
    lock(nr_of_doener_mutex);
    while(nr_of_doener == 0){
        unlock(nr_of_doener_mutex);
        // this will work(!) but it's not the best solution
        // we are essentially busy waiting (but in a thread safe way)
        // -> we should use a condition variable instead
        // -> advantage: we can sleep until the condition is met
        //               in our case, that "nr_of_doener" changed 
        //               (we are not wasting CPU cycles)
        // -> see 1_B_muster.c for a better solution
        lock(nr_of_doener_mutex);  
    }

    nr_of_doener--;

    unlock(nr_of_doener_mutex);
}