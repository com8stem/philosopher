#include "philo.h"

static void _join_threads(t_table *info)
{
	int i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(info->philos[i].thread_id, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table info;

	if (!check_arg(argc, argv))
		return (printf("Argument Error\n"));
	if (!init_data(argc, argv, &info))
		return (printf("Argument Error\n"));
	start_dinner(&info);
	if (info.num_of_philo != 1)
		_join_threads(&info);
	end_dinner(&info);
	return (0);
}
