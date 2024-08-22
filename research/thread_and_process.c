#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *threadFunction(void *arg) {
	printf("Thread running in the same process. Thread ID = %ld, PID = %d\n", pthread_self(), getpid());
	return NULL;
}

int main(void) {
	printf("This is the starting process' pid (parent's) = %d\n", getpid());

	pid_t pid;
	pthread_t tid;

	pid = fork();

	if (pid < 0) {
		perror("fork failed");
		return 1;
	}
	else if (pid == 0) {  // Child process
		printf("This is the child process. PID = %d\n", getpid());
		// Creating a thread in the child process
		pthread_create(&tid, NULL, threadFunction, NULL);
		pthread_join(tid, NULL); // Waiting for the thread to finish
	}
	else { // Parent process
		printf("This is the parent process. PID = %d\n", getpid());
		// Also create a thread in the parent process
		pthread_create(&tid, NULL, threadFunction, NULL);
		pthread_join(tid, NULL); // Waiting for the thread to finish
	}

	return 0;
}
