/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:27:48 by airyago           #+#    #+#             */
/*   Updated: 2024/08/29 13:54:37 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Think routine function
void	philo_think(t_philo *philo)
{
	log_philo_status("is thinking", philo);
}

// Sleep routine function
void	philo_sleep(t_philo *philo)
{
	if(!philo->program->dead_flag)
		return ;
	log_philo_status("is sleeping", philo);
	ft_sleep(philo->config->time_to_sleep);
}

/**
 * @brief Updates the meal information for a philosopher.
 *
 * This function is responsible for updating the meal information 
 * for a philosopher.
 * If there is only one philosopher, 
 * we unlock the fork and wait until the philosopher dies.
 * @param philo A pointer to the philosopher structure.
 */
static void	update_meal_info(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->meal_lock);
}

/**
 * Takes the forks for a philosopher.
 *
 * This function is responsible for a philosopher taking the forks
 * in order to start eating. It ensures that the philosopher can only
 * take the forks if they are both available.
 *
 * @param philo A pointer to the philosopher struct.
 * @return Returns 0 if the forks were successfully taken, -1 otherwise.
 */
static int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) != 0)
	{
		log_philo_status("error: unable to lock right fork", philo);
		return (0);
	}
	log_philo_status("has taken a fork", philo);
	if (philo->config->num_of_philos == 1)
	{
		ft_sleep(philo->config->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	if (pthread_mutex_lock(philo->l_fork) != 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		log_philo_status("error: unable to lock left fork", philo);
		return (0);
	}
	log_philo_status("has taken a fork", philo);
	return (1);
}

/**
 * @brief Function to perform the eating action for a philosopher.
 *
 * @param philo A pointer to the philosopher structure.
 */
void	philo_eat(t_philo *philo)
{
	if (is_philo_dead(philo) || !take_forks(philo))
		return ;
	if (is_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	philo->eating = true;
	log_philo_status("is eating", philo);
	update_meal_info(philo);
	ft_sleep(philo->config->time_to_eat);
	philo->eating = false;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
