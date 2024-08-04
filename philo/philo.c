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

int	main(int argc, char **argv)
{
	t_philo		*philosophers;
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
	init_threads(philosophers, args);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_join(philosophers[i].thread_philo, NULL);
		pthread_mutex_destroy(&philosophers[i].fork);
		pthread_mutex_destroy(&philosophers[i].timer_mutex);
		i++;
	}
	pthread_join(args->thread_monitor, NULL);
	printf("%d philosophers died\n", args->end);
	pthread_mutex_destroy(&args->mutex_global);
	free(philosophers);
	free(args);
	return (0);
}
