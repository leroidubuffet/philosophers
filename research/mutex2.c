#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;

void* thread_function(void* arg) {
    // Lock the mutex
    pthread_mutex_lock(&mutex);
    printf("Thread %d has locked the mutex.\n", *(int*)arg);

    // Critical section
    // ...

    // Unlock the mutex
    pthread_mutex_unlock(&mutex);
    printf("Thread %d has unlocked the mutex.\n", *(int*)arg);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&thread1, NULL, thread_function, &id1);
    pthread_create(&thread2, NULL, thread_function, &id2);

    // Join threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
