/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:43:32 by airyago           #+#    #+#             */
/*   Updated: 2024/08/22 16:20:34 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
