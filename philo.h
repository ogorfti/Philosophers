/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:28 by ogorfti           #+#    #+#             */
/*   Updated: 2023/02/18 19:29:44 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>



typedef struct s_philo{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				id;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_count;
	int				philo_count;
	long			last_eat;
	long			first_eat;
	int				dead;
}   				t_philo;

#endif