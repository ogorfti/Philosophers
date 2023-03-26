/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:28 by ogorfti           #+#    #+#             */
/*   Updated: 2023/03/26 16:35:50 by ogorfti          ###   ########.fr       */
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
	int				argc;
	char			**argv;
}   				t_philo;



typedef struct s_process{
	
	pthread_mutex_t	mutex_print;
	t_philo			*all_philo;

}   			t_process;


void	initializes_philos(pthread_mutex_t *forks, t_philo *philo, t_process *process);
void	init_forks(pthread_mutex_t *forks, int nbr);
long	get_time(void);
void	my_usleep(int ms);
int		check_args(int ac, char **av);
void	*philosopher(void *arg);
void	*check_dead(void *arg);
void create_philos(pthread_t *id, t_philo *philo, char **av, t_process *process);


#endif