#include "philo.h"

static int	ft_atoi(const char *str)
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

static bool	check_t_philo(t_table *info)
{
	if (info->num_of_philo == -1
		||info->time_to_die == -1
		||info->time_to_eat == -1
		||info->time_to_sleep == -1)
		return (false);
	else if (info->num_of_philo == 0
		||info->time_to_die == 0
		||info->time_to_eat == 0
		||info->time_to_sleep == 0
		||info->num_of_must_eat == 0)
		return (false);
	return (true);
}

static void	set_fork(t_philo *philo, pthread_mutex_t *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->num_of_philo;
	philo->left_fork = &forks[position];
	philo->right_fork = &forks[(position + 1) % philo_nbr];
}

static void	init_philo(t_table *info)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < info->num_of_philo)
	{
		philo = &(info->philos[i]);
		philo->id = i + 1;
		philo->dead = false;
		philo->meal_count = 0;
		philo->is_eating = 0;
		philo->last_meal_time = 0;
		philo->table = info;
		philo->time_to_die = info->time_to_die;
		philo->time_to_eat = info->time_to_eat;
		philo->time_to_sleep = info->time_to_sleep;
		pthread_mutex_init(&philo->lock, NULL);
		set_fork(philo, info->forks, i);
		i++;
	}
}

bool	init_data(int argc, char **argv, t_table *info)
{
	int		i;

	i = 0;
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->end_flag = 0;
	info->num_of_finish = 0;
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
	else
		info->num_of_must_eat = -1;
	if (!check_t_philo(info))
		return (false);
	pthread_mutex_init(&info->timing, NULL);
	pthread_mutex_init(&info->write, NULL);
	while (i < info->num_of_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	init_philo(info);
	return (true);
}

