#include "philo.h"

int check_last_meal(t_philo *philo)
{
	if (get_time() - philo->table->start_time > philo->table->time_to_die)
	{
		philo->table->end_flag = 1;
		print_dead(philo);
		return (0);
	}
	else
		return (1);
}

int		is_dead(t_table *info)
{
	int i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (check_last_meal(&info->philos[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	*monitor(t_table *info)
{
	while(1)
	{
		pthread_mutex_lock(&info->timing);
		if (is_dead(info) == 1)
		{
			usleep(100);
			pthread_mutex_unlock(&info->timing);
			return (NULL);
		}
		pthread_mutex_unlock(&info->timing);
		usleep(200);
	}
}

void join_threads(t_table *info)
{
	int i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(info->philos[i].thread_id, NULL);
		i++;
	}
}
