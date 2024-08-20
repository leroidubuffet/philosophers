/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:08:18 by airyago           #+#    #+#             */
/*   Updated: 2024/08/20 12:38:28 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//DEBUG
#include<inttypes.h>
static void print_config(const t_config *config) {
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

static void verify_philosophers(t_philosopher *philosophers, int num_philosophers)
{
    int i;

    printf("\nVerifying philosopher initialization:\n");
    i = 0;
    while (i < num_philosophers)
    {
        printf("Philosopher %d:\n", philosophers[i].id);
        printf("\tLeft Fork: %p\n", (void*)philosophers[i].left_fork);
        printf("\tRight Fork: %p\n", (void*)philosophers[i].right_fork);
        printf("\tState Mutex: %p\n", (void*)philosophers[i].state_mutex);
        printf("\tThread ID: %" PRIuPTR "\n", (uintptr_t)philosophers[i].thread);
        printf("\tLast Meal Time: %lld\n", philosophers[i].last_meal_time);
        i++;
    }
}

//DEBUG

int main(int argc, char **argv)
{
	t_config		config;
	t_fork			*forks = NULL;
	t_philosopher	*philos = NULL;

	if (validate_args(argc, argv) != 0)
		return (1);

	init_config(&config, argc, argv);

	if (init_resources(&config, &forks, &philos) != 0)
		return (1);

	print_config(&config); //DEBUG
	verify_philosophers(philos, config.num_philosophers); // Verify initialization
/*
	// Wait for philosopher threads to finish
	for (int i = 0; i < config.num_philosophers; i++)
		pthread_join(philos[i].thread, NULL);

	// Cleanup resources
	cleanup_resources(forks, config.num_philosophers);
	for (int i = 0; i < config.num_philosophers; i++)
	{
		pthread_mutex_destroy(philos[i].state_mutex);
		free(philos[i].state_mutex);
	}
	free(philos);
*/
	return (0);
}

