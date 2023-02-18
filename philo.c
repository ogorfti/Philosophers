/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:44 by ogorfti           #+#    #+#             */
/*   Updated: 2023/02/18 21:53:28 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <sys/time.h>

void print_philo(t_philo *philo, char **av)
{
    int i;

    i = 0;
    while (i < atoi(av[1]))
    {
        printf("Philosopher #%d:\n", philo[i].id);
        printf("Die time: %d\n", philo[i].die_time);
        printf("Eat time: %d\n", philo[i].eat_time);
        printf("Sleep time: %d\n", philo[i].sleep_time);
        printf("Eat count: %d\n", philo[i].eat_count);
        printf("Left fork address: %p\n", (void *) philo[i].left);
        printf("Right fork address: %p\n", (void *) philo[i].right);
        printf("\n");
        i++;
    }
}

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

int	check_dead(long last_eat, int die_time)
{
	long long curr_time = get_time();
	if ((curr_time - last_eat) > die_time)
		return (1);
	return (0);
}
void	*philosopher(void *arg)
{
	t_philo	*philo;
	long	start_eat;

	philo = (t_philo *)arg;
	while (!philo->dead)
	{
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
		printf("%ld %d has taken a fork\n", get_time() - philo->first_eat, philo->id);	
		printf("%ld %d has taken a fork\n", get_time() - philo->first_eat, philo->id);

		philo->last_eat = get_time();
		start_eat = philo->last_eat;
		printf("%ld %d is eating\n", get_time() - philo->first_eat, philo->id);
		usleep(philo->eat_time * 1000);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		
		printf("%ld %d is sleeping\n", get_time() - philo->first_eat, philo->id);
		usleep(philo->sleep_time * 1000);
		printf("%ld %d is thinking\n", get_time() - philo->first_eat, philo->id);
		if (philo->eat_count > 0)
		{
			philo->eat_count--;
			if (philo->eat_count == 0)
			{
				return (NULL);
			}
		}
		if (check_dead(philo->last_eat, philo->die_time) == 1)
		{
			philo->dead = 1;
			printf("%ld %d died\n", get_time() - philo->first_eat, philo->id);
			return (NULL);
		}
	}
	return (NULL);
}

void	create_philos(pthread_t *id, t_philo *philo, char **av)
{
	int	nbr_philo;
	int	i;

	i = 0;
	nbr_philo = atoi(av[1]);
	while (i < nbr_philo)
	{
		if (pthread_create(&id[i], NULL, &philosopher, &philo[i]) != 0)
		{
			printf("Failed to creat thread\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < nbr_philo)
	{
		if (pthread_join(id[i], NULL) != 0)
		{
			printf("Failed to join thread\n");
			return ;
		}
		i++;
	}
}

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

void	initializes_philos(int ac, char **av, pthread_mutex_t *forks, t_philo	*philo)
{
	int	i;
	long first;
	first = get_time();
	i = 0;
	while (i < atoi(av[1]))
	{
		philo[i].first_eat = first;
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
		philo[i].dead = 0;
		philo[i].philo_count = atoi(av[1]);
		i++;
	}	
}

int main(int ac, char **av) 
{
	pthread_mutex_t	*forks;
	pthread_t		*id;
	t_philo			*philo;

	if (ac == 5 || ac == 6)
	{
		id = malloc(sizeof(pthread_t) * atoi(av[1]));
		forks = malloc(sizeof(pthread_mutex_t) * atoi(av[1]));
		init_forks (forks, atoi(av[1]));
		philo = malloc(sizeof(t_philo) * atoi(av[1]));
		initializes_philos(ac, av, forks, philo);	
	
		create_philos(id, philo, av);
		//print_philo(philo, av);
	}
	else
		printf("Invalid number of arguments!\n");
	
	return (0);
}
