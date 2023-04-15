/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:44 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/14 21:29:37 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_error(t_process *process, int nbr_philo)
{
	process->id = malloc(sizeof(pthread_t) * nbr_philo);
	if (!process->id)
		return (1);
	process->forks = malloc(sizeof(pthread_mutex_t) * nbr_philo);
	if (!process->forks)
	{
		free (process->id);
		return (1);
	}
	process->philo = malloc(sizeof(t_philo) * nbr_philo);
	if (!process->philo)
	{
		free (process->id);
		destroy_forks (process->forks, nbr_philo);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_process		*process;

	if (ac == 5 || ac == 6)
	{
		if (check_args(ac, av) == 1)
			return (0);
		process = malloc(sizeof(t_process));
		if (!process)
			return (1);
		if (check_error(process, ft_atoi(av[1])))
			return (1);
		if (init_forks(process, ft_atoi(av[1])))
		{
			my_free(process->forks, process, process->philo, process->id);
			return (1);
		}
		process->philo->argv = av;
		process->philo->argc = ac;
		initializes_philos(process->forks, process->philo, process);
		create_philos(process->id, process->philo, av, process);
		my_free(process->forks, process, process->philo, process->id);
	}
	else
		printf("Invalid number of arguments!\n");
	return (0);
}
