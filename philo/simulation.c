/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:46 by kishizu           #+#    #+#             */
/*   Updated: 2024/06/19 19:31:10 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_start_delay(t_philo *philo)
{
	int	philo_num;
	int	philo_id;
	int	time_to_eat;

	philo_num = philo->table->num_of_philo;
	philo_id = philo->id;
	time_to_eat = philo->table->time_to_eat;
	if (philo_num % 2 == 0)
	{
		if (philo_id % 2 == 0)
			time_sleep(time_to_eat);
	}
	else
	{
		if (philo_id % 2 == 0)
			time_sleep((2 * philo_num - philo_id)
				* time_to_eat / (philo_num - 1));
		else
			time_sleep((philo_num - philo_id)
				* time_to_eat / (philo_num - 1));
	}
	return ;
}

void	*start_philo(void *philo_ptr)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)philo_ptr;
	time = get_time();
	while (time < philo->table->start_time)
	{
		usleep(10);
		time = get_time();
	}
	pthread_mutex_lock(&philo->lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->lock);
	_start_delay(philo);
	routine(philo);
	return (NULL);
}
