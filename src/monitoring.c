/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:50:06 by airyago           #+#    #+#             */
/*   Updated: 2024/08/29 18:31:22 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/**
 * Cleans up the resources used by the program.
 *
 * @param str The string parameter.
 * @param program The pointer to the program structure.
 * @param forks The pointer to the array of mutex locks representing the forks.
 */
void	cleanup_resources(char *str, t_program *program, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->start_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->config->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

/**
 * Checks if a philosopher is dead.
 *
 * This function takes a pointer to a `t_philo` structure representing 
 * a philosopher and checks if the philosopher is dead. 
 * It returns an integer value indicating whether the philosopher 
 * is dead or not.
 * Added time buffer to account for time it takes to print
 * and timing inconsistencies due to different execution speeds.
 *
 * @param philo A pointer to the philosopher to check.
 * @return 1 if the philosopher is dead, 0 otherwise.
 */
int	is_philo_dead(t_philo *philo)
{
	size_t	current_time;
	size_t	last_meal_time;

	pthread_mutex_lock(&philo->program->meal_lock);
	current_time = get_current_time();
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->program->meal_lock);
	if (current_time - last_meal_time >= philo->config->time_to_die + 0)
	{
		return (1);
	}
	return (0);
}

/**
 * Checks if any philosopher is dead.
 *
 * @param program A pointer to the program structure.
 * @return `true` if any philosopher is dead, `false` otherwise.
 */
static bool	check_any_philo_dead(t_program *program)
{
	size_t	i;

	i = 0;
	while (i < program->config->num_of_philos)
	{
		if (is_philo_dead(&program->philos[i]))
		{
			log_philo_status("died", &program->philos[i]);
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = true;
			pthread_mutex_unlock(&program->dead_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

/**
 * Checks if all philosophers have finished eating.
 *
 * This function takes a pointer to a `t_program` structure representing
 * the program and checks if all philosophers have finished eating.
 *
 * @param program A pointer to the program structure.
 * @return true if all philosophers have finished eating, false otherwise.
 */
static bool	check_all_philos_ate(t_program *program)
{
	size_t	i;
	size_t	finished_eating;

	i = 0;
	if (program->config->num_times_to_eat == 0)
		return (false);
	finished_eating = 0;
	while (i < program->config->num_of_philos)
	{
		pthread_mutex_lock(&program->meal_lock);
		if (program->philos[i].meals_eaten >= program->config->num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(&program->meal_lock);
		i++;
	}
	if (finished_eating == program->config->num_of_philos)
	{
		pthread_mutex_lock(&program->dead_lock);
		program->dead_flag = true;
		pthread_mutex_unlock(&program->dead_lock);
		return (true);
	}
	return (false);
}

/**
 * Monitors the philosophers' activities.
 *
 * @param program_ptr A pointer to the program structure.
 * @return void
 */
void	*monitor_philos(void *program_ptr)
{
	t_program	*program;

	program = (t_program *)program_ptr;
	while (1)
	{
		if (check_any_philo_dead(program) == true
			|| check_all_philos_ate(program) == true)
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = true;
			pthread_mutex_unlock(&program->dead_lock);
			break ;
		}
	}
	return (NULL);
}
