/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:50:06 by airyago           #+#    #+#             */
/*   Updated: 2024/08/22 19:35:47 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_resources(char *str, t_program *program, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->config->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

// Checks if the philosopher is dead
int	is_philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

// Check if any philosopher died
static int	check_any_philo_dead(t_program *program)
{
	size_t	i;

	i = 0;
	while (i < program->config->num_of_philos)
	{
		if (is_philo_dead(&program->philos[i],
			*program->philos[i].time_to_die))
		{
			log_philo_status("died", &program->philos[i]);
			pthread_mutex_lock(program->philos[0].dead_lock);
			*program->philos->dead = 1;
			pthread_mutex_unlock(program->philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if all the philosophers ate the required number of meals
static int	check_all_philos_ate(t_program *program)
{
	size_t	i;
	int		finished_eating;

	i = 0;
	finished_eating = 0;
	if (program->config->num_times_to_eat == -1)
		return (0);
	while (i < program->config->num_of_philos)
	{
		pthread_mutex_lock(program->philos[i].meal_lock);
		if (program->philos[i].meals_eaten
			>= (int)*program->philos[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(program->philos[i].meal_lock);
		i++;
	}
	if (finished_eating == (int)program->config->num_of_philos)
	{
		pthread_mutex_lock(&program->dead_lock);
		*program->philos->dead = 1;
		pthread_mutex_unlock(&program->dead_lock);
		return (1);
	}
	return (0);
}

// Monitor thread routine
void	*monitor_philos(void *program_ptr)
{
	t_program	*program;

	program = (t_program *)program_ptr;
	while (1)
		if (check_any_philo_dead(program) == 1 ||
			check_all_philos_ate(program) == 1)
			break ;
	return (program);
}
