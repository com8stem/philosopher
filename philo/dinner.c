#include "philo.h"

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
		pthread_create(&info->philos[i].thread_id, NULL, &philo_routine,
			(void *)&info->philos[i]);
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
		pthread_mutex_destroy(&info->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&info->timing);
	pthread_mutex_destroy(&info->write);
}
