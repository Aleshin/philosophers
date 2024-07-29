/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:57:43 by saleshin          #+#    #+#             */
/*   Updated: 2024/07/29 17:57:52 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*monitor(void *data)
{
	t_philo		*philo;
	int			i;
	long long	time_to_die;

	philo = (t_philo *)data;
	i = 0;
	time_to_die = philo->args->time_to_die;
	while (1)
	{
		if (f_time(philo->args->start_time) - philo[i].timer_life > time_to_die)
		{
//			pthread_mutex_lock(&philo->args->mutex_global);
			philo->args->end++;
//			pthread_mutex_unlock(&philo->args->mutex_global);
			printf("%lld %d died\n", f_time(philo->args->start_time), philo[i].id);
			return (NULL);
		}
		i = (i + 1) % philo->args->number_of_philosophers;
	}
	return (NULL);
}
