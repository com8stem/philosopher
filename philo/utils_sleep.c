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


bool	should_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->timing);
	if (philo->table->end_flag == 1)
	{
		pthread_mutex_unlock(&philo->table->timing);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->timing);
	return (1);
}

void	get_sleep(t_philo *philo)
{
	print_sleeping(philo);
	time_sleep(philo->table->time_to_sleep);
}
