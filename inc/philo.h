/* ************************************************************************** */
/*				           */
/*				    :::      ::::::::   */
/*   philo.h				     :+:      :+:    :+:   */
/*				+:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*				         +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:55:02 by airyago           #+#    #+#				*/
/*   Updated: 2024/08/19 14:22:18 by airyago          ###   ########.fr       */
/*				           */
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
# include <unistd.h>
# include <sys/time.h>

/*
`mutex` is a mutex lock for accessing the fork.
*/
typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_config
{
	int	num_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
}	t_config;

/*
Philo structure with all the corresponding parameters
*/
typedef struct s_philosopher
{
	int				id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	t_config		*config;
	long long		last_meal_time;   // Timestamp of the last time the philosopher ate
	pthread_mutex_t *state_mutex;     // Mutex to protect the philosopher's state
}	t_philosopher;

// Num utils
bool	ft_is_digit(const char c);
int		ft_atoi(const char *str);

// Arg utils
int		validate_args(int argc, char *argv[]);
void	parse_args(int argc, char **argv, t_config *config);

// General program
void	init_program(t_config *config, int argc, char **argv);
int		init_resources(t_config *config, t_fork **forks);
void	initialize_simulation(t_config config, t_fork **forks, \
		t_philosopher **philosophers);
void	cleanup_resources(t_fork *forks, int num_philosophers);
void	log_state(int philo_id, char *msg);

// Time
size_t	get_current_time(void);

#endif
