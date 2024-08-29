/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:17:29 by airyago           #+#    #+#             */
/*   Updated: 2024/08/29 14:50:18 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Initializes a single philosopher.
 * 
 * @param philo     Pointer to the philosopher to be initialized.
 * @param program   Pointer to the program structure.
 * @param forks     Array of mutexes representing the forks.
 */
static void	init_single_philo(t_philo *philo, t_program *program, \
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
	philo->meals_eaten = 0;
	philo->eating = false;
	philo->dead = &program->dead_flag;
}

/**
 * Initializes the philosophers and their resources.
 *
 * @param philos The array of philosophers.
 * @param program The program configuration.
 * @param forks The array of forks (mutexes).
 */
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&program->start_lock);
	while (i < program->config->num_of_philos)
	{
		philos[i].id = i + 1;
		init_single_philo(&philos[i], program, forks);
		i++;
	}
	philos->start_time = get_current_time();
	pthread_mutex_unlock(&program->start_lock);
}

/**
 * Initializes the forks (mutexes).
 *
 * @param forks     The array of forks (mutexes).
 * @param philo_num The number of philosophers.
 */
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

/**
 * Initializes the program structure with the given philosopher, 
 * configuration, and locks.
 *
 * @param program The program structure to initialize.
 * @param philos The array of philosophers.
 * @param config The configuration for the program.
 */
void	init_program(t_program *program, t_philo *philos, t_config *config)
{
	program->dead_flag = false;
	program->philos = philos;
	pthread_mutex_init(&program->start_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	program->config = config;
}
