/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:38:04 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/13 22:40:27 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int		check_if_fed(t_rules *rules, int number_of_meals)
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
	return (1);
}

void	*monitor_threads(void *param)
{
	t_rules	*rules;

	rules = (t_rules *)param;
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
	return (NULL);
}

/*
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
}*/