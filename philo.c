/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:44 by ogorfti           #+#    #+#             */
/*   Updated: 2023/03/26 22:49:10 by ogorfti          ###   ########.fr       */
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

int	main(int ac, char **av)
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
		//printf("TEST\n");
	}
	else
		printf("Invalid number of arguments!\n");
	return (0);
}
