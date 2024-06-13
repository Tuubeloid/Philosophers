/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:42:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/14 01:14:01 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	init_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		if (pthread_mutex_init(&(rules->fork_id[i]), NULL) != 0)
			error(rules, "Error: Mutex init failed");
		rules->fork_taken[i] = 0;
		i++;
	}
	if (pthread_mutex_init(&rules->monitor, NULL) != 0)
		error(rules, "Error: Mutex init failed");
	if (pthread_mutex_init(&rules->write_lock, NULL) != 0)
		error(rules, "Error: Mutex init failed");
	if (pthread_mutex_init(&rules->meal_lock, NULL) != 0)
		error(rules, "Error: Mutex init failed");
}

void	init_philosophers(t_rules *rules)
{
	int				i;
	long			time;

	i = 0;
	time = get_current_time();
	while (i < rules->number_of_philosophers)
	{
		ft_memset(&rules->philo_data[i], 0, sizeof(t_philo_data));
		rules->philo_data[i].philo_id = i;
		rules->philo_data[i].right_fork = i;
		if (i < rules->number_of_philosophers - 1)
			rules->philo_data[i].left_fork = i + 1;
		else
			rules->philo_data[i].left_fork = 0;
		rules->philo_data[i].rules = rules;
		rules->philo_data[i].time_since_last_meal = time;
		rules->philo_data[i].time_since_start = time;
		rules->philo_data[i].monitor = &rules->monitor;
		rules->philo_data[i].write_lock = &rules->write_lock;
		i++;
	}
}

void	init_time(t_rules *rules)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		error(rules, "Error: gettimeofday failed");
	rules->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
}

void	init_vars(t_rules *rules)
{
	init_mutexes(rules);
	init_time(rules);
	init_philosophers(rules);
}
