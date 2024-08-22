/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:25:43 by airyago           #+#    #+#             */
/*   Updated: 2024/08/22 14:16:48 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
// 300 philosophers is the maximum number of philosophers in the evaluation
# define PHILO_MAX 300

typedef struct s_config
{
	int	num_of_philos;
	int	num_times_to_eat;
}	t_config;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				meals_eaten;
	bool			eating;
	bool			*dead;
	char			id;
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

#endif // PHILO_H
