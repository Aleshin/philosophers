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

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_global);
	if (philo->args->end > 0)
	{
		pthread_mutex_unlock(&philo->args->mutex_global);
		return (1);
	}
	if (philo->status != DEAD
		&& f_time(philo->args->start_time) - philo->timer_life
			>= philo->args->time_to_die)
	{
		philo->status = DEAD;
		philo->args->end++;
		printf("%lld %d died\n", f_time(philo->args->start_time), philo->id);
		pthread_mutex_unlock(&philo->args->mutex_global);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->mutex_global);
	return (0);
}

int	check_taken_fork(t_philo *philo)
{
	if (philo->status == TAKEN_FORK)
	{
		pthread_mutex_lock(&philo->args->mutex_global);
		philo->status = EATING;
		philo->timer_current = f_time(philo->args->start_time);
		philo->timer_life = philo->timer_current;
		printf("%lld %d is eating\n", philo->timer_current, philo->id);
		pthread_mutex_unlock(&philo->args->mutex_global);
	}
	return (0);
}

int	check_eating(t_philo *philo, t_philo *next_philo)
{
	if (philo->status == EATING
		&& (f_time(philo->args->start_time) - philo->timer_current
			>= philo->args->time_to_eat))
	{
		pthread_mutex_lock(&philo->args->mutex_global);
		philo->status = SLEEPING;
		philo->timer_current = f_time(philo->args->start_time);
		printf("%lld %d is sleeping\n", philo->timer_current, philo->id);
		free_forks(philo, next_philo);
		pthread_mutex_unlock(&philo->args->mutex_global);
		philo->eat_count++;
		if (philo->eat_count
			== philo->args->number_of_times_each_philosopher_must_eat)
			return (1);
	}
	return (0);
}

int	check_sleeping(t_philo *philo)
{
	if (philo->status == SLEEPING
		&& f_time(philo->args->start_time) - philo->timer_current
		>= philo->args->time_to_sleep)
	{
		pthread_mutex_lock(&philo->args->mutex_global);
		philo->status = THINKING;
		philo->timer_current = f_time(philo->args->start_time);
		printf("%lld %d is thinking\n", philo->timer_current, philo->id);
		pthread_mutex_unlock(&philo->args->mutex_global);
	}
	return (0);
}
