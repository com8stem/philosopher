#include "philo.h"

int	main(int argc, char **argv)
{
	t_table info;

	if (!check_arg(argc, argv))
		return (printf("argerror\n"));
	init_philo(argv, &info);
	start_dinner(&info);
	start_monitor(&info);
	if (info.num_of_philo != 1)
	{
		join_threads(&info);
		end_dinner(&info);
	}
	return (0);
}
