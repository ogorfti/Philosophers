/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:18:23 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/14 22:43:47 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_dead(t_philo *philo, int i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(philo->mutex_sleep);
	pthread_mutex_lock(philo->mutex_print);
	printf("%ld %d\033[0;31m died\033[0m\n",
		get_time() - philo[i].start_time, philo[i].id);
	while (j < philo->philo_count)
	{
		philo[j].stop = 0;
		j++;
	}
	pthread_mutex_unlock(philo->mutex_print);
	pthread_mutex_unlock(philo->mutex_sleep);
	if (philo[i].philo_count == 1)
		pthread_mutex_unlock(philo[i].left);
}

int	meal_return(t_philo *philo, int *i)
{
	pthread_mutex_lock(philo->data_race);
	pthread_mutex_lock(philo->mutex_sleep);
	if (meal_tracker(philo) == 1)
	{
		pthread_mutex_unlock(philo->mutex_sleep);
		pthread_mutex_unlock(philo->data_race);
		return (1);
	}
	pthread_mutex_unlock(philo->mutex_sleep);
	pthread_mutex_unlock(philo->data_race);
	*i = 0;
	return (0);
}

void	*check_dead(void *arg)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)arg;
	while (philo[i].stop)
	{
		pthread_mutex_lock(philo->data_race);
		while (i < philo->philo_count)
		{
			if (get_time() - philo[i].last_eat > philo->die_time
				&& philo[i].eat_count != 0)
			{
				handle_dead(philo, i);
				pthread_mutex_unlock(philo->data_race);
				return (NULL);
			}
			i++;
		}
		pthread_mutex_unlock(philo->data_race);
		if (meal_return(philo, &i))
			return (NULL);
	}
	return (NULL);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	int		is_done;

	philo = (t_philo *)arg;
	is_done = philo->stop;
	if (philo->id % 2 == 0)
		my_usleep(100, philo);
	while (is_done)
	{	
		taken_fork(philo);
		print_simulation(philo, EAT);
		my_usleep(philo->eat_time, philo);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		print_simulation(philo, SLEEP);
		my_usleep(philo->sleep_time, philo);
		pthread_mutex_lock(philo->mutex_sleep);
		is_done = philo->stop;
		pthread_mutex_unlock(philo->mutex_sleep);
		print_simulation(philo, THINK);
	}
	return (NULL);
}
