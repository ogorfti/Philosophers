/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:18:23 by ogorfti           #+#    #+#             */
/*   Updated: 2023/03/28 15:27:57 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_dead(t_philo *philo, int i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(philo->mutex_print);
	printf("%ld %d is died\n", get_time() - philo[i].start_time, philo[i].id);
	while (j < philo->philo_count)
	{
		philo[j].stop = 0;
		j++;
	}
}

void	*check_dead(void *arg)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)arg;
	while (philo[i].stop)
	{
		while (i < philo->philo_count)
		{
			if (get_time() - philo[i].last_eat > philo->die_time
				&& philo[i].eat_count != 0)
			{
				handle_dead(philo, i);
				pthread_mutex_unlock(philo->mutex_print);
				if (philo[i].philo_count == 1)
					pthread_mutex_unlock(philo[i].left);
				return (NULL);
			}
			i++;
		}
		// if (philo->stop)
		// 	pthread_mutex_unlock(philo->data_race);
		//return NULL;
		i = 0;
	}
	return (NULL);
}

void	print_simulation(t_philo *philo, char *str)
{
	// if (!philo->stop)
	// 	return ;
	
	pthread_mutex_lock(philo->mutex_print);
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(philo->mutex_print);
	if (str == EAT)
	{
		philo->last_eat = get_time();
		if (philo->eat_count > 0)
			philo->eat_count--;
	}
}

int	deadlock_case(t_philo *philo)
{
	if (!philo->stop)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (0);
	}
	return (1);
}

int	taken_fork(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->philo_count != philo->id)
	{
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(philo->left);
	}
	else
	{
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
	}	
	if (!deadlock_case(philo))
		return (0);
	pthread_mutex_lock(philo->mutex_print);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->start_time, philo->id);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->mutex_print);
	return (1);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		my_usleep(10);
	while (philo->stop)
	{
		if (meal_tracker(philo) == 1 || !philo->stop)
		{
			// pthread_mutex_unlock(philo->mutex_print);
			// printf("TEST0\n");
			return (NULL);
		}
		
		print_simulation(philo, THINK);
	
		if (!philo->stop)
		{
			// printf("TEST1\n");
			// pthread_mutex_unlock(philo->mutex_print);
			return (NULL);
		}
		
		taken_fork(philo);
		
		if (!deadlock_case(philo))
		{
			// pthread_mutex_unlock(philo->mutex_print);
			// printf("TEST2\n");
			return (NULL);
		}
		
		print_simulation(philo, EAT);
	
		my_usleep(philo->eat_time);
	
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	
		if (!philo->stop)
		{		
			// pthread_mutex_unlock(philo->mutex_print);
			// printf("TEST3\n");
			return (NULL);
		}
	
		print_simulation(philo, SLEEP);
		my_usleep(philo->sleep_time);

		if (!philo->stop)
		{		
			// pthread_mutex_unlock(philo->mutex_print);
			// printf("TEST4\n");
			return (NULL);
		}
	}
	return (NULL);
}
