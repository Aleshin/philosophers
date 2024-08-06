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

int	take_forks(t_philo *philo, t_philo *next_philo)
{
	if (philo->status == THINKING)
	{
		if (philo->id % 2 != 0)
		{
			pthread_mutex_lock(&next_philo->fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(&philo->fork);
			print_status(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&philo->fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(&next_philo->fork);
			print_status(philo, "has taken a fork");
		}
		philo->status = TAKEN_FORK;
	}
	return (0);
}

int	check_taken_fork(t_philo *philo)
{
	if (philo->status == TAKEN_FORK)
	{
		philo->status = EATING;
		pthread_mutex_lock(&philo->timer_mutex);
		philo->timer_current = f_time(philo->args->start_time);
		philo->timer_life = philo->timer_current;
		pthread_mutex_unlock(&philo->timer_mutex);
		print_status(philo, "is eating");
	}
	return (0);
}

int	free_forks(t_philo *philo, t_philo *next_philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&next_philo->fork);
	}
	else
	{
		pthread_mutex_unlock(&next_philo->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	return (0);
}

int	check_eating(t_philo *philo, t_philo *next_philo)
{
	if (philo->status == EATING
		&& (f_time(philo->args->start_time) - philo->timer_current
			>= philo->args->time_to_eat))
	{
		free_forks(philo, next_philo);
		philo->status = SLEEPING;
		philo->timer_current = f_time(philo->args->start_time);
		print_status(philo, "is sleeping");
		philo->eat_count++;
		pthread_mutex_lock(&philo->args->mutex_global);
		if (philo->eat_count
			== philo->args->number_of_times_each_philosopher_must_eat)
			philo->args->philos_finished++;
		pthread_mutex_unlock(&philo->args->mutex_global);
	}
	return (0);
}

int	check_sleeping(t_philo *philo)
{
	if (philo->status == SLEEPING
		&& f_time(philo->args->start_time) - philo->timer_current
		>= philo->args->time_to_sleep)
	{
		philo->status = THINKING;
		philo->timer_current = f_time(philo->args->start_time);
		print_status(philo, "is thinking");
	}
	return (0);
}
