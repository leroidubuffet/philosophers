/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:55:02 by airyago           #+#    #+#             */
/*   Updated: 2024/08/16 16:10:57 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>

// Each fork has a mutex associated with it so only one philo can use it
typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

/* Philo structure with all the corresponding parameters*/
typedef struct s_philosopher
{
	int			id;
	int			left_fork_id;
	int			right_fork_id;
	pthread_t	thread;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_must_eat;
}	t_philosopher;

typedef struct s_config
{
	int	num_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
}	t_config;

void	parse_args(int argc, char **argv, t_config *config);
void	initialize_simulation(t_config config, t_fork **forks, \
		t_philosopher **philosophers);
void	clean_up(t_fork *forks, t_philosopher *philosophers);
#endif
