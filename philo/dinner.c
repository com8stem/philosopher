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
	// printf("[%d]\n", info->philos[0].id);
	print_thinking(&(info->philos[0]));
	time_sleep(info->time_to_die);
	print_dead(&(info->philos[0]));
	return ;
}

static void many_philo(t_table )
{

}

void	start_dinner(t_table *info)
{
	info->start_time = get_time();
	if (info->num_of_philo == 1)
	{
		_one_philo(info);
		return ;
	}
	many_philo(info);
	return ;
}
