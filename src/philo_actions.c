/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:27:48 by airyago           #+#    #+#             */
/*   Updated: 2024/08/22 19:39:17 by airyago          ###   ########.fr       */
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
	log_philo_status("is sleeping", philo);
	ft_sleep(*philo->time_to_sleep);
}

// Eat routine function
void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	log_philo_status("has taken a fork", philo);
	if (philo->config->num_of_philos == 1)
	{
		ft_sleep(*philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	log_philo_status("has taken a fork", philo);
	philo->eating = 1;
	log_philo_status("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_sleep(*philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
