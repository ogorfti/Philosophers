/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:44 by ogorfti           #+#    #+#             */
/*   Updated: 2023/03/26 16:36:04 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		i = 0;
	}
	return (NULL);
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
			return(NULL);	

		pthread_mutex_lock(philo->mutex_print);
		printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex_print);

		if (!philo->stop)
			return (NULL);


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
		
		if (!philo->stop)
		{
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			return (NULL);
		}
		

		pthread_mutex_lock(philo->mutex_print);
		printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
		printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex_print);

		if (!philo->stop)
		{
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			return (NULL);
		}

		pthread_mutex_lock(philo->mutex_print);
		printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex_print);
		philo->last_eat = get_time();
		if (philo->eat_count > 0)
			philo->eat_count--;
			
		my_usleep(philo->eat_time);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		
		if (!philo->stop)
			return (NULL);

		pthread_mutex_lock(philo->mutex_print);
		printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex_print);
		my_usleep(philo->sleep_time);
		
			
		if (!philo->stop)
			return (NULL);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	pthread_mutex_t	*forks;
	t_process		*process;
	t_philo			*philo;
	pthread_t		*id;
	
	if (ac == 5 || ac == 6)
	{
		if (check_args(ac, av) == 1)
		{
			printf("Error\n");
			return (0);
		}
		id = malloc(sizeof(pthread_t) * atoi(av[1]));
		forks = malloc(sizeof(pthread_mutex_t) * atoi(av[1]));
		init_forks(forks, atoi(av[1]));
		philo = malloc(sizeof(t_philo) * atoi(av[1]));
		philo->argv = av;
		philo->argc = ac;
		process = malloc(sizeof(t_process));
		initializes_philos(forks, philo, process);
		create_philos(id, philo, av, process);
		}
	else
		printf("Invalid number of arguments!\n");
	//printf("Ho!👋🏻\n");
	return (0);
}
