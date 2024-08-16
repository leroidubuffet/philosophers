/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:55:02 by airyago           #+#    #+#             */
/*   Updated: 2024/08/16 15:41:31 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

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

void	initialize_forks(t_fork *forks, int num_forks);
void	initialize_philosophers(t_philosopher *philosophers, t_config config);

#endif
