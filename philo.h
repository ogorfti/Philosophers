/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:28 by ogorfti           #+#    #+#             */
/*   Updated: 2023/03/24 01:18:54 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo{
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	int				id;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_count;
	int				philo_count;
	long			last_eat;
	long			start_time;
	int				dead;
	int				stop;
}   				t_philo;



typedef struct s_process{
	
	pthread_mutex_t	mutex_print;
	t_philo			*all_philo;

}   			t_process;

#endif