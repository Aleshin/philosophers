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

int	take_forks_even(t_philo *philo, t_philo *next_philo)
{
	pthread_mutex_lock(&next_philo->mutex);
	if (next_philo->fork == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->fork == 0)
		{
			philo->fork = philo->id;
			next_philo->fork = philo->id;
			philo->status = TAKEN_FORK;
			printf("%lld %d has taken a fork\n",
				f_time(philo->args->start_time), philo->id);
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	pthread_mutex_unlock(&next_philo->mutex);
	return (0);
}

int	take_forks_odd(t_philo *philo, t_philo *next_philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->fork == 0)
	{
		pthread_mutex_lock(&next_philo->mutex);
		if (next_philo->fork == 0)
		{
			philo->fork = philo->id;
			next_philo->fork = philo->id;
			philo->status = TAKEN_FORK;
			printf("%lld %d has taken a fork\n",
				f_time(philo->args->start_time), philo->id);
		}
		pthread_mutex_unlock(&next_philo->mutex);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (0);
}

int	take_forks(t_philo *philo, t_philo *next_philo)
{
	pthread_mutex_lock(&philo->args->mutex_global);
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
	pthread_mutex_unlock(&philo->args->mutex_global);
/*
	if (philo->id % 2 == 0)
		take_forks_even(philo, next_philo);
	else
		take_forks_odd(philo, next_philo);
*/
	return (0);
}

int	free_forks(t_philo *philo, t_philo *next_philo)
{
//	pthread_mutex_lock(&philo->args->mutex_global);
	philo->fork = 0;
	next_philo->fork = 0;
//	pthread_mutex_unlock(&philo->args->mutex_global);
/*
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&next_philo->mutex);
		next_philo->fork = 0;
		pthread_mutex_unlock(&next_philo->mutex);
		pthread_mutex_lock(&philo->mutex);
		philo->fork = 0;
		pthread_mutex_unlock(&philo->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->mutex);
		philo->fork = 0;
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_lock(&next_philo->mutex);
		next_philo->fork = 0;
		pthread_mutex_unlock(&next_philo->mutex);
	}
*/
	return (0);
}
