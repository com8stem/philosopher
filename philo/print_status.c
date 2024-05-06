#include "philo.h"


void print_eating(t_philo *philo)
{
	printf("%ld %d is eating\n",
		get_time() - philo->table->start_time, philo->id);
}

void print_sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n",
		get_time() - philo->table->start_time, philo->id);
}

void print_thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n",
		get_time() - philo->table->start_time, philo->id);
}

void print_dead(t_philo *philo)
{
	printf("%ld %d died\n",
		get_time() - philo->table->start_time, philo->id);
}

void print_forks(t_philo *philo)
{
	printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->id);
}