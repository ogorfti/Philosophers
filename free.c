/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:54:28 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/06 19:47:37 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(pthread_mutex_t	*forks, int nbr_philo)
{
	int	i;

	i = -1;
	while (++i < nbr_philo)
		pthread_mutex_destroy(&forks[i]);
	free (forks);
}

void	my_free(pthread_mutex_t *forks, t_process *process,
		t_philo *philo, pthread_t *id)
{
	destroy_forks(forks, philo->philo_count);
	free (id);
	free (philo);
	free (process);
}
