// WARNING: this file will not compile

// MUSTERLOESUNG:
// this is based on the signal and wait logic from the lectures
// in the lecture 
//      -> a signal() simply sets a cond to true (no matter if it is already true)
//      -> a wait() will block if the cond is false and
//         wake up if the cond is true and set the cond back to false
//      -> wait() ONLY blocks and has no other side effects (like unlocking a mutex)
//


char buffer[1024];
state_t state = GATHERING;

void gather_data_into_buffer() { /* simulate gathering data */ }
void copy_buffer() { /* simulate copying data */ }
void calculate_forecast() { /* simulate calculating forecast */ }

mutex_t access_buffer_mutex;
cond_t buffer_filled;
cond_t buffer_copied;


void sensor_thread(){
    while(1) {
        lock(access_buffer_mutex);

        gather_data_into_buffer();
        state = COPYING;                        // now we switch to state COPYING 
        signal(buffer_filled);                  // signal that other thread can start copying
        
        unlock(access_buffer_mutex);

        // now we loop here until the other thread is done copying
        lock(access_buffer_mutex);
        while(state == COPYING){
            unlock(access_buffer_mutex);
            wait(buffer_copied);
            lock(access_buffer_mutex);
        }
        unlock(access_buffer_mutex);
    }
}

void controller_thread(){
    while(1) {
        lock(access_buffer_mutex);

        // we loop here until the sensor thread is done gathering
        while(state == GATHERING){
            unlock(access_buffer_mutex);
            wait(buffer_filled);
            lock(access_buffer_mutex);
        }

        copy_buffer();
        state = GATHERING;                      // now we switch to state GATHERING 
        signal(buffer_copied);                  // signal that other thread can start gathering again

        unlock(access_buffer_mutex);

        calculate_forecast();                  // this can happen outside of the critical section
    }
}