/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:17:03 by airyago           #+#    #+#             */
/*   Updated: 2024/08/26 15:21:09 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (*philo->dead == true)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (0);
}

// Wait 1 millisecond to avoid deadlock
static void	*philo_lifecycle(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		ft_sleep(1);
	while (!check_philo_died(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (philo_ptr);
}

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
