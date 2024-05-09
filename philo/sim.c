#include "philo.h"

int	take_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->first_fork) != 0)
		print_forks(philo);
	else
		return (0);
	if (pthread_mutex_lock(philo->second_fork) != 0)
		print_forks(philo);
	else
		pthread_mutex_unlock(philo->first_fork);
	return (0);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

static void	mark_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->timing);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->table->timing);
}

static void	increase_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eat);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->table->eat);
}

static bool	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death);
	if (philo->dead == true || philo->table->end_flag == true)
	{
		pthread_mutex_unlock(&philo->table->death);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->death);
	return (false);
}

static bool	should_continue(t_philo *philo)
{
	if (check_dead(philo) == true
		|| philo->meal_count == philo->table->num_of_must_eat)
		return (false);
	return (true);
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
	mark_last_meal_time(philo);
	// if (philo->id % 2 == 0)
	// 	time_sleep(1);
	start_delay(philo);
	while (1)
	{
		if (should_continue(philo) == false)
			return (NULL);
		print_thinking(philo);
		if (take_fork(philo) == 1)
			return (NULL);
		if (should_continue(philo) == false)
			return (NULL);
		print_eating(philo);
		mark_last_meal_time(philo);
		time_sleep(philo->table->time_to_sleep); // timetoeat?
		increase_eat_count(philo);
		release_forks(philo);
		if (should_continue(philo) == false)
			return (NULL);
		get_sleep(philo);
	}
	return (NULL);
}
