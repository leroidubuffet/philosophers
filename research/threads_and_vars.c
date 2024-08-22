#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Global variable that will be shared by threads
int shared_var = 0;

// Thread function that modifies the shared variable
// Because of race conditions, both threads perform the same action
// and the resulting value of the global variable is 1
void* increment_shared_var(void* arg) {
    int local_copy = shared_var;
    local_copy++; // Increment the local copy
    sleep(1); // Simulate some computation
    shared_var = local_copy; // Write back to the shared variable
    printf("Thread %d incremented shared_var to %d\n", *(int*)arg, shared_var);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    printf("Initial value of shared_var = %d\n", shared_var);

    // Create threads
    pthread_create(&thread1, NULL, increment_shared_var, &id1);
    pthread_create(&thread2, NULL, increment_shared_var, &id2);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of shared_var = %d\n", shared_var);

    return 0;
}
