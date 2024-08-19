/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:08:18 by airyago           #+#    #+#             */
/*   Updated: 2024/08/19 14:09:38 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	if (validate_args(argc, argv) != 0)
		return (1);
	t_config	config;
	init_program(&config, argc, argv);

	// t_fork			*forks;
	// t_philosopher	*philosophers;

	// forks = malloc(config.num_philosophers * sizeof(t_fork));
	// philosophers = malloc(config.num_philosophers * sizeof(t_philosopher));
	// initialize_forks(forks, config.num_philosophers);
	// initialize_philosophers(philosophers, config);

	// // Aquí iría el código para crear hilos y manejar la simulación

	// Limpieza y salida
	// free(forks);
	// free(philosophers);
	return (0);
}
