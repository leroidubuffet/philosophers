#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define ARRAY_SIZE 10

// Global array that will be modified by threads
int shared_array[ARRAY_SIZE];

// Thread function that modifies part of the shared array
void* modify_array(void* arg) {
	int thread_id = *(int*)arg;

	// Each thread works on a different part of the array
	int start_index = (ARRAY_SIZE / NUM_THREADS) * thread_id;
	int end_index = start_index + (ARRAY_SIZE / NUM_THREADS);

	for (int i = start_index; i < end_index; i++) {
		shared_array[i] = thread_id + 1;  // Each thread assigns a different value
		sleep(1);  // Simulate some work
	}

	printf("Thread %d modified the array from index %d to %d\n", thread_id, start_index, end_index - 1);
	return NULL;
}

int main() {
	pthread_t threads[NUM_THREADS];
	int thread_ids[NUM_THREADS];

	// Initialize array with zero
	for (int i = 0; i < ARRAY_SIZE; i++) {
		shared_array[i] = 0;
	}

		// Print the initial state of the array
	printf("Initial array state: ");
	for (int i = 0; i < ARRAY_SIZE; i++) {
		printf("%d ", shared_array[i]);
	}
	printf("\n");

	// Create threads
	for (int i = 0; i < NUM_THREADS; i++) {
		thread_ids[i] = i;
		pthread_create(&threads[i], NULL, modify_array, &thread_ids[i]);
	}

	// Wait for threads to finish
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	// Print the final state of the array
	printf("Final array state: ");
	for (int i = 0; i < ARRAY_SIZE; i++) {
		printf("%d ", shared_array[i]);
	}
	printf("\n");

	return 0;
}
