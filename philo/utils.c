/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:11:19 by saleshin          #+#    #+#             */
/*   Updated: 2024/07/14 23:11:32 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	f_time(size_t start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

//returns 0 if number is 0, negative or not number
unsigned	int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	if (*str == '-')
		return (0);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (0);
	return (res);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == 0)
		{
			printf("Wrong arg \"%s\". Need positive int\n", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->args->mutex_global);
	if (philo->args->end > 0)
	{
		pthread_mutex_unlock(&philo->args->mutex_global);
		return (1);
	}
	printf("%zu %d %s\n", f_time(philo->args->start_time), philo->id, status);
	pthread_mutex_unlock(&philo->args->mutex_global);
	return (0);
}

int	thread_errors(t_philo *philo, t_args *args, int f)
{
	if (f != -1)
	{
		pthread_mutex_lock(&philo->args->mutex_global);
		printf ("Threads creating error\n");
		args->end++;
		pthread_mutex_unlock(&philo->args->mutex_global);
		finish_threads(philo, args, f);
		return (0);
	}
	if (pthread_create(&args->thread_monitor, NULL, monitor, &philo[0]))
	{
		pthread_mutex_lock(&philo->args->mutex_global);
		printf ("Monitor creating error\n");
		args->end++;
		pthread_mutex_unlock(&philo->args->mutex_global);
		finish_threads(philo, args, args->number_of_philosophers);
		return (0);
	}
	pthread_join(args->thread_monitor, NULL);
	return (1);
}
