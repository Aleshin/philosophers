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

int	init_timer(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_global);
	pthread_mutex_unlock(&philo->args->mutex_global);
	printf("-----------------%d start at %zu\n", philo->id, f_time(0));//philo->args->start_time));
	pthread_mutex_lock(&philo->timer_mutex);
	philo->timer_life = f_time(philo->args->start_time);
	philo->timer_current = philo->timer_life;
	pthread_mutex_unlock(&philo->timer_mutex);
	return (0);
}

int	check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_global);
	if (philo->args->end > 0)
	{
		pthread_mutex_unlock(&philo[0].args->mutex_global);
		return (1);
	}
	pthread_mutex_unlock(&philo[0].args->mutex_global);
	return (0);
}

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
//	printf("-----------------%d start at %zu\n", philo->id, f_time(0));//philo->args->start_time));
	pthread_mutex_lock(&philo->timer_mutex);
	philo->timer_life = f_time(philo->args->start_time);
	philo->timer_current = philo->timer_life;
	pthread_mutex_unlock(&philo->timer_mutex);

//	init_timer(philo);
//	return (NULL);
	if (philo->id % 2 == 0 || philo->id == philo->args->number_of_philosophers)
		usleep(100);
	while (1)
	{
		if (check_end(philo))
			break ;
		take_forks(philo, next_philo);
		check_taken_fork(philo);
		check_eating(philo, next_philo);
		check_sleeping(philo);
//		usleep(200);
	}
	free_forks(philo, next_philo);
	return (NULL);
}

int	check_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].timer_mutex);
	if (f_time(philo[0].args->start_time) - philo[i].timer_life
		>= philo[0].args->time_to_die)
	{
		print_status(philo, "died");
		pthread_mutex_unlock(&philo[i].timer_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo[i].timer_mutex);
	return (0);
}

void	*monitor(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo[0].args->mutex_global);
		if (philo[0].args->philos_finished
			== philo[0].args->number_of_philosophers)
		{
			pthread_mutex_unlock(&philo[0].args->mutex_global);
			break ;
		}
		pthread_mutex_unlock(&philo[0].args->mutex_global);
		if (check_dead(philo, i))
			break ;
//		usleep(100);
		i = (i + 1) % philo->args->number_of_philosophers;
	}
	pthread_mutex_lock(&philo[0].args->mutex_global);
	philo[0].args->end++;
	pthread_mutex_unlock(&philo[0].args->mutex_global);
	return (NULL);
}
