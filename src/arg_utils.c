/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:44:34 by airyago           #+#    #+#             */
/*   Updated: 2024/08/22 13:38:51 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positive_integer(const char *str)
{
	int	i;
	int	num;

	i = 0;
	if (str[0] == '\0' || str[0] == '-')
		return (0);
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			return (0);
		i++;
	}
	num = ft_atoi(str);
	if (num <= 0)
		return (0);
	return (1);
}

/**
 * Validates the command line arguments.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings representing the command line arguments.
 * if number_times_to_eat is 0 the argument will be considered invalid
 * @return An integer indicating the success or failure of the validation.
 */
int	validate_args(int argc, char **argv)
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
