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
		if (check_dead(philo))
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
	pthread_t	*threads;
	t_args		*args;
	int			i;

	args = malloc(sizeof(t_args));
	if (init_args(argc, argv, args))
	{
		free(args);
		return (1);
	}
	philosophers = malloc(args->number_of_philosophers * sizeof(t_philo));
	init_philo(philosophers, args);
	threads = malloc(args->number_of_philosophers * sizeof(pthread_t));
	init_threads(philosophers, threads, args);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		pthread_mutex_destroy(&philosophers[i].fork_mutex);
		i++;
	}
	printf("%d philosophers died\n", args->end);
	pthread_mutex_destroy(&args->mutex_global);
	free(philosophers);
	free(threads);
	free(args);
	return (0);
}
