/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:33:44 by ogorfti           #+#    #+#             */
/*   Updated: 2023/03/26 16:34:51 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(pthread_mutex_t *forks, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	initializes_philos(pthread_mutex_t *forks, t_philo *philo, t_process *process)
{
	long	first;
	int		i;

	first = get_time();
	i = 0;
	pthread_mutex_init(&process->mutex_print, NULL);
	while (i < atoi(philo->argv[1]))
	{
		philo[i].start_time = first;
		philo[i].last_eat = first;
		philo[i].die_time = atoi(philo->argv[2]);
		philo[i].eat_time = atoi(philo->argv[3]);
		philo[i].sleep_time = atoi(philo->argv[4]);
		if (philo->argc == 6)
			philo[i].eat_count = atoi(philo->argv[5]);
		else
			philo[i].eat_count = -1;
		philo[i].left = &forks[i];
		philo[i].right = &forks[(i + 1) % atoi(philo->argv[1])];
		philo[i].id = i + 1;
		philo[i].dead = 1;
		philo[i].stop = 1;
		philo[i].mutex_print = &process->mutex_print;
		philo[i].philo_count = atoi(philo->argv[1]);
		i++;
	}
	process->all_philo = philo;
}

void	ft_join(pthread_t *id, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_join(id[i], NULL) != 0)
		{
			printf("Failed to join thread\n");
			return ;
		}
		i++;
	}
}

void	create_philos(pthread_t *id, t_philo *philo,
		char **av, t_process *process)
{
	pthread_t	dead_id;
	int			nbr_philo;
	int			i;

	i = 0;
	nbr_philo = atoi(av[1]);
	while (i < philo->philo_count)
	{
		if (pthread_create(&id[i], NULL, &philosopher, &philo[i]) != 0)
		{
			printf("Failed to creat thread\n");
			return ;
		}
		i++;
	}
	pthread_create(&dead_id, NULL, check_dead, (void *)process->all_philo);
	pthread_join(dead_id, NULL);
	ft_join(id, philo->philo_count);
}
