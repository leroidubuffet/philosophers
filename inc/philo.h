/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:55:02 by airyago           #+#    #+#             */
/*   Updated: 2024/08/19 13:36:46 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <limits.h>
# include <stdbool.h>

// Structure representing a philosopher's fork.
// `mutex` is a mutex lock for accessing the fork.
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

# Num utils
int		ft_atoi(const char *str);

# Arg utils
int		validate_args(int argc, char *argv[]);
void	parse_args(int argc, char **argv, t_config *config);

# General program
void	initialize_simulation(t_config config, t_fork **forks, \
		t_philosopher **philosophers);
void	clean_up(t_fork *forks, t_philosopher *philosophers);
#endif
