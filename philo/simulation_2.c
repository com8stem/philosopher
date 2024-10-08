/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:41:11 by kishizu           #+#    #+#             */
/*   Updated: 2024/06/19 19:30:34 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_forks(philo);
	pthread_mutex_lock(philo->right_fork);
	print_forks(philo);
	return (0);
}

static void	_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = 1;
	print_eating(philo);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->lock);
	time_sleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = 0;
	if (philo->meal_count != -1)
		philo->meal_count++;
	pthread_mutex_unlock(&philo->lock);
	_release_forks(philo);
}

void	routine(t_philo *philo)
{
	while (1)
	{
		if (should_continue(philo) == false)
			return ;
		_take_fork(philo);
		if (should_continue(philo) == false)
		{
			_release_forks(philo);
			return ;
		}
		_eating(philo);
		if (should_continue(philo) == false)
			return ;
		get_sleep(philo);
		if (should_continue(philo) == false)
			return ;
		print_thinking(philo);
	}
}
