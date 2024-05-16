// #include "philo.h"


// static void	_report_death(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->table->death);
// 	philo->dead = true;
// 	philo->table->end_flag = true;
// 	pthread_mutex_unlock(&philo->table->death);
// 	print_dead(philo);
// }


// static bool	_is_him_dead(t_table *info, int i)
// {
// 	pthread_mutex_lock(&info->timing);
// 	if (get_time() - info->philos[i].last_meal_time > info->time_to_die
// 			&& info->philos[i].last_meal_time != -1
// 			&& (info->philos[i].last_meal_time < info->num_of_must_eat
// 				|| info->num_of_must_eat == -1))
// 	{
// 		pthread_mutex_unlock(&info->timing);
// 		return (true);
// 	}
// 	pthread_mutex_unlock(&info->timing);
// 	return (false);
// }

// static bool	_is_game_clear(t_table *info)
// {
// 	int	i;

// 	if (info->num_of_must_eat == -1)
// 		return (false);
// 	i = 0;
// 	while (i < info->num_of_philo)
// 	{
// 		if (info->philos[i].meal_count < info->num_of_must_eat)
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// void	*monitor_philo(void *info_arg)
// {
// 	int		i;
// 	t_table	*info;

// 	info = (t_table *)info_arg;
// 	i = 0;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&info->eat);
// 		if (_is_game_clear(info) == true)
// 		{
// 			pthread_mutex_unlock(&info->eat);
// 			return (NULL);
// 		}
// 		if (_is_him_dead(info, i) == true)
// 		{
// 			pthread_mutex_unlock(&info->eat);
// 			_report_death(&info->philos[i]);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&info->eat);
// 		i = (i + 1) % info->num_of_philo;
// 	}
// 	return (NULL);
// }
