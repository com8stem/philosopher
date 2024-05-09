#include "philo.h"

int	main(int argc, char **argv)
{
	t_table info;

	if (!check_arg(argc, argv))
		return (printf("argerror\n"));
	init_philo(argv, &info);
	start_dinner(&info);
	end_dinner(&info);
	return (0);
}
