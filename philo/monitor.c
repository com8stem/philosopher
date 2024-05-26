/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:39 by kishizu           #+#    #+#             */
/*   Updated: 2024/05/25 17:40:13 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_unlock_tablelock_and_lock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->table_lock);
	pthread_mutex_unlock(&philo->lock);
}

static int	_dead_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_lock);
	philo->table->end_flag = 1;
	pthread_mutex_unlock(&philo->table->table_lock);
	print_dead(philo);
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

static int	_check_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (get_time() - philo->last_meal_time >= philo->table->time_to_die
		&& philo->is_eating == 0)
		return (_dead_case(philo));
	if (philo->meal_count == philo->table->num_of_must_eat)
	{
		pthread_mutex_lock(&philo->table->table_lock);
		philo->table->num_of_finish++;
		if (philo->table->num_of_finish == philo->table->num_of_philo)
		{
			philo->table->end_flag = 1;
			_unlock_tablelock_and_lock(philo);
			return (0);
		}
		_unlock_tablelock_and_lock(philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

static bool	_is_dead(t_philo *philo)
{
	if (_check_last_meal(philo) == 0)
		return (true);
	return (false);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (_is_dead(philo) == 1)
			return (NULL);
		time_sleep(philo->table->time_to_die / 10);
	}
	return (NULL);
}
