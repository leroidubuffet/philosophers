/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:43:32 by airyago           #+#    #+#             */
/*   Updated: 2024/08/29 11:18:28 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Retrieves the current time.
 * timeval is used to obtain the current time with microsecond precision
 * tv_sec part represents the number of seconds since the Epoch
 * tv_usec part represents the number of microseconds
 * @return The current time as a size_t value.
 */
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return ((size_t) - 1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * Suspends the execution of the current thread for 
 * the specified number of milliseconds.
 *
 * @param milliseconds The number of milliseconds to sleep.
 */
int	ft_sleep(size_t milliseconds)
{
	size_t			start;
	size_t			current;
	struct timespec	ts;

	ts.tv_sec = 0;
	ts.tv_nsec = 100000;
	start = get_current_time();
	while (1)
	{
		current = get_current_time();
		if (current == (size_t) - 1)
			return (-1);
		if ((current - start) >= milliseconds)
			break ;
		nanosleep(&ts, NULL);
	}
	return (0);
}
