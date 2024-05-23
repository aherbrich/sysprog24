// WARNING: this is pseudo code and will not compile

// Task 3.2 c) (SYNCHRONIZING buffer access)
//
// PROBLEM:
// The sensor_thread and controller_thread are working on the same buffer.
// The sensor_thread is gathering data into the buffer 
// and the controller_thread is copying the data from the buffer.
// -> only one thread should access the buffer at a time
//

// SOLUTION:

// critical code
buffer[1024];
state = GATHERING;
gather_data_into_buffer() { /* simulate gathering data */ }
copy_buffer() { /* simulate copying data */ }

// non-critical code
void calculate_forecast() { /* simulate calculating forecast */ }

// mutexes
access_buffer_mutex;

// cond/signal variables
buffer_filled;
buffer_copied;


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

        calculate_forecast();                   // this can happen outside of lock (non-critical code)
    }
}