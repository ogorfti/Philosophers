/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:44 by ogorfti           #+#    #+#             */
/*   Updated: 2023/02/16 18:42:33 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int count = 0;
pthread_mutex_t mutex;

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *myThreadFun()
{
	int i = 0;
	while (i++ < 1000000)
	{
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_lock(&mutex);
	}
    //(void)vargp;
	//printf("%s\n", (char *)vargp);
	return NULL;
}

int main()
{
	pthread_t t1,t2;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, myThreadFun, NULL);
	pthread_create(&t2, NULL, myThreadFun, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf ("count : %d\n", count);
	exit(0); 
	pthread_mutex_destroy(&mutex);
}
