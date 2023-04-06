/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:42:46 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/06 21:40:53 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	long	i;
	long	r;
	long	s;

	i = 0;
	r = 0;
	s = 1;
	while ((str[i] >= 9 && str [i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = s * (-1);
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		r = r * 10;
		r = r + str[i] - 48;
		i++;
	}
	return (s * r);
}

int	check_max(char *s)
{
	long	nbr;

	nbr = ft_atoi(s);
	if (nbr <= -2147483649 || nbr > 2147483647)
		return (1);
	return (0);
}

int	valid_number(char *s)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (s[i])
	{
		if (s[i] == '+' || s[i] == '-')
		{
			if (i > 0 || sign == 1)
				return (1);
			sign = 1;
		}
		else if (!(s[i] >= '0' && s[i] <= '9'))
			return (1);
		i++;
	}
	if (sign == 1 && i == 1)
		return (1);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	(void) ac;
	while (av[i])
	{
		if (valid_number(av[i]) || ft_atoi(av[i]) <= 0 || check_max(av[i]) == 1)
		{
			printf("Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}
