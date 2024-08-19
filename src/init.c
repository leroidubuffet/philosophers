/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:04:28 by airyago           #+#    #+#             */
/*   Updated: 2024/08/19 14:19:02 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//DEBUG
#include <stdio.h>

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

void	init_program(t_config *config, int argc, char **argv)
{
	config->num_philosophers = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);

	if (argc == 6)
		config->times_must_eat = ft_atoi(argv[5]);
	else
		config->times_must_eat = -1;
	print_config(config); //DEBUG
}


