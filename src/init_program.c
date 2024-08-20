/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:04:28 by airyago           #+#    #+#             */
/*   Updated: 2024/08/20 12:08:01 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fork	*init_forks(int num_philosophers)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * num_philosophers);
	if (!forks)
	{
		printf("Failed to allocate memory for forks\n");
		return (NULL);
	}
	i = 0;
	while (i < num_philosophers)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			printf("Failed to initialize mutex for fork %d\n", i);
			cleanup_resources(forks, i);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	init_resources(t_config *config, t_fork **forks, t_philosopher **philos)
{
	*forks = init_forks(config->num_philosophers);
	if (*forks == NULL)
		return (1);

	if (init_philosophers(philos, *forks, config) != 0)
	{
		cleanup_resources(*forks, config->num_philosophers);
		return (1);
	}

	// Initialize other resources here if necessary
	return (0);
}

void	init_config(t_config *config, int argc, char **argv)
{
	config->num_philosophers = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		config->times_must_eat = ft_atoi(argv[5]);
	else
		config->times_must_eat = -1;
}
