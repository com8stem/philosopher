/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:39 by kishizu           #+#    #+#             */
/*   Updated: 2024/06/12 21:53:54 by kishizu          ###   ########.fr       */
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
	print_dead(philo);
	philo->table->end_flag = 1;
	pthread_mutex_unlock(&philo->table->table_lock);
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

static int	_check_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (get_time() - philo->last_meal_time >= philo->table->time_to_die
		&& philo->is_eating == 0)
		return (_dead_case(philo));
	if (philo->table->num_of_must_eat > 0
		&& philo->meal_count >= philo->table->num_of_must_eat
		&& philo->full == false)
	{
		philo->full = true;
		pthread_mutex_lock(&philo->table->table_lock);
		philo->table->num_of_finish++;
		if (philo->table->num_of_finish >= philo->table->num_of_philo)
		{
			philo->table->end_flag = 1;
			_unlock_tablelock_and_lock(philo);
			return (FINISH);
		}
		_unlock_tablelock_and_lock(philo);
		return (CONTINUE);
	}
	pthread_mutex_unlock(&philo->lock);
	return (CONTINUE);
}

static bool	_is_dead(t_philo *philo)
{
	if (_check_last_meal(philo) == 0)
		return (true);
	return (false);
}

void	*monitor(t_table *info)
{
	t_philo	*philo;
	int		i;

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
			i = 0;
		usleep(1);
	}
	return (NULL);
}
