/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:17:03 by airyago           #+#    #+#             */
/*   Updated: 2024/08/22 19:20:54 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// Previously check_philo_dead
static int	check_philo_died(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == true)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
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

int	init_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	thread_monitor;
	size_t		i;

	if (pthread_create(&thread_monitor, NULL, &monitor_philos, program) != 0)
		cleanup_resources("Thread creation error", program, forks);
	i = 0;
	while (i < program->config->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_lifecycle,
				&program->philos[i]) != 0)
			cleanup_resources("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(thread_monitor, NULL) != 0)
		cleanup_resources("Thread join error", program, forks);
	while (i < program->config->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			cleanup_resources("Thread join error", program, forks);
		i++;
	}
	return (0);
}
