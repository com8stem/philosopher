/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:24:41 by kishizu           #+#    #+#             */
/*   Updated: 2024/06/12 21:59:43 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FINISH 0
# define CONTINUE 1

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	int					is_eating;
	bool				dead;
	long				meal_count;
	bool				full;
	long				last_meal_time;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		lock;
	pthread_t			thread_id;
	pthread_t			monitor;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	bool				end_flag;
	int					num_of_finish;
	int					num_of_must_eat;
	long				start_time;
	pthread_mutex_t		forks[201];
	t_philo				philos[201];
	pthread_mutex_t		table_lock;
	pthread_t			monitor;
}						t_table;

bool					check_arg(int argc, char **argv);
bool					init_data(int argc, char **argv, t_table *info);
void					start_dinner(t_table *info);
void					end_dinner(t_table *info);

bool					init_philo(t_table *info);
bool					error_destroy_mutex(pthread_mutex_t *mutex);
bool					error_destroy_mutex_fork(t_table *info, int i);

void					print_eating(t_philo *philo);
void					print_sleeping(t_philo *philo);
void					print_thinking(t_philo *philo);
void					print_dead(t_philo *philo);
void					print_forks(t_philo *philo);

void					*start_philo(void *philo_ptr);
void					routine(t_philo *philo);
void					*monitor(t_table *arg);

long					get_time(void);
bool					should_continue(t_philo *philo);

void					time_sleep(int time);
void					get_sleep(t_philo *philo);

#endif