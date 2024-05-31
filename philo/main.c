/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:36 by kishizu           #+#    #+#             */
/*   Updated: 2024/05/31 19:09:02 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_join_threads(t_table *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(info->philos[i].thread_id, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	info;

	if (!check_arg(argc, argv))
		return (printf("Error\n"));
	if (!init_data(argc, argv, &info))
		return (printf("Error\n"));
	start_dinner(&info);
	if (info.num_of_philo != 1)
		_join_threads(&info);
	end_dinner(&info);
	return (0);
}
