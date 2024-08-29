/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:08:53 by airyago           #+#    #+#             */
/*   Updated: 2024/08/29 10:56:11 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Initializes the configuration struct with the provided arguments.
 *
 * @param config The configuration struct to be initialized.
 * @param argv The command line arguments.
 */
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
