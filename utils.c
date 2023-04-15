/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:39:14 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/14 18:09:46 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	j;

	j = 0;
	while (s1[j] == s2[j] && s2[j] && s1[j])
		j++;
	return (s1[j] - s2[j]);
}

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

int	check_time(t_philo *philo)
{
	if (philo->eat_time > philo->die_time
		|| philo->sleep_time > philo->die_time)
		return (1);
	return (0);
}

void	my_usleep(int ms, t_philo *philo)
{
	int		is_done;
	long	start;

	start = get_time();
	is_done = 1;
	while (is_done)
	{
		if (get_time() - start >= ms || !is_done)
			break ;
		usleep(100);
		pthread_mutex_lock(philo->mutex_sleep);
		is_done = philo->stop;
		pthread_mutex_unlock(philo->mutex_sleep);
	}
}
