/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:44:34 by airyago           #+#    #+#             */
/*   Updated: 2024/08/17 19:29:00 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positive_integer(const char *str)
{
	int num;

	num = ft_atoi(str);
	return (num > 0); // Verifica que el número sea mayor que cero
}

int	validate_arguments(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage:\n%s num_philosophers time_to_die "\
			"time_to_eat time_to_sleep "\
			"[number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_positive_integer(argv[i]))
		{
			printf("All arguments must integers bigger than 0." \
				"'%s' is invalid.\n", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
