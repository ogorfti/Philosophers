/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:44 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/06 21:40:15 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_error(pthread_mutex_t	*forks, t_philo *philo,
		pthread_t *id, int nbr_philo)
{
	if (!id)
		return (1);
	if (!forks)
	{
		free (id);
		return (1);
	}
	if (!philo)
	{
		free (id);
		destroy_forks (forks, nbr_philo);
		return (1);
	}
	return (0);
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
			return (0);
		id = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
		forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
		philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
		if (check_error(forks, philo, id, ft_atoi(av[1])))
			return (0);
		init_forks(forks, ft_atoi(av[1]));
		philo->argv = av;
		philo->argc = ac;
		process = malloc(sizeof(t_process));
		initializes_philos(forks, philo, process);
		create_philos(id, philo, av, process);
		my_free(forks, process, philo, id);
	}
	else
		printf("Invalid number of arguments!\n");
	return (0);
}
