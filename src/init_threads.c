/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:17:03 by airyago           #+#    #+#             */
/*   Updated: 2024/08/22 17:41:07 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
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
		ft_usleep(1);
	while (!check_philo_dead(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (philo_ptr);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	thread_monitor;
	int			i;

	if (pthread_create(&thread_monitor, NULL, &monitor, program->philos) != 0)
		destory_all("Thread creation error", program, forks);
	i = 0;
	while (i < program->config->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_lifecycle,
				&program->philos[i]) != 0)
			destory_all("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(thread_monitor, NULL) != 0)
		destory_all("Thread join error", program, forks);
	while (i < program->config->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destory_all("Thread join error", program, forks);
		i++;
	}
	return (0);
}
