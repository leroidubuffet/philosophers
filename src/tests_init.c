#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include "philo.h"

// Test function for init_program
static void test_init_program() {
	t_program program;
	t_philo philos[5];
	t_config config = { .num_of_philos = 5, .time_to_die = 800, .time_to_eat = 200, .time_to_sleep = 200, .num_times_to_eat = 3 };

	init_program(&program, philos, &config);

	assert(program.dead_flag == false);
	assert(program.philos == philos);
	assert(program.config == &config);
	assert(pthread_mutex_trylock(&program.write_lock) == 0);
	assert(pthread_mutex_trylock(&program.dead_lock) == 0);
	assert(pthread_mutex_trylock(&program.meal_lock) == 0);

	pthread_mutex_unlock(&program.write_lock);
	pthread_mutex_unlock(&program.dead_lock);
	pthread_mutex_unlock(&program.meal_lock);

	printf("test_init_program passed\n");
}

// Test function for init_forks
static void test_init_forks() {
	pthread_mutex_t forks[5];

	init_forks(forks, 5);

	for (int i = 0; i < 5; i++) {
		assert(pthread_mutex_trylock(&forks[i]) == 0);
		pthread_mutex_unlock(&forks[i]);
	}

	printf("test_init_forks passed\n");
}

// Test function for init_philos
static void test_init_philos() {
	t_program program;
	t_philo philos[5];
	pthread_mutex_t forks[5];
	t_config config = { .num_of_philos = 5, .time_to_die = 800, .time_to_eat = 200, .time_to_sleep = 200, .num_times_to_eat = 3 };

	init_program(&program, philos, &config);
	init_forks(forks, 5);
	init_philos(philos, &program, forks, NULL);

	for (int i = 0; i < 5; i++) {
		assert(philos[i].id == i + 1);
		assert(philos[i].eating == 0);
		assert(philos[i].meals_eaten == 0);
		assert(philos[i].time_to_die == 800);
		assert(philos[i].time_to_eat == 200);
		assert(philos[i].time_to_sleep == 200);
		assert(philos[i].num_times_to_eat == 3);
		assert(philos[i].start_time == get_current_time());
		assert(philos[i].last_meal == 1000);
		assert(philos[i].write_lock == &program.write_lock);
		assert(philos[i].dead_lock == &program.dead_lock);
		assert(philos[i].meal_lock == &program.meal_lock);
		assert(philos[i].dead == &program.dead_flag);
		assert(philos[i].l_fork == &forks[i]);
		if (i == 0)
			assert(philos[i].r_fork == &forks[4]);
		else
			assert(philos[i].r_fork == &forks[i - 1]);
	}

	printf("test_init_philos passed\n");
}

int main() {
	test_init_program();
	test_init_forks();
	test_init_philos();
	return 0;
}
