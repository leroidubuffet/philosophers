#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shared_var = 0;       // Shared variable
pthread_mutex_t lock;     // Mutex declaration

void* increment_shared_var(void* arg)
{
	pthread_mutex_lock(&lock); // Lock the mutex before accessing shared_var
	printf("Mutex locked\n");

	shared_var++;

	pthread_mutex_unlock(&lock); // Unlock the mutex after modifying shared_var
	printf("Mutex unlocked\n");

	printf("Thread %d incremented shared_var to %d\n", *(int*)arg, shared_var);
	return NULL;
}

int main(void)
{
	pthread_t thread1, thread2;
	int id1 = 1, id2 = 2;

	// Initialize the mutex
	pthread_mutex_init(&lock, NULL);

	printf("Initial value of shared_var = %d\n", shared_var);

	// Create threads
	pthread_create(&thread1, NULL, increment_shared_var, &id1);
	pthread_create(&thread2, NULL, increment_shared_var, &id2);

	// Wait for threads to finish
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Final value of shared_var = %d\n", shared_var);

	// Destroy the mutex after use
	pthread_mutex_destroy(&lock);

	return 0;
}
