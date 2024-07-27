/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:14:49 by saleshin          #+#    #+#             */
/*   Updated: 2024/07/14 23:15:01 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum e_status
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct args
{
	int				number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	int				number_of_times_each_philosopher_must_eat;
	int				end;
	pthread_mutex_t	mutex_global;
}	t_args;

typedef struct philo
{
	int				id;
	pthread_mutex_t	fork;
	long long		timer_life;
	long long		timer_current;
	int				status;
	int				eat_count;
	t_args			*args;
}	t_philo;

long long	f_time(long long start_time);
int			init_args(int argc, char **argv, t_args *args);
int			init_philo(t_philo *philosophers, t_args *args);
int			init_threads(t_philo *philosophers,
				pthread_t *threads, t_args *args);
int			take_forks(t_philo *philo, t_philo *next_philo);
int			check_dead(t_philo *philo);
int			check_taken_fork(t_philo *philo);
int			check_eating(t_philo *philo, t_philo *next_philo);
int			check_sleeping(t_philo *philo);
void		*philosopher_routine(void *data);

#endif
