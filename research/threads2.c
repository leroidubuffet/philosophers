#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_thread_data{
	int				increments;	// Número de incrementos que debe realizar el hilo
	int				thread_id;	// Identificador del hilo
	int				*counter;	// Referencia al contador compartido
	pthread_mutex_t	*mutex;		// Mutex para proteger el contador
} t_thread_data;

void *increment_counter(void *arg)
{
	t_thread_data *data = (t_thread_data *)arg;
	for (int i = 0; i < data->increments; i++)
	{
		pthread_mutex_lock(data->mutex);
		(*(data->counter))++;
		printf("Thread %d incremented the counter to %d\n", data->thread_id, *(data->counter));
		pthread_mutex_unlock(data->mutex);
	}
	return NULL;
}

int main(void) {
	int num_threads = 5;
	pthread_t threads[num_threads];
	t_thread_data thread_data[num_threads];
	int shared_counter = 0;
	pthread_mutex_t mutex;

	pthread_mutex_init(&mutex, NULL);

	// Crear hilos
	for (int i = 0; i < num_threads; i++)
	{
		thread_data[i].increments = 10; // Cada hilo realizará 10 incrementos
		thread_data[i].thread_id = i;
		thread_data[i].counter = &shared_counter;
		thread_data[i].mutex = &mutex;

		if (pthread_create(&threads[i], NULL, increment_counter, &thread_data[i]) != 0)
		{
			fprintf(stderr, "Failed to create thread %d\n", i);
			return 1;
		}
	}

	// Esperar a que todos los hilos terminen
	for (int i = 0; i < num_threads; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("Final counter value: %d\n", shared_counter);
	pthread_mutex_destroy(&mutex);

	return 0;
}
