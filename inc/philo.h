/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:25:43 by airyago           #+#    #+#             */
/*   Updated: 2024/08/23 11:31:08 by airyago          ###   ########.fr       */
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

// 300 philosophers is the maximum number of philosophers in the evaluation
# define PHILO_MAX 300

typedef struct s_config
{
	size_t			num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int			num_times_to_eat;
}	t_config;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	size_t			*time_to_die;
	size_t			*time_to_eat;
	size_t			*time_to_sleep;
	int				*num_times_to_eat;
	size_t			last_meal;
	size_t			start_time;
	int				meals_eaten;
	bool			eating;
	bool			*dead;
	char			id;
	t_config		*config;
}					t_philo;

typedef struct s_program
{
	t_config		*config;
	t_philo			*philos;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	bool			dead_flag;
}					t_program;

// Num utils
bool	ft_is_digit(const char c);
int		ft_atoi(const char *str);

// Arg utils
int		validate_args(int argc, char *argv[]);
void	parse_args(int argc, char **argv, t_config *config);

// Program initialization
void	init_program(t_program *program, t_philo *philos, t_config *config);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks);
int		init_threads(t_program *program, pthread_mutex_t *forks);

// Utils
int		ft_sleep(size_t milliseconds);
void	cleanup_resources(char *str, t_program *program, pthread_mutex_t *forks);
int		ft_strlen(const char *str);

// Simulation control
void	*monitor_philos(void *program_ptr);
int		is_philo_dead(t_philo *philo);

// Philosopher actions
void	*philosopher_routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

// Utility functions
size_t	get_current_time(void);
void	log_philo_status(char *str, t_philo *philo);

#endif // PHILO_H
