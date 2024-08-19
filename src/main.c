/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:08:18 by airyago           #+#    #+#             */
/*   Updated: 2024/08/19 13:36:45 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	if (validate_args(argc, argv) != 0)
		return (1);

/*	t_config	config;

	config.num_philosophers = atoi(argv[1]);
	config.time_to_die = atoi(argv[2]);
	config.time_to_eat = atoi(argv[3]);
	config.time_to_sleep = atoi(argv[4]);

	if (argc == 6)
		config.times_must_eat = atoi(argv[5]);
	else
		config.times_must_eat = -1;

	t_fork			*forks;
	t_philosopher	*philosophers;

	forks = malloc(config.num_philosophers * sizeof(t_fork));
	philosophers = malloc(config.num_philosophers * sizeof(t_philosopher));
	initialize_forks(forks, config.num_philosophers);
	initialize_philosophers(philosophers, config);

	// Aquí iría el código para crear hilos y manejar la simulación

	// Limpieza y salida
	free(forks);
	free(philosophers);*/
	return (0);
}
