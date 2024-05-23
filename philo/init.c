#include "philo.h"

int	check_over(const char *nb, long num, int sign)
{
	long	next_digit;

	if (*nb == '\0' || *nb < '0' || *nb > '9')
		return (0);
	next_digit = *nb - '0';
	if (sign > 0)
	{
		if (num > LONG_MAX / 10)
			return (1);
		if (num == LONG_MAX / 10 && next_digit > LONG_MAX % 10)
			return (1);
	}
	else if (sign < 0)
	{
		if (num * sign < LONG_MIN / 10)
			return (-1);
		if (num * sign == LONG_MIN / 10 && next_digit * sign < LONG_MIN % 10)
			return (-1);
	}
	return (0);
}

int	ft_atoi(const char *str)
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

bool	check_t_philo(t_table *info)
{
	if (info->num_of_philo == -1
		||info->time_to_die == -1
		||info->time_to_eat == -1
		||info->time_to_sleep == -1
		||info->num_of_must_eat == -1)
		return (false);
	return (true);
}

void	set_fork(t_philo *philo, pthread_mutex_t *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->num_of_philo;
	// if (philo->id % 2 == 0)
	// {
		philo->left_fork = &forks[position];
		philo->right_fork = &forks[(position + 1) % philo_nbr];
	// }
	// else
	// {
	// 	philo->left_fork = &forks[(position + 1) % philo_nbr];
	// 	philo->right_fork = &forks[position];
	// }
}

void	philo_init(t_table *info)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < info->num_of_philo)
	{
		philo = &(info->philos[i]);
		philo->id = i + 1;
		philo->full = false;
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

void	init_philo(char **argv, t_table *info)
{
	int		i;

	i = 0;
	info->num_of_philo = atoi(argv[1]);
	info->time_to_die = atoi(argv[2]);
	info->time_to_eat = atoi(argv[3]);
	info->time_to_sleep = atoi(argv[4]);
	info->end_flag = 0;
	if (argv[5] != NULL)
		info->num_of_must_eat = atoi(argv[5]);
	else
		info->num_of_must_eat = -1;
	pthread_mutex_init(&info->timing, NULL);
	pthread_mutex_init(&info->write, NULL);
	while (i < info->num_of_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	philo_init(info);
}
