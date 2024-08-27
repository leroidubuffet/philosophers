/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:17:29 by airyago           #+#    #+#             */
/*   Updated: 2024/08/26 12:30:30 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks)
{
	size_t	current_time;
	size_t	i;

	current_time = get_current_time();
	i = 0;
	while (i < program->config->num_of_philos)
	{
		if (i == 0)
			philos[i].r_fork = &forks[program->config->num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		philos[i].l_fork = &forks[i];
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].time_to_die = &program->config->time_to_die;
		philos[i].time_to_eat = &program->config->time_to_eat;
		philos[i].time_to_sleep = &program->config->time_to_sleep;
		philos[i].num_times_to_eat = &program->config->num_times_to_eat;
		philos[i].last_meal = current_time;
		philos[i].start_time = current_time;
		philos[i].meals_eaten = 0;
		philos[i].eating = false;
		philos[i].dead = &program->dead_flag;
		philos[i].id = i + 1;
		philos[i].config = program->config;
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos, t_config *config)
{
	program->dead_flag = false;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	program->config = config;
}
