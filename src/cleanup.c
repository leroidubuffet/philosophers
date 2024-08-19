/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:47:52 by airyago           #+#    #+#             */
/*   Updated: 2024/08/19 14:54:55 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_resources(t_fork *forks, int num_philosophers)
{
	int i;

	i = 0;
	while (i++ < num_philosophers)
		pthread_mutex_destroy(&forks[i].mutex);
	free(forks);
}
