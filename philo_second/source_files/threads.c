/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:56:53 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/16 16:54:38 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	printf("joining threads\n");
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

void	monitor_threads(void *param)
{
	t_rules	*rules;
	int		i;

	printf("Monitoring threads\n");
	rules = (t_rules *)param;
	while (1)
	{
		pthread_mutex_lock(&rules->monitor);
		if (rules->philo_died == 1)
		{
			pthread_mutex_unlock(&rules->monitor);
			break ;
		}
		pthread_mutex_unlock(&rules->monitor);
		i = 0;
		while (i < rules->philo_count)
		{
			pthread_mutex_lock(&rules->meal_lock);
			pthread_mutex_lock(&rules->monitor);
			if (rules->philo_died == 1)
			{
				pthread_mutex_unlock(&rules->meal_lock);
				pthread_mutex_unlock(&rules->monitor);
				break ;
			}
			if (rules->philo_data[i].time_since_last_meal + rules->time_to_die
				< get_current_time())
			{
				write_with_thread(&rules->philo_data[i], "died");
				rules->philo_died = 1;
				lay_forks(&rules->philo_data[i]);
				pthread_mutex_unlock(&rules->meal_lock);
				pthread_mutex_unlock(&rules->monitor);
				break ;
			}
			pthread_mutex_unlock(&rules->meal_lock);
			pthread_mutex_unlock(&rules->monitor);
			i++;
		}
		if (rules->number_of_meals != -1)
		{
			if (check_if_fed(rules, rules->number_of_meals))
			{
				pthread_mutex_lock(&rules->meal_lock);
				pthread_mutex_lock(&rules->write_lock);
				printf("All philosophers have eaten %d meals\n", \
				rules->number_of_meals);
				pthread_mutex_unlock(&rules->meal_lock);
				pthread_mutex_unlock(&rules->write_lock);
			}
		}
	}
	while(rules->threads_running)
		usleep(100);
	
	join_threads(rules);
	printf("end of monitoring");
}
