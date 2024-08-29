/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:17:03 by airyago           #+#    #+#             */
/*   Updated: 2024/08/29 18:37:27 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Checks if a philosopher has died.
 *
 * @param philo The philosopher to check.
 * @return Returns an integer indicating if the philosopher has died.
 */
static bool	check_philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (*philo->dead == true)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (false);
}

/**
 * @brief Function that represents the lifecycle of a philosopher.
 *
 * This function is responsible for executing the lifecycle of a philosopher.
 * It takes a pointer to a philosopher as an argument and returns a void pointer.
 * Wait 1 millisecond to avoid deadlock
 * if the philosopher is even numbered.
 *
 * @param philo_ptr A pointer to a philosopher object.
 * @return void* A void pointer.
 */
static void	*philo_lifecycle(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		ft_sleep(40);
	while (!check_philo_died(philo))
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (philo_ptr);
}

// Uncomment to print the number of meals eaten by each philosopher
// static void	print_meals_eaten(t_program *program)
// {
// 	size_t	i;

// 	printf("Meals eaten by each philosopher:\n");
// 	i = 0;
// 	while (i < program->config->num_of_philos)
// 	{
// 		pthread_mutex_lock(&program->meal_lock);
// 		printf("Philosopher %zu ate %d times\n", i + 1,
// 			program->philos[i].meals_eaten);
// 		pthread_mutex_unlock(&program->meal_lock);
// 		i++;
// 	}
// }

/**
 * Initializes the threads for the program.
 *
 * @param program A pointer to the program structure.
 * @param forks   An array of mutexes representing the forks.
 * @return        Returns 0 on success, -1 on failure.
 */
int	init_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	thread_monitor;
	size_t		i;

	i = 0;
	if (pthread_create(&thread_monitor, NULL, &monitor_philos, program) != 0)
		cleanup_resources("Thread creation error", program, forks);
	while (i < program->config->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				&philo_lifecycle, &program->philos[i]) != 0)
			cleanup_resources("Thread creation error", program, forks);
		i++;
	}
	pthread_join(thread_monitor, NULL);
	i = 0;
	while (i < program->config->num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
