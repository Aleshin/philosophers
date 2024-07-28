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

int	init_args(int argc, char **argv, t_args *args)
{
	if (argc != 5 && argc != 6)
	{
		printf("Need arguments:\n"
			"number_of_philosophers\n"
			"time_to_die\n"
			"time_to_eat\n"
			"time_to_sleep\n"
			"<number_of_times_each_philosopher_must_eat>\n");
		return (1);
	}
	args->number_of_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	args->start_time = 0;
	args->start_time = f_time(args->start_time);
	args->number_of_times_each_philosopher_must_eat = 0;
	pthread_mutex_init(&args->mutex_global, NULL);
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	return (0);
}

int	init_philo(t_philo *philosophers, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].status = THINKING;
		philosophers[i].fork = 0;
		philosophers[i].args = args;
		philosophers[i].eat_count = 0;
		pthread_mutex_init(&philosophers[i].fork_mutex, NULL);
		i++;
	}
	return (0);
}

int	init_threads(t_philo *philosophers, pthread_t *threads, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		philosophers[i].timer_life = f_time(args->start_time);
		philosophers[i].timer_current = philosophers[i].timer_life;
		pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
		i++;
	}
	return (0);
}
