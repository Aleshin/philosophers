/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:11:19 by saleshin          #+#    #+#             */
/*   Updated: 2024/07/14 23:11:32 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	f_time(long long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

void	*philosopher_routine(void *data)
{
	t_philo	*philo;
	t_philo	*next_philo;

	philo = (t_philo *)data;
	if (philo->id == philo->args->number_of_philosophers)
		next_philo = (philo - philo->args->number_of_philosophers + 1);
	else
		next_philo = (philo + 1);
	printf("%lld %d is thinking\n", f_time(philo->args->start_time), philo->id);
	while (1)
	{
		if (check_end(philo))
			return (NULL);
		take_forks(philo, next_philo);
		check_taken_fork(philo);
		if (check_eating(philo, next_philo))
			return (NULL);
		check_sleeping(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		*philosophers;
//	pthread_t	*threads;
//	pthread_t	*thread_monitor;
	t_args		args;
//	int			i;

	if (init_args(argc, argv, &args))
		return (1);
	printf("%d\n", args.number_of_philosophers);
	philosophers = malloc(args.number_of_philosophers * sizeof(t_philo));
	if (philosophers)
		return (1);
	init_philo(&philosophers, &args);
	printf("%d\n", philosophers->args->number_of_philosophers);
/*
	threads = malloc(args->number_of_philosophers * sizeof(pthread_t));
	thread_monitor = malloc(sizeof(pthread_t));
	pthread_create(thread_monitor, NULL, monitor, &philosophers);
	init_threads(philosophers);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		pthread_mutex_destroy(&philosophers[i].mutex_philo);
		i++;
	}
	printf("%d philosophers died\n", args->end);
	pthread_join(*thread_monitor, NULL);
//	pthread_mutex_destroy(&args->mutex_global);
	free(philosophers);
	free(threads);
//	free(thread_monitor);
*/
	return (0);
}
