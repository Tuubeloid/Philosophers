/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:36:15 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/16 17:47:50 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef struct s_rules t_rules;

typedef struct s_philo_data
{
	int				philo_id;
	int				has_forks;
	int				right_fork;
	int				has_right;
	int				left_fork;
	int				has_left;
	int				meals_eaten;
	long			time_since_last_meal;
	long			time_since_start;
	pthread_mutex_t	*monitor;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	t_rules			*rules;
}				t_philo_data;

typedef struct s_rules
{
	int					odd_sync;
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					philo_died;
	int					all_fed;
	long				clock_rate;
	int					threads_running;
	int					number_of_meals;
	int					total_deaths;
	int					write_lock_locked;
	long				start_time;
	pthread_mutex_t		monitor;
	pthread_mutex_t		fork_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		fork_id[200];
	int					fork_taken[200];
	t_philo_data		philo_data[200];
	pthread_t			thread_id[200];
}				t_rules;

/* ************************************************************************** */
/*                             Parse.c                                        */
/* ************************************************************************** */

int		check_args(int argv_int[5], char **argv, int argc);
void	parse_args(t_rules *philo, char **argv);

/* ************************************************************************** */
/*                             error.c                                        */
/* ************************************************************************** */

void	error(t_rules *rules, char *message);
void	thread_fail_handler(t_rules *rules, int i);

/* ************************************************************************** */
/*                             init.c                                         */
/* ************************************************************************** */

void	init_philosophers(t_rules *rules);
void	init_vars(t_rules *rules);

/* ************************************************************************** */
/*                             process.c                                      */
/* ************************************************************************** */

void	*process_simulation(void *param);
long	get_current_time(void);

/* ************************************************************************** */
/*                             threads.c                                      */
/* ************************************************************************** */

void	spawn_threads(t_rules *rules);
void	join_threads(t_rules *rules);
void	monitor_threads(void *param);
void	destroy_mutexes(t_rules *rules);

/* ************************************************************************** */
/*                             time.c                                         */
/* ************************************************************************** */

long	get_current_time(void);
int		timer(int milliseconds, t_philo_data *philo);

int		check_death(t_rules *rules);

int		mutexlock(t_philo_data *philo, pthread_mutex_t *mutex);
int		mutexunlock(t_philo_data *philo, pthread_mutex_t *mutex);

void	write_with_thread(t_philo_data *philo, char *message);

void	lay_forks(t_philo_data *philo);

#endif
