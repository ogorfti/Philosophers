/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:39:14 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/02 21:11:24 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	my_usleep(int ms, t_philo *philo)
{
	int		is_done;
	long	start;

	start = get_time();
	is_done = philo->stop;
	while (is_done)
	{
		if (get_time() - start >= ms)
			break;
		usleep(100);
		pthread_mutex_lock(philo->mutex_sleep);
		is_done = philo->stop;
		pthread_mutex_unlock(philo->mutex_sleep);
	}
}