/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:44 by ogorfti           #+#    #+#             */
/*   Updated: 2023/03/24 22:00:14 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void print_philo(t_philo *philo, char **av)
// {
// 	int i;
// 	i = 0;
// 	while (i < atoi(av[1]))
// 	{
// 		printf("Philosopher #%d:\n", philo[i].id);
// 		printf("Die time: %d\n", philo[i].die_time);
// 		printf("Eat time: %d\n", philo[i].eat_time);
// 		printf("Sleep time: %d\n", philo[i].sleep_time);
// 		printf("Eat count: %d\n", philo[i].eat_count);
// 		printf("Left fork address: %p\n", (void *)philo[i].left);
// 		printf("Right fork address: %p\n", (void *)philo[i].right);
// 		printf("\n");
// 		i++;
// 	}
// }
    
long get_time(void)
{
	struct timeval time;
	long ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void my_usleep(int ms)
{
    long    start;
    //long    time;

	
    start = get_time();
	usleep(ms * 920);
	
    while (get_time() < ms + start)
    {
        // time = get_time() - start;
        usleep(ms * 3);
    }
}

int meal_tracker(t_philo *philo)
{
	int i;

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
		{
			philo[i].stop = 0;
			// printf("TEST : %d\n", philo[i].id);
		}
		i++;
	}
	return (1);
}

void *check_dead(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	int i = 0;
	int j = 0;
	while (philo[i].stop)
	{
		while (i < philo->philo_count)
		{
			if (get_time() - philo[i].last_eat > philo->die_time && philo[i].eat_count != 0)
			{
				//printf("TESTED ***//*** : %d\n", philo[i].eat_count);
				pthread_mutex_lock(philo->mutex_print);
				printf("%ld %d is died\n", get_time() - philo[i].start_time, philo[i].id);
				j = 0;
				while (j < philo->philo_count)
				{
					philo[j].stop = 0;
					j++;
				}
				pthread_mutex_unlock(philo->mutex_print);
				pthread_mutex_unlock(philo[i].left);
				pthread_mutex_unlock(philo[i].right);
				return (NULL);
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}

void *philosopher(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		my_usleep(40);
	while (philo->stop)
	{
		if (meal_tracker(philo) == 1 || !philo->stop)
			return(NULL);	

		pthread_mutex_lock(philo->mutex_print);
		printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex_print);

		if (!philo->stop)
			return (NULL);


		if (philo->id % 2 == 0 && philo->philo_count != philo->id)
		{
			pthread_mutex_lock(philo->right);
			pthread_mutex_lock(philo->left);
		}
		else
		{
			pthread_mutex_lock(philo->left);
			pthread_mutex_lock(philo->right);
		}
		
		if (!philo->stop)
		{
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			return (NULL);
		}
		

		pthread_mutex_lock(philo->mutex_print);
		printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
		printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex_print);

		if (!philo->stop)
		{
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			return (NULL);
		}
		// if (meal_tracker(philo) == 1 || !philo->stop)
		// 	return(NULL);

		pthread_mutex_lock(philo->mutex_print);
		printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex_print);
		philo->last_eat = get_time();
		if (philo->eat_count > 0)
			philo->eat_count--;
			
		my_usleep(philo->eat_time);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		
		if (!philo->stop)
			return (NULL);

		pthread_mutex_lock(philo->mutex_print);
		printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex_print);
		my_usleep(philo->sleep_time);
		
			
		if (!philo->stop)
			return (NULL);
	}
	return (NULL);
}

void create_philos(pthread_t *id, t_philo *philo, char **av, t_process *process)
{
	pthread_t dead_id;
	int nbr_philo;
	int i;

	i = 0;
	nbr_philo = atoi(av[1]);
	while (i < nbr_philo)
	{
		if (pthread_create(&id[i], NULL, &philosopher, &philo[i]) != 0)
		{
			printf("Failed to creat thread\n");
			return;
		}
		i++;
	}
	pthread_create(&dead_id, NULL, check_dead, (void *)process->all_philo);
	pthread_join(dead_id, NULL);
	i = 0;
	while (i < nbr_philo)
	{
		if (pthread_join(id[i], NULL) != 0)
		{
			printf("Failed to join thread\n");
			return;
		}
		i++;
	}
}

void init_forks(pthread_mutex_t *forks, int nbr)
{
	int i;

	i = 0;
	while (i < nbr)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void initializes_philos(int ac, char **av, pthread_mutex_t *forks,
						t_philo *philo, t_process *process)
{
	int i;
	long first;

	first = get_time();
	i = 0;
	pthread_mutex_init(&process->mutex_print, NULL);
	while (i < atoi(av[1]))
	{
		philo[i].start_time = first;
		philo[i].last_eat = first;
		philo[i].die_time = atoi(av[2]);
		philo[i].eat_time = atoi(av[3]);
		philo[i].sleep_time = atoi(av[4]);
		if (ac == 6)
			philo[i].eat_count = atoi(av[5]);
		else
			philo[i].eat_count = -1;
		philo[i].left = &forks[i];
		philo[i].right = &forks[(i + 1) % atoi(av[1])];
		philo[i].id = i + 1;
		philo[i].dead = 1;
		philo[i].stop = 1;
		philo[i].mutex_print = &process->mutex_print;
		philo[i].philo_count = atoi(av[1]);
		i++;
	}
	process->all_philo = philo;
}

int check_args(int ac, char **av)
{
	if (atoi(av[2]) < 0 || atoi(av[3]) < 0 || atoi(av[4]) < 0)
		return 1;
	if (ac == 6)
	{
		if (atoi(av[5]) < 0)
			return 1;
	}
	return (0);
}

int main(int ac, char **av)
{
	pthread_mutex_t *forks;
	pthread_t *id;
	t_philo *philo;
	t_process *process = malloc(sizeof(t_process));

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
		initializes_philos(ac, av, forks, philo, process);

		create_philos(id, philo, av, process);
		// print_philo(philo, av);
	}
	else
		printf("Invalid number of arguments!\n");

	return (0);
}
