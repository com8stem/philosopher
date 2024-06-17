/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:46 by kishizu           #+#    #+#             */
/*   Updated: 2024/06/10 19:48:16 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_philo(void *philo_ptr)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)philo_ptr;
	time = get_time();
	while(time < philo->table->start_time)
	{
		usleep(10);
		time = get_time();
	}
	pthread_mutex_lock(&philo->lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->lock);
	if (philo->id % 2 == 0)
		time_sleep(20);
	routine(philo);
	return (NULL);
}
