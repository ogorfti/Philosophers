/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:54:28 by ogorfti           #+#    #+#             */
/*   Updated: 2023/04/01 23:15:39 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void   destroy_forks(pthread_mutex_t	*forks, int nbr_philo)
{
    int i;

    i = -1;
    while (++i < nbr_philo)
        pthread_mutex_destroy(&forks[i]);
    free (forks);
}