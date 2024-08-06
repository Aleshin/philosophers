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

	args = malloc(sizeof(t_args));
	if (init_args(argc, argv, args) || one_philo(args))
	{
		free(args);
		return (1);
	}
	philosophers = malloc(args->number_of_philosophers * sizeof(t_philo));
	init_philo(philosophers, args);
	init_threads(philosophers, args);
	finish_threads(philosophers, args);
	return (0);
}
