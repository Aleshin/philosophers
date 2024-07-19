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
		pthread_mutex_lock(&philo->args->mutex_global);
		if (philo->args->end == 1)
		{
			pthread_mutex_unlock(&philo->args->mutex_global);
			return (NULL);
		}
		if (f_time(philo->args->start_time) - philo->timer_life
			>= philo->args->time_to_die)
		{
			philo->status = DEAD;
			philo->args->end = 1;
			printf("%lld %d died\n", f_time(philo->args->start_time), philo->id);
			pthread_mutex_unlock(&philo->args->mutex_global);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->mutex_global);
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&next_philo->mutex);
		if (philo->status == EATING
			&& (f_time(philo->args->start_time) - philo->timer_current
				>= philo->args->time_to_eat))
		{
			philo->status = SLEEPING;
			philo->timer_current = f_time(philo->args->start_time);
			philo->fork = 0;
			next_philo->fork = 0;
			philo->eat_count++;
			if (philo->eat_count
				== philo->args->number_of_times_each_philosopher_must_eat)
			{
				return (NULL);
			}
			printf("%lld %d is sleeping\n", philo->timer_current, philo->id);
		}
		pthread_mutex_unlock(&next_philo->mutex);
		pthread_mutex_unlock(&philo->mutex);
		if (philo->status == SLEEPING
			&& f_time(philo->args->start_time) - philo->timer_current
			>= philo->args->time_to_sleep)
		{
			philo->status = THINKING;
			philo->timer_current = f_time(philo->args->start_time);
			printf("%lld %d is thinking\n", philo->timer_current, philo->id);
		}
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&next_philo->mutex);
		if (philo->status == THINKING)
		{
			if (philo->fork == 0 && next_philo->fork == 0)
			{
				philo->fork = philo->id;
				next_philo->fork = philo->id;
				philo->status = TAKEN_FORK;
				printf("%lld %d has taken a fork\n",
					f_time(philo->args->start_time), philo->id);
			}
		}
		pthread_mutex_unlock(&next_philo->mutex);
		pthread_mutex_unlock(&philo->mutex);
		if (philo->status == TAKEN_FORK)
		{
			philo->status = EATING;
			philo->timer_current = f_time(philo->args->start_time);
			philo->timer_life = philo->timer_current;
			printf("%lld %d is eating\n", philo->timer_current, philo->id);
		}
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
	if (argc != 5 && argc != 6)
	{
		printf("Need arguments:\n"
			"number_of_philosophers\n"
			"time_to_die\n"
			"time_to_eat\n"
			"time_to_sleep\n"
			"<number_of_times_each_philosopher_must_eat>\n");
		free(args);
		return (1);
	}
	args->number_of_philosophers = atoi(argv[1]);
	philosophers = malloc(args->number_of_philosophers * sizeof(t_philo));
	threads = malloc(args->number_of_philosophers * sizeof(pthread_t));
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	args->start_time = 0;
	args->start_time = f_time(args->start_time);
	args->number_of_times_each_philosopher_must_eat = 0;
	pthread_mutex_init(&args->mutex_global, NULL);
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_init(&philosophers[i].mutex, NULL);
		philosophers[i].id = i + 1;
		philosophers[i].timer_life
			= f_time(args->start_time);
		philosophers[i].timer_current = philosophers[i].timer_life;
		philosophers[i].status = THINKING;
		philosophers[i].fork = i + 1;
		philosophers[i].args = args;
		pthread_create(&threads[i], NULL, philosopher_routine,
			&philosophers[i]);
		i++;
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		pthread_mutex_destroy(&philosophers[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&args->mutex_global);
	free(philosophers);
	free(threads);
	free(args);
	return (0);
}
