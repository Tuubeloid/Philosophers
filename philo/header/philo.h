/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:36:15 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/13 22:49:38 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef struct s_rules	t_rules;

typedef struct s_philo_data
{
	int				philo_id;
	int				right_fork;
	int				left_fork;
	int				meals_eaten;
	long			time_since_last_meal;
	long			time_since_start;
	pthread_mutex_t	*monitor;
	pthread_mutex_t	*write_lock;
	t_rules			*rules;
}				t_philo_data;

typedef struct s_rules
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					philo_died;
	int					all_fed;
	int					threads_running;
	int					number_of_meals;
	int					total_deaths;
	long				start_time;
	pthread_mutex_t		monitor;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		fork_id[200];
	t_philo_data		philo_data[200];
	pthread_t			thread_id[200];
	pthread_t			monitor_thread;
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
void	*monitor_threads(void *param);
long	get_current_time(void);

/* ************************************************************************** */
/*                             threads.c                                      */
/* ************************************************************************** */

void	spawn_threads(t_rules *rules);
void	join_threads(t_rules *rules);
void	destroy_mutexes(t_rules *rules);

/* ************************************************************************** */
/*                             time.c                                         */
/* ************************************************************************** */

long	get_current_time(void);
int 	timer(int milliseconds, t_philo_data *philo, int status, int first_fork, int second_fork);

int     death_monitor(t_philo_data *philo, int status, int first_fork, int second_fork);

#endif
