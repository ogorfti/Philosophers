/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:58:29 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/06 23:20:52 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_colors(t_philo *philo, char *str)
{
	if (!ft_strcmp(str, SLEEP))
		printf("%ld %d \033[0;36m%s\033[0m\n",
			get_time() - philo->start_time, philo->id, str);
	if (!ft_strcmp(str, EAT))
		printf("%ld %d \033[0;35m%s\033[0m\n",
			get_time() - philo->start_time, philo->id, str);
	if (!ft_strcmp(str, THINK))
		printf("%ld %d \033[0;32m%s\033[0m\n",
			get_time() - philo->start_time, philo->id, str);
	if (!ft_strcmp(str, FORK))
		printf("%ld %d \033[0;34m%s\033[0m\n",
			get_time() - philo->start_time, philo->id, str);
}

void	print_simulation(t_philo *philo, char *str)
{	
	pthread_mutex_lock(philo->data_race);
	pthread_mutex_lock(philo->mutex_print);
	if (philo->stop != 0)
		my_colors(philo, str);
	pthread_mutex_unlock(philo->mutex_print);
	if (ft_strcmp(str, EAT) == 0)
	{
		philo->last_eat = get_time();
		if (philo->eat_count > 0)
			philo->eat_count--;
	}
	pthread_mutex_unlock(philo->data_race);
}

void	taken_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_simulation(philo, FORK);
	pthread_mutex_lock(philo->right);
	print_simulation(philo, FORK);
}

int	meal_tracker(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
	{
		if (philo[i].eat_count > 0 || philo[i].eat_count == -1)
			return (0);
		i++;
	}
	i = 0;
	while (i < philo->philo_count)
	{
		if (philo[i].eat_count == 0)
			philo[i].stop = 0;
		i++;
	}
	return (1);
}
