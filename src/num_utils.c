/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airyago <airyago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:22:16 by airyago           #+#    #+#             */
/*   Updated: 2024/08/22 13:35:59 by airyago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_is_space(const char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\f' || c == '\r' || c == '\v');
}

bool	ft_is_digit(const char c)
{
	if (ft_is_space(c))
		return (false);
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	long long		num;
	int				sign;
	int				i;

	num = 0;
	sign = 1;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_is_digit(str[i]))
	{
		if (sign > 0 && num > (INT_MAX - (str[i] - '0')) / 10)
			return (INT_MAX);
		else if (sign < 0 && - num < (INT_MIN + (str[i] - '0')) / 10)
			return (INT_MIN);
		num = num * 10 + sign * (str[i] - '0');
		i++;
	}
	return (num);
}
