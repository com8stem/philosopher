/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:49 by kishizu           #+#    #+#             */
/*   Updated: 2024/05/25 17:24:52 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_sleep(int time)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time)
		usleep(100);
	return ;
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	should_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_lock);
	if (philo->table->end_flag == true)
	{
		pthread_mutex_unlock(&philo->table->table_lock);
		return (false);
	}
	pthread_mutex_unlock(&philo->table->table_lock);
	return (true);
}

void	get_sleep(t_philo *philo)
{
	print_sleeping(philo);
	time_sleep(philo->table->time_to_sleep);
}
