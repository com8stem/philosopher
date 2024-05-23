#include "philo.h"

static int check_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (get_time() - philo->last_meal_time >= philo->table->time_to_die && philo->is_eating == 0)
	{
		pthread_mutex_lock(&philo->table->timing);
		philo->table->end_flag = 1;
		pthread_mutex_unlock(&philo->table->timing);
		print_dead(philo);
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	if (philo->meal_count == philo->table->num_of_must_eat)
	{
		pthread_mutex_lock(&philo->table->timing);
		philo->table->num_of_finish++;
		if (philo->table->num_of_finish == philo->table->num_of_philo)
		{
			philo->table->end_flag = 1;
			pthread_mutex_unlock(&philo->table->timing);
			pthread_mutex_unlock(&philo->lock);
			return (0);
		}
		pthread_mutex_unlock(&philo->table->timing);
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}	
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

static bool	is_dead(t_philo *philo)
{	
	if (check_last_meal(philo) == 0)
		return (true);
	return (false);
}

void	*monitor(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(1)
	{
		if (is_dead(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
