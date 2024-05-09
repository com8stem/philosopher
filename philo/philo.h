#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>


typedef struct s_table	t_table;


typedef struct s_philo
{
	int			id;
	long		meal_count;
	bool		full;
	long		last_meal_time;
	bool		dead;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_must_eat;
	long		start_time;
	bool		end_flag;
	pthread_mutex_t		forks[200];
	t_philo		philos[200];
	pthread_mutex_t		eat;
	pthread_mutex_t		death;
	pthread_mutex_t		timing;
	pthread_t	supreviser;
}				t_table;

bool	check_arg(int argc, char **argv);
void	init_philo(char **argv, t_table *info);

void print_eating(t_philo *philo);
void print_sleeping(t_philo *philo);
void print_thinking(t_philo *philo);
void print_dead(t_philo *philo);
void print_forks(t_philo *philo);

void	start_dinner(t_table *info);

long	get_time(void);

void	*life_of_philo(void *philo_ptr);

void	time_sleep(int time);

void	end_dinner(t_table *info);

void	*monitor_philo(void *info_arg);



#endif