/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:56:53 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/13 16:36:44 by tvalimak         ###   ########.fr       */
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
	printf("Spawning threads\n");
	while (i < rules->number_of_philosophers && rules->philo_died == 0)
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
	while (i < rules->number_of_philosophers)
	{
		pthread_mutex_lock(&rules->monitor);
		if (rules->philo_data[i].meals_eaten < number_of_meals)
		{
			pthread_mutex_unlock(&rules->monitor);
			return (0);
		}
		pthread_mutex_unlock(&rules->monitor);
		i++;
	}
	pthread_mutex_lock(&rules->write_lock);
	rules->all_fed = 1;
	return (1);
}

int	check_death(t_rules *rules)
{
	int		i;
	long	current_time;
	long	time_of_death;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		pthread_mutex_lock(&rules->monitor);
		if (rules->philo_data[i].time_since_last_meal + rules->time_to_die
			< get_current_time())
		{
			rules->philo_died = 1;
			pthread_mutex_lock(&rules->write_lock);
			current_time = get_current_time();
			time_of_death = current_time - \
			rules->philo_data[i].time_since_start;
			printf("%ld %d %s\n", time_of_death, i + 1, "died");
			pthread_mutex_unlock(&rules->monitor);
			return (1);
		}
		pthread_mutex_unlock(&rules->monitor);
		i++;
	}
	return (0);
}

void	monitor_threads(t_rules *rules)
{
	printf("Simulation started\n");
	while (1)
	{
		if (rules->number_of_meals != -1)
			if (check_if_fed(rules, rules->number_of_meals) == 1)
			{
				pthread_mutex_unlock(&rules->write_lock);
				break ;
			}
		if (check_death(rules) == 1)
		{
			pthread_mutex_unlock(&rules->write_lock);
			break ;
		}
	}
	join_threads(rules);
	usleep(1000000);
	destroy_mutexes(rules);
}
