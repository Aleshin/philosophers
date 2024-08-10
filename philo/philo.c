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
	int			f;

	args = malloc(sizeof(t_args));
	if (init_args(argc, argv, args) || one_philo(args))
	{
		free(args);
		return (1);
	}
	philosophers = malloc(args->number_of_philosophers * sizeof(t_philo));
	init_philo(philosophers, args);
	f = init_threads(philosophers, args);
	if (f != -1)
	{
		pthread_mutex_lock(&philosophers->args->mutex_global);
		args->end++;
		pthread_mutex_unlock(&philosophers->args->mutex_global);
		finish_threads(philosophers, args, f);
		return (0);
	}
	if (!pthread_create(&args->thread_monitor, NULL, monitor, &philosophers[0]))
		pthread_join(args->thread_monitor, NULL);
	finish_threads(philosophers, args, args->number_of_philosophers);
	return (0);
}
