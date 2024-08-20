/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:57:56 by airyago           #+#    #+#             */
/*   Updated: 2024/08/20 11:48:18 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(int philo_id, char *msg)
{
	size_t	time;

	time = get_current_time();
	printf("%zu %i is %s\n", time, philo_id, msg);
	return ;
}

void *philosopher_routine(void *arg)
{
	t_philosopher *philo = (t_philosopher *)arg;

	while (1) {
		// Think (not involving forks)
		log_state(philo->id, "is thinking");

		// Attempt to pick up the left fork
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_state(philo->id, "has taken a fork");

		// Attempt to pick up the right fork
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_state(philo->id, "has taken a fork");

		// Eat
		log_state(philo->id, "is eating");
		philo->last_meal_time = get_current_time();  // Update last meal time
		usleep(philo->config->time_to_eat * 1000);  // Simulate eating

		// Put down the forks (unlock mutexes)
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);

		// Sleep
		log_state(philo->id, "is sleeping");
		usleep(philo->config->time_to_sleep * 1000);  // Simulate sleeping
	}
	return NULL;
}

int init_philosophers(t_philosopher **philosophers, t_fork *forks, t_config *config)
{
	int i;

	*philosophers = malloc(sizeof(t_philosopher) * config->num_philosophers);
	if (!*philosophers) {
		printf("Failed to allocate memory for philosophers\n");
		return (1);
	}
	i = 0;
	while (i < config->num_philosophers)
	{
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].left_fork = &forks[i];
		(*philosophers)[i].right_fork = &forks[(i + 1) % config->num_philosophers];
		(*philosophers)[i].config = config;
		(*philosophers)[i].last_meal_time = 0; // Initialize the last meal time to zero or the start time
		(*philosophers)[i].state_mutex = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init((*philosophers)[i].state_mutex, NULL) != 0) {
			printf("Failed to initialize state mutex for philosopher %d\n", i);
			// Clean up any created mutexes and threads
			return (1);
		}
		if (pthread_create(&(*philosophers)[i].thread, NULL, philosopher_routine, &(*philosophers)[i]) != 0) {
			printf("Failed to create thread for philosopher %d\n", i);
			// Cleanup already created threads and resources
			return (1);
		}
		i++;
	}
	return (0);
}
