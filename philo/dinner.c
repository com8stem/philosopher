#include "philo.h"

void	time_sleep(int time)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time)
		usleep(150);
	return ;
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static void	_one_philo(t_table *info)
{
	print_thinking(&(info->philos[0]));
	time_sleep(info->time_to_die);
	print_dead(&(info->philos[0]));
	return ;
}

void	start_dinner(t_table *info)
{
	int		i;

	info->start_time = get_time();
	i = 0;
	if (info->num_of_philo == 1)
	{
		_one_philo(info);
		return ;
	}
	while (i < info->num_of_philo)
	{
		pthread_create(&info->philos[i].thread_id, NULL, &life_of_philo,
			(void *)&info->philos[i]);
		i++;
	}
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(info->philos[i].thread_id, NULL);
		i++;
	}
}

void	end_dinner(t_table *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	// pthread_mutex_destroy(&info->death);
	// pthread_mutex_destroy(&info->eat);
	pthread_mutex_destroy(&info->timing);
	return ;
}
