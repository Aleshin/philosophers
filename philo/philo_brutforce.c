# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	print_status (int philo, int time, char *even, char *odd)
{
	int	i;

	i = 1;
	while (i <= philo)
	{
		if (i % 2 != 0)
		{
			if (even != NULL)
				printf("%d %d %s\n", time, i, even);
		}
		else
		{
			if (odd != NULL)
				printf("%d %d %s\n", time, i, odd);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		time;
	int		eat;
	int		n_eat;
	int 	sleep;
	int 	life;
	int		philosophers;

	philosophers = atoi(argv[1]);
	life = atoi(argv[2]);
	eat = atoi(argv[3]);
	sleep = atoi(argv[4]);
	if (argc == 6)
		n_eat = atoi(argv[5]);
	time = 0;
	if ((eat + sleep > life) || (eat * 2 > life))
	{
		print_status(philosophers, time, "take fork", "thinking");
		print_status(philosophers, time, "is eating", NULL);
		usleep(eat * 1000);
		time = time + eat;
		printf("%d 2 is died\n", time);
		return (0);
	}
	while (n_eat > 0)
	{
		print_status(philosophers, time, "is sleeping", "take fork");
		print_status(philosophers, time, NULL, "is eating");
		if (sleep < eat)
		{
			usleep(sleep * 1000);
			print_status(philosophers, time + sleep, "is thinking", NULL);
			time = time + eat;
			usleep((eat - sleep) * 1000);
			print_status(philosophers, time, NULL, "is sleeping");
			print_status(philosophers, time, "take fork", NULL);
			print_status(philosophers, time, "is eating", NULL);
			print_status(philosophers, time + sleep, NULL, "is thinking");
			time = time + eat;
			usleep(eat * 1000);
		}
		else
		{
			usleep(eat * 1000);
			print_status(philosophers, time + eat, NULL, "is sleeping");
			time = time + sleep;
			usleep((sleep - eat) * 1000);
			print_status(philosophers, time, "is thinking", NULL);
			print_status(philosophers, time, "take fork", NULL);
			print_status(philosophers, time, "is eating", NULL);
			time = time + eat;
			usleep(eat * 1000);
			print_status(philosophers, time, NULL, "is thinking");
		}
		n_eat--;
	}
	return (0);
}
