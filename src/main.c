/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:08:53 by airyago           #+#    #+#             */
/*   Updated: 2024/08/26 12:29:27 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_config(t_config *config, char **argv)
{
	config->num_of_philos = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		config->num_times_to_eat = ft_atoi(argv[5]);
	else
		config->num_times_to_eat = 0;
}

// void	print_philos(t_philo *philos, t_config *config)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < config->num_of_philos)
// 	{
// 		printf("Philosopher %zu has eaten %d times\n", i + 1, philos[i].eat_count);
// 		i++;
// 	}
// }

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	t_config		config;

	if (validate_args(argc, argv) != 0)
		return (1);
	init_config(&config, argv);
	init_program(&program, philos, &config);
	init_philos(philos, &program, forks);
	init_forks(forks, config.num_of_philos);
	init_threads(&program, forks);
	return (0);
}
