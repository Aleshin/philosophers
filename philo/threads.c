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

void	*philo_routine(void *data)
{
	t_philo	*philo;
	t_philo	*next_philo;

	philo = (t_philo *)data;
	if (philo->id == philo->args->number_of_philosophers)
		next_philo = (philo - philo->args->number_of_philosophers + 1);
	else
		next_philo = (philo + 1);
	pthread_mutex_lock(&philo->args->mutex_global);
	pthread_mutex_unlock(&philo->args->mutex_global);
	if (philo->id % 2 == 0)
		usleep(200);
	printf("%zu %d is thinking\n", f_time(philo->args->start_time), philo->id);
	while (1)
	{
		if (take_forks(philo, next_philo))
			return (NULL);
		if (check_taken_fork(philo))
			return (NULL);
		if (check_eating(philo, next_philo))
			return (NULL);
		if (check_sleeping(philo))
			return (NULL);
		usleep(400);
	}
	return (NULL);
}

void	*monitor(void *data)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)data;
	i = 0;
	pthread_mutex_lock(&philo->args->mutex_global);
	pthread_mutex_unlock(&philo->args->mutex_global);
	while (1)
	{
		pthread_mutex_lock(&philo[0].args->mutex_global);
		if (philo[0].args->philos_finished == philo[0].args->number_of_philosophers)
		{
			philo[0].args->end++;
			pthread_mutex_unlock(&philo[0].args->mutex_global);
			return (NULL);
		}
		pthread_mutex_unlock(&philo[0].args->mutex_global);
		pthread_mutex_lock(&philo[i].timer_mutex);
		if (f_time(philo[0].args->start_time) - philo[i].timer_life
			>= philo[0].args->time_to_die)
		{
			pthread_mutex_lock(&philo[0].args->mutex_global);
			philo[0].args->end++;
//			print_status(philo, "died");
			printf("%zu %d died\n", f_time(philo[0].args->start_time), philo[i].id);
			pthread_mutex_unlock(&philo[0].args->mutex_global);
			pthread_mutex_unlock(&philo[i].timer_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo[i].timer_mutex);
		i = (i + 1) % philo[0].args->number_of_philosophers;
		usleep(200);
	}
	return (NULL);
}
