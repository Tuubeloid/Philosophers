/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:56:53 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/17 00:26:59 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->threads_running)
	{
		if (pthread_join(rules->thread_id[i], NULL) != 0)
			error(rules, "Error: Thread join failed");
		i++;
	}
}

void	spawn_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_count)
	{
		if (pthread_create(&rules->thread_id[i], NULL,
				process_simulation, &rules->philo_data[i]) != 0)
		{
			printf("Error: Thread creation failed\n");
			thread_fail_handler(rules, i);
		}
		rules->threads_running++;
		i++;
	}
}

int	check_if_fed(t_rules *rules, int number_of_meals)
{
	int	i;

	i = 0;
	while (i < rules->philo_count)
	{
		pthread_mutex_lock(&rules->meal_lock);
		if (rules->philo_data[i].meals_eaten < number_of_meals)
		{
			pthread_mutex_unlock(&rules->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&rules->meal_lock);
		i++;
	}
	rules->all_fed = 1;
	return (1);
}

int		set_death(t_rules *rules, int i)
{
	rules->philo_died = 1;
	write_with_thread(&rules->philo_data[i], "died");
	rules->write_lock_locked = 1;
	pthread_mutex_unlock(&rules->monitor);
	pthread_mutex_unlock(&rules->meal_lock);
	return (1);
}

int		philo_died(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_count)
	{
		pthread_mutex_lock(&rules->meal_lock);
		if (rules->philo_data[i].time_since_last_meal + rules->time_to_die
			< get_current_time())
		{
			pthread_mutex_unlock(&rules->meal_lock);
			pthread_mutex_lock(&rules->monitor);
			if (rules->philo_died == 0)
				set_death(rules, i);
			pthread_mutex_unlock(&rules->monitor);
			return (1);
		}
		pthread_mutex_unlock(&rules->meal_lock);
		i++;
	}
	return (0);
}

int		set_fed(t_rules *rules)
{
	rules->all_fed = 1;
	rules->write_lock_locked = 1;
	pthread_mutex_unlock(&rules->write_lock);
	pthread_mutex_unlock(&rules->monitor);
	return (1);
}

int		all_fed(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_count)
	{
		pthread_mutex_lock(&rules->meal_lock);
		if (rules->philo_data[i].meals_eaten < rules->number_of_meals)
		{
			pthread_mutex_unlock(&rules->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&rules->meal_lock);
		i++;
	}
	pthread_mutex_lock(&rules->write_lock);
	pthread_mutex_lock(&rules->monitor);
	if (rules->all_fed == 0)
		return (set_fed(rules));
	pthread_mutex_unlock(&rules->write_lock);
	pthread_mutex_unlock(&rules->monitor);
	return (1);
}

void	monitor_threads(void *param)
{
	t_rules	*rules;

	rules = (t_rules *)param;
	while (1)
	{
		if (philo_died(rules) == 1)
			break ;
		if (rules->number_of_meals != -1)
		{
			if (all_fed(rules) == 1)
				break ;
		}
	}
	while(rules->threads_running)
		usleep(100);
	join_threads(rules);
}
