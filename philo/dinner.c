/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:31 by kishizu           #+#    #+#             */
/*   Updated: 2024/06/12 22:00:00 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_one_philo(t_table *info)
{
	print_forks(&(info->philos[0]));
	time_sleep(info->time_to_die);
	print_dead(&(info->philos[0]));
	return ;
}

void	start_dinner(t_table *info)
{
	int		i;

	info->start_time = get_time();
	i = 0;
	if (info->num_of_philo == 1)
	{
		_one_philo(info);
		return ;
	}
	while (i < info->num_of_philo)
	{
		pthread_create(&info->philos[i].thread_id, NULL, &start_philo,
			(void *)&info->philos[i]);
		i++;
	}
	monitor(info);
}

void	end_dinner(t_table *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&info->table_lock);
}
