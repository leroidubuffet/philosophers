#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> // For malloc/free

void *thread_function(void *arg) {
	int *num = (int *)arg;
	printf("Thread %d is running\n", *num);
	free(num); // Liberar la memoria asignada
	return NULL;
}

int main(void)
{
	pthread_t thread;
	int *num = malloc(sizeof(int)); // Asignar memoria para num
	if (num == NULL)
	{
		fprintf(stderr, "Error allocating memory\n");
		return (1);
	}

	*num = 99;
	if (pthread_create(&thread, NULL, thread_function, num) != 0)
	{
		fprintf(stderr, "Error creating thread\n");
		free(num); // Asegurar que se libere la memoria en caso de error
		return (1);
	}

	if (pthread_join(thread, NULL) != 0)
	{
		fprintf(stderr, "Error joining thread\n");
		return (2);
	}

	return (0);
}
