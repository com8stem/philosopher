/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:44 by kishizu           #+#    #+#             */
/*   Updated: 2024/06/12 21:58:30 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_lock);
	if (philo->table->end_flag == false)
	{
		printf("%ld %d is eating\n", get_time() - philo->table->start_time,
			philo->id);
	}
	pthread_mutex_unlock(&philo->table->table_lock);
}

void	print_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_lock);
	if (philo->table->end_flag == false)
	{
		printf("%ld %d is sleeping\n", get_time() - philo->table->start_time,
			philo->id);
	}
	pthread_mutex_unlock(&philo->table->table_lock);
}

void	print_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_lock);
	if (philo->table->end_flag == false)
	{
		printf("%ld %d is thinking\n", get_time() - philo->table->start_time,
			philo->id);
	}
	pthread_mutex_unlock(&philo->table->table_lock);
}

void	print_dead(t_philo *philo)
{
	if (philo->table->end_flag == false)
	{
		printf("%ld %d died\n", get_time() - philo->table->start_time,
			philo->id);
	}
}

void	print_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_lock);
	if (philo->table->end_flag == false)
	{
		printf("%ld %d has taken a fork\n", get_time()
			- philo->table->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->table->table_lock);
}
