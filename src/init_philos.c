/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:57:56 by airyago           #+#    #+#             */
/*   Updated: 2024/08/20 12:58:30 by airyago          ###   ########.fr       */
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

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo = (t_philosopher *)arg;

	while (1)
	{
		log_state(philo->id, "is thinking");
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_state(philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_state(philo->id, "has taken a fork");
		log_state(philo->id, "is eating");
		philo->last_meal_time = get_current_time();
		usleep(philo->config->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		log_state(philo->id, "is sleeping");
		usleep(philo->config->time_to_sleep * 1000);
	}
	return (NULL);
}

static int	allocate_philosophers(t_philosopher **philosophers, int num_philos)
{
	*philosophers = malloc(sizeof(t_philosopher) * num_philos);
	if (!*philosophers)
	{
		printf("Failed to allocate memory for philosophers\n");
		return (1);
	}
	return (0);
}

static int init_philosopher(t_philosopher *philosopher, int id, t_fork *left_fork, t_fork *right_fork, t_config *config)
{
	philosopher->id = id;
	philosopher->left_fork = left_fork;
	philosopher->right_fork = right_fork;
	philosopher->config = config;
	philosopher->last_meal_time = 0;
	philosopher->state_mutex = malloc(sizeof(pthread_mutex_t));
	if (philosopher->state_mutex == NULL
		|| pthread_mutex_init(philosopher->state_mutex, NULL) != 0)
	{
		printf("Failed to initialize state mutex for philosopher %d\n", id);
		return (1);
	}
	if (pthread_create(&philosopher->thread, NULL,
			philosopher_routine, philosopher) != 0)
	{
		printf("Failed to create thread for philosopher %d\n", id);
		pthread_mutex_destroy(philosopher->state_mutex);
		free(philosopher->state_mutex);
		return (1);
	}
	return (0);
}

static void	cleanup_philosophers_on_failure(t_philosopher *philosophers, int num_initialized)
{
	int	i;

	i = num_initialized - 1;
	while (i >= 0)
	{
		pthread_mutex_destroy(philosophers[i].state_mutex);
		free(philosophers[i].state_mutex);
		pthread_cancel(philosophers[i].thread);
		pthread_join(philosophers[i].thread, NULL);
		i--;
	}
	free(philosophers);
}

int init_philosophers(t_philosopher **philosophers, t_fork *forks, t_config *config)
{
	int i;

	if (allocate_philosophers(philosophers, config->num_philosophers) != 0)
		return (1);
	i = 0;
	while (i < config->num_philosophers)
	{
		if (init_philosopher(&(*philosophers)[i], i + 1, &forks[i], &forks[(i + 1) % config->num_philosophers], config) != 0)
		{
			cleanup_philosophers_on_failure(*philosophers, i);
			return (1);
		}
		i++;
	}
	return (0);
}
