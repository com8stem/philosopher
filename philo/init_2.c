/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:29:57 by kishizu           #+#    #+#             */
/*   Updated: 2024/05/31 18:58:47 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_set_fork(t_philo *philo, pthread_mutex_t *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->num_of_philo;
	philo->left_fork = &forks[position];
	philo->right_fork = &forks[(position + 1) % philo_nbr];
}

static bool	destroy_mutex_philo_lock(t_table *info, int i)
{
	t_philo	*philo;

	i = i - 1;
	while (i >= 0)
	{
		philo = &(info->philos[i]);
		pthread_mutex_destroy(&philo->lock);
		i--;
	}
	return (false);
}

bool	init_philo(t_table *info)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < info->num_of_philo)
	{
		philo = &(info->philos[i]);
		philo->id = i + 1;
		philo->is_eating = 0;
		philo->dead = false;
		philo->meal_count = 0;
		philo->last_meal_time = 0;
		philo->time_to_die = info->time_to_die;
		philo->time_to_eat = info->time_to_eat;
		philo->time_to_sleep = info->time_to_sleep;
		if (pthread_mutex_init(&philo->lock, NULL) != 0)
			return (destroy_mutex_philo_lock(info, i));
		philo->table = info;
		_set_fork(philo, info->forks, i);
		i++;
	}
	return (true);
}

bool	error_destroy_mutex(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
	return (false);
}

bool	error_destroy_mutex_fork(t_table *info, int i)
{
	i = i - 1;
	while (i >= 0)
		pthread_mutex_destroy(&info->forks[i]);
	pthread_mutex_destroy(&info->table_lock);
	pthread_mutex_destroy(&info->write);
	return (false);
}
