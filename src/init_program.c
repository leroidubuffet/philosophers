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

static void	init_single_philo(t_philo *philo, t_program *program,
	pthread_mutex_t *forks)
{
	size_t	current_time;
	size_t	num_of_philos;

	num_of_philos = program->config->num_of_philos;
	current_time = get_current_time();
	philo->r_fork = &forks[(philo->id - 2 + num_of_philos) % num_of_philos];
	philo->l_fork = &forks[(philo->id - 1) % num_of_philos];
	philo->program = program;
	philo->config = program->config;
	philo->last_meal = current_time;
	philo->start_time = current_time;
	philo->meals_eaten = 0;
	philo->eating = false;
	philo->dead = &program->dead_flag;
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	while (i < program->config->num_of_philos)
	{
		philos[i].id = i + 1;
		init_single_philo(&philos[i], program, forks);
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
