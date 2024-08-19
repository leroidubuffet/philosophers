/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:08:18 by airyago           #+#    #+#             */
/*   Updated: 2024/08/19 14:47:21 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_config(const t_config *config) {
    printf("Number of Philosophers: %d\n", config->num_philosophers);
    printf("Time to Die: %d ms\n", config->time_to_die);
    printf("Time to Eat: %d ms\n", config->time_to_eat);
    printf("Time to Sleep: %d ms\n", config->time_to_sleep);
    if (config->times_must_eat != -1) {  // Assuming -1 indicates it's not set
        printf("Times Must Eat: %d\n", config->times_must_eat);
    } else {
        printf("Times Must Eat: Not specified\n");
    }
}

//DEBUG

int main(int argc, char **argv)
{
	if (validate_args(argc, argv) != 0)
		return (1);
	t_config	config;
	t_fork		*forks;

	init_program(&config, argc, argv);
	if (init_resources(&config, &forks) != 0)
		return (1);
	print_config(&config); //DEBUG


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
