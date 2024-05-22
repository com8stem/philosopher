#include "philo.h"

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (should_continue(philo) == 1)
		print_forks(philo);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (pthread_mutex_unlock(philo->right_fork), 1);
		if (should_continue(philo) == 1)
			print_forks(philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (pthread_mutex_unlock(philo->left_fork), 1);
		if (should_continue(philo) == 1)
			print_forks(philo);
	}
	return (0);
}

void	eating(t_philo *philo)
{
	print_eating(philo);
	pthread_mutex_lock(&philo->table->timing);
	philo->last_meal_time = get_time() - philo->table->start_time;
	philo->time_to_die = philo->last_meal_time + philo->table->time_to_die;
	pthread_mutex_unlock(&philo->table->timing);
	time_sleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->timing);
	if (philo->meal_count != -1)
		philo->meal_count++;
	pthread_mutex_unlock(&philo->table->timing);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


// void	release_forks(t_philo *philo)
// {
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// }

// static void	mark_last_meal_time(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->table->timing);
// 	philo->last_meal_time = get_time();
// 	pthread_mutex_unlock(&philo->table->timing);
// }

// static void	increase_eat_count(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->table->eat);
// 	philo->meal_count++;
// 	pthread_mutex_unlock(&philo->table->eat);
// }

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

static void	start_delay(t_philo *philo)
{
	int	philo_num;
	int	philo_id;
	int	time_to_eat;

	philo_num = philo->table->num_of_philo;
	philo_id = philo->id;
	time_to_eat = philo->table->time_to_eat;
	if (philo_num % 2 == 0 && philo_id % 2 == 0)
		time_sleep(time_to_eat);
	else if (philo_num % 2 == 0 && philo_id % 2 != 0)
		time_sleep(0);
	else if (philo_num % 2 != 0 && philo_id % 2 == 0)
		time_sleep((2 * philo_num - philo_id) * time_to_eat / (philo_num - 1));
	else if (philo_num % 2 != 0 && philo_id % 2 != 0)
		time_sleep((philo_num - philo_id) * time_to_eat / (philo_num - 1));
	return ;
}

void	*life_of_philo(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	start_delay(philo);
	while (philo->table->end_flag == 0)
	{
		if (should_continue(philo) == 0)
			return (0);
		take_fork(philo);
		if (should_continue(philo) == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (NULL);
		}
		eating(philo);
		if (should_continue(philo) == 0 || philo->meal_count == philo->table->num_of_must_eat)
			return (NULL);
		time_sleep(philo->table->time_to_sleep);
		if (should_continue(philo) == 0)
			return (NULL);
		print_thinking(philo);
	}
	return (NULL);
}
