/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:55:02 by airyago           #+#    #+#             */
/*   Updated: 2024/08/16 14:58:39 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

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

void	initialize_forks(t_fork *forks, int num_forks);
void	initialize_philosophers(t_philosopher *philosophers, int num_philosophers, int time_to_die, int time_to_eat, int time_to_sleep, int times_must_eat);

#endif
