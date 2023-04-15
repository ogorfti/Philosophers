/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:33:44 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/14 21:27:37 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if your program terminates due to an error, all threads will be terminated,
// including those that were successfully created before the error occurred.

int	init_forks(t_process *process, int nbr)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&process->mutex_print, NULL)
		|| pthread_mutex_init(&process->data_race, NULL)
		|| pthread_mutex_init(&process->mutex_sleep, NULL))
	{
		printf("Failed to init mutex\n");
		return (1);
	}
	while (++i < nbr)
	{
		if (pthread_mutex_init(&process->forks[i], NULL) != 0)
		{
			printf("Failed to init mutex\n");
			return (1);
		}
	}
	return (0);
}

void	init_arguments(t_philo *philo, int *i)
{
	philo[*i].die_time = ft_atoi(philo->argv[2]);
	philo[*i].eat_time = ft_atoi(philo->argv[3]);
	philo[*i].sleep_time = ft_atoi(philo->argv[4]);
	if (philo->argc == 6)
		philo[*i].eat_count = ft_atoi(philo->argv[5]) + 1;
	else
		philo[*i].eat_count = -1;
}

void	initializes_philos(pthread_mutex_t *forks, t_philo *philo,
		t_process *process)
{
	long	first;
	int		i;

	first = get_time();
	i = 0;
	while (i < ft_atoi(philo->argv[1]))
	{
		philo[i].start_time = first;
		philo[i].last_eat = first;
		init_arguments(philo, &i);
		philo[i].left = &forks[i];
		philo[i].right = &forks[(i + 1) % ft_atoi(philo->argv[1])];
		philo[i].id = i + 1;
		philo[i].stop = 1;
		philo[i].mutex_print = &process->mutex_print;
		philo[i].mutex_sleep = &process->mutex_sleep;
		philo[i].data_race = &process->data_race;
		philo[i].philo_count = ft_atoi(philo->argv[1]);
		i++;
	}
	process->all_philo = philo;
}

void	ft_join(pthread_t *id, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_join(id[i], NULL) != 0)
		{
			printf("Failed to join thread\n");
			return ;
		}
	}
}

void	create_philos(pthread_t *id, t_philo *philo,
		char **av, t_process *process)
{
	pthread_t	dead_id;
	int			i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_create(&id[i], NULL, &philosopher, &philo[i]) != 0)
		{
			printf("Failed to creat thread\n");
			return ;
		}
		i++;
	}
	if (pthread_create(&dead_id, NULL, check_dead,
			(void *)process->all_philo) != 0)
	{
		printf("Failed to creat thread\n");
		return ;
	}
	ft_join(id, ft_atoi(av[1]));
	if (pthread_join(dead_id, NULL) != 0)
	{
		printf("Failed to join thread\n");
		return ;
	}
}
