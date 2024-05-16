#include "philo.h"

int check_last_meal(t_philo *philo)
{
	if (get_time() - philo->table->start_time > philo->time_to_die)
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
			return (0);
		i++;
	}
	return (1);
}


void	*monitor(t_table *info)
{
	while(1)
	{
		pthread_mutex_lock(&info->timing);
		if (is_dead(info))
		{
			usleep(100);
			return (pthread_mutex_unlock(&info->timing), NULL);
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


int	main(int argc, char **argv)
{
	t_table info;

	if (!check_arg(argc, argv))
		return (printf("argerror\n"));
	init_philo(argv, &info);
	start_dinner(&info);
	join_threads(&info);
	monitor(&info);
	end_dinner(&info);
	return (0);
}
