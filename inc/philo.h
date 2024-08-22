/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:25:43 by airyago           #+#    #+#             */
/*   Updated: 2024/08/22 13:38:42 by airyago          ###   ########.fr       */
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

// Num utils
bool	ft_is_digit(const char c);
int		ft_atoi(const char *str);

// Arg utils
int		validate_args(int argc, char *argv[]);
void	parse_args(int argc, char **argv, t_config *config);


#endif // PHILO_H
