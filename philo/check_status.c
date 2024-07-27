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
	if (philo->args->end > 0)
		return (1);
	if (philo->status != DEAD
		&& f_time(philo->args->start_time) - philo->timer_life
		>= philo->args->time_to_die)
	{
		philo->args->end++;
		philo->status = DEAD;
		printf("%lld %d died\n", f_time(philo->args->start_time), philo->id);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo, t_philo *next_philo)
{
	if (philo->status == THINKING)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&next_philo->fork);
			printf("%lld %d has taken a fork\n",
				f_time(philo->args->start_time), philo->id);
			pthread_mutex_lock(&philo->fork);
			printf("%lld %d has taken a fork\n",
				f_time(philo->args->start_time), philo->id);
		}
		else
		{
			pthread_mutex_lock(&philo->fork);
			printf("%lld %d has taken a fork\n",
				f_time(philo->args->start_time), philo->id);
			pthread_mutex_lock(&next_philo->fork);
			printf("%lld %d has taken a fork\n",
				f_time(philo->args->start_time), philo->id);
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
		philo->timer_current = f_time(philo->args->start_time);
		philo->timer_life = philo->timer_current;
		printf("%lld %d is eating\n", philo->timer_current, philo->id);
	}
	return (0);
}

int	check_eating(t_philo *philo, t_philo *next_philo)
{
	if (philo->status == EATING
		&& (f_time(philo->args->start_time) - philo->timer_current
			>= philo->args->time_to_eat))
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(&next_philo->fork);
		}
		else
		{
			pthread_mutex_unlock(&next_philo->fork);
			pthread_mutex_unlock(&philo->fork);
		}
		philo->status = SLEEPING;
		philo->timer_current = f_time(philo->args->start_time);
		printf("%lld %d is sleeping\n", philo->timer_current, philo->id);
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
		philo->status = THINKING;
		philo->timer_current = f_time(philo->args->start_time);
		printf("%lld %d is thinking\n", philo->timer_current, philo->id);
	}
	return (0);
}
