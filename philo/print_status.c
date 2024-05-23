#include "philo.h"


void print_eating(t_philo *philo)
{
	if (should_continue(philo))
	{
		pthread_mutex_lock(&philo->table->write);
		printf("%ld %d is eating\n",
			get_time() - philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->write);
	}
}

void print_sleeping(t_philo *philo)
{
	if (should_continue(philo))
	{
		pthread_mutex_lock(&philo->table->write);
		printf("%ld %d is sleeping\n",
			get_time() - philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->write);
	}
}

void print_thinking(t_philo *philo)
{
	if (should_continue(philo))
	{
		pthread_mutex_lock(&philo->table->write);
		printf("%ld %d is thinking\n",
			get_time() - philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->write);
	}
}

void print_dead(t_philo *philo)
{
	static int i = 0;
	
	pthread_mutex_lock(&philo->table->write);
	if (i == 0)
	{
		printf("%ld %d died\n",
			get_time() - philo->table->start_time, philo->id);
		i++;
	}
	pthread_mutex_unlock(&philo->table->write);
}

void print_forks(t_philo *philo)
{
	if (should_continue(philo))
	{
		pthread_mutex_lock(&philo->table->write);
		printf("%ld %d has taken a fork\n",
			get_time() - philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->write);
	}
}