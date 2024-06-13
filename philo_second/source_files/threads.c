/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:56:53 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/14 01:47:03 by tvalimak         ###   ########.fr       */
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
	if (pthread_create(&rules->thread_id[i], NULL,
			monitor_threads, rules) != 0)
	{
		printf("Error: Thread creation failed\n");
		thread_fail_handler(rules, i);
	}
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
	while (rules->philo_died == 0)
	{
		if (rules->all_fed == 1)
			break ;
		if (rules->philo_died == 1)
			break ;
	}
	if (pthread_join(rules->thread_id[i], NULL) != 0)
		error(rules, "Error: Thread join failed");
	while (i < rules->number_of_philosophers)
	{
		if (pthread_join(rules->thread_id[i], NULL) != 0)
			error(rules, "Error: Thread join failed");
		i++;
	}
	destroy_mutexes(rules);
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
/*
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
}*/

void	*monitor_threads(void *param)
{
	t_rules	*rules;
	int		i;

	printf("Monitoring threads\n");
	rules = (t_rules *)param;
	while (1)
	{
		i = 0;
		while (i < rules->number_of_philosophers)
		{
			pthread_mutex_lock(&rules->meal_lock);
			pthread_mutex_lock(&rules->monitor);
			if (rules->philo_data[i].time_since_last_meal + rules->time_to_die
				< get_current_time())
			{
				rules->philo_died = 1;
				pthread_mutex_unlock(&rules->monitor);
				pthread_mutex_lock(&rules->write_lock);
				printf("%ld %d %s\n", get_current_time() - \
				rules->philo_data[i].time_since_start, i + 1, "died");
				pthread_mutex_unlock(&rules->meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&rules->meal_lock);
			pthread_mutex_unlock(&rules->monitor);
			i++;
		}
		if (rules->all_fed == 1)
		{
			pthread_mutex_lock(&rules->meal_lock);
			pthread_mutex_lock(&rules->write_lock);
			printf("All philosophers have eaten %d meals\n", \
			rules->number_of_meals);
			pthread_mutex_unlock(&rules->meal_lock);
			pthread_mutex_unlock(&rules->write_lock);
			return (NULL);
		}
	}
}
