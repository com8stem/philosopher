/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:33 by kishizu           #+#    #+#             */
/*   Updated: 2024/05/31 18:58:05 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_ft_atoi(const char *str)
{
	long	num;
	long	sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (10 * num) + (*str - '0');
		str++;
		if (num > INT_MAX)
			return (-1);
	}
	return ((int)(num * sign));
}

static void	init_table(int argc, char **argv, t_table *info)
{
	info->num_of_philo = _ft_atoi(argv[1]);
	info->time_to_die = _ft_atoi(argv[2]);
	info->time_to_eat = _ft_atoi(argv[3]);
	info->time_to_sleep = _ft_atoi(argv[4]);
	info->end_flag = false;
	info->num_of_finish = 0;
	if (argc == 6)
		info->num_of_must_eat = _ft_atoi(argv[5]);
	else
		info->num_of_must_eat = -1;
}

static bool	_check_t_philo(t_table *info)
{
	if (info->num_of_philo == -1 || info->time_to_die == -1
		|| info->time_to_eat == -1 || info->time_to_sleep == -1)
		return (false);
	else if (info->num_of_philo == 0 || info->time_to_die == 0
		|| info->time_to_eat == 0 || info->time_to_sleep == 0
		|| info->num_of_must_eat == 0)
		return (false);
	else if (info->num_of_philo > 200)
		return (false);
	return (true);
}

bool	init_data(int argc, char **argv, t_table *info)
{
	int	i;

	i = 0;
	init_table(argc, argv, info);
	if (!_check_t_philo(info))
		return (false);
	if (pthread_mutex_init(&info->table_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (error_destroy_mutex(&info->table_lock));
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (error_destroy_mutex_fork(info, i));
		i++;
	}
	if (init_philo(info) == false)
		return (error_destroy_mutex_fork(info, i));
	return (true);
}
