#include "philo.h"

bool	ft_is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}


bool	is_valid_param(char *arg)
{
	int	i;

	i = 0;
	while (ft_is_space(arg[i]))
		i++;
	if (arg[i] == '-')
		return (false);
	if (arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (!(argc == 5 || argc == 6))
		return (false);
	while (i < argc)
	{
		if (!is_valid_param(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	if (!check_arg(argc, argv))
		return (printf("[%d]\n", argc));
	return (0);
}
