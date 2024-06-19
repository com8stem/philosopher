/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:39 by kishizu           #+#    #+#             */
/*   Updated: 2024/06/19 19:35:49 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_dead_case(t_philo *philo)
{
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(&philo->table->table_lock);
	print_dead(philo);
	philo->table->end_flag = 1;
	pthread_mutex_unlock(&philo->table->table_lock);
	return (0);
}

static int	_check_last_meal(t_philo *philo)
{
	long	time;

	time = get_time();
	pthread_mutex_lock(&philo->lock);
	if (philo->last_meal_time != -1 && time
		- philo->last_meal_time >= philo->time_to_die && philo->is_eating == 0)
	{
		_dead_case(philo);
		return (FINISH);
	}
	pthread_mutex_unlock(&philo->lock);
	return (CONTINUE);
}

static bool	_check_must_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->full == false && philo->table->num_of_must_eat > 0
		&& philo->meal_count >= philo->table->num_of_must_eat)
	{
		philo->full = true;
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&philo->table->table_lock);
		philo->table->num_of_finish++;
		if (philo->table->num_of_finish >= philo->table->num_of_philo)
		{
			philo->table->end_flag = 1;
			pthread_mutex_unlock(&philo->table->table_lock);
			return (FINISH);
		}
		pthread_mutex_unlock(&philo->table->table_lock);
		return (CONTINUE);
	}
	pthread_mutex_unlock(&philo->lock);
	return (CONTINUE);
}

static bool	_is_dead(t_philo *philo)
{
	if (_check_last_meal(philo) == FINISH)
		return (true);
	if (_check_must_eat(philo) == FINISH)
		return (true);
	return (false);
}

void	*monitor(void *arg)
{
	t_table	*info;
	t_philo	*philo;
	int		i;

	info = (t_table *)arg;
	i = 0;
	time_sleep(10);
	while (1)
	{
		philo = &info->philos[i];
		if (_is_dead(philo) == 1)
		{
			return (NULL);
		}
		i++;
		if (i == info->num_of_philo)
		{
			i = 0;
		}
	}
	return (NULL);
}
