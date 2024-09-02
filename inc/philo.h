/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:25:43 by airyago           #+#    #+#             */
/*   Updated: 2024/09/02 12:38:13 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>

# define PHILO_MAX 300

typedef struct s_philo	t_philo;

typedef struct s_config
{
	size_t			num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
}	t_config;

typedef struct s_program
{
	t_config		*config;
	t_philo			*philos;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	bool			dead_flag;
}					t_program;

typedef struct s_philo
{
	pthread_t		thread;
	t_program		*program;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_config		*config;
	size_t			last_meal;
	size_t			start_time;
	int				id;
	int				meals_eaten;
	bool			eating;
	bool			*dead;
}					t_philo;

// Initialization
void	init_program(t_program *program, t_philo *philos, t_config *config);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program,
			pthread_mutex_t *forks);
int		init_threads(t_program *program, pthread_mutex_t *forks);

// Philosopher actions
void	*philosopher_routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

// Simulation control
void	*monitor_philos(void *program_ptr);
int		is_philo_dead(t_philo *philo);

// Utility functions
size_t	get_current_time(void);
void	log_philo_status(char *str, t_philo *philo);
int		ft_sleep(size_t milliseconds);
void	cleanup_resources(char *str, t_program *program,
			pthread_mutex_t *forks);
int		ft_strlen(const char *str);

// Argument handling
int		validate_args(int argc, char *argv[]);

// Number utilities
bool	ft_is_digit(const char c);
int		ft_atoi(const char *str);

#endif // PHILO_H
