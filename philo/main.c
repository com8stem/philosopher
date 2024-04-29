#include "philo.h"

typedef struct s_philo
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_must_eat;
}		t_philo;

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

bool	check_t_philo(t_philo info)
{
	if (info.num_of_philo == -1
		||info.time_to_die == -1
		||info.time_to_eat == -1
		||info.time_to_sleep == -1
		||info.num_of_must_eat == -1)
		return (false);
	return (true);
}

bool	init_philo(int argc, char **argv)
{
	t_philo	info;
	(void) argc;

	info.num_of_philo = ft_atoi(argv[1]);
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		info.num_of_must_eat = ft_atoi(argv[5]);
	else
		info.num_of_must_eat = 0;
	if (!check_t_philo(info))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	if (!check_arg(argc, argv))
		return (printf("argerror\n"));
	if (!init_philo(argc, argv))
		return (printf("initerror\n"));
	return (0);
}
