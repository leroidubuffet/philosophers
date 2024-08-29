/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:09:11 by airyago           #+#    #+#             */
/*   Updated: 2024/08/29 11:05:47 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/**
 * Logs the status of a philosopher.
 *
 * @param str The string to be logged.
 * @param philo A pointer to the philosopher struct.
 */
void	log_philo_status(char *str, t_philo *philo)
{
	size_t	time;
	int		philo_id;
	bool	is_dead;

	time = get_current_time() - philo->start_time;
	philo_id = philo->id;
	pthread_mutex_lock(&philo->program->dead_lock);
	is_dead = *philo->dead;
	pthread_mutex_unlock(&philo->program->dead_lock);
	if (!is_dead)
	{
		pthread_mutex_lock(&philo->program->write_lock);
		printf("%zu %d %s\n", time, philo_id, str);
		pthread_mutex_unlock(&philo->program->write_lock);
	}
}
