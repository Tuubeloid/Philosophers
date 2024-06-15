/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:37:33 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/15 09:26:10 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	timer(int milliseconds, t_philo_data *philo)
{
	long	start;
	long	end;
	t_rules	*rules;

	rules = philo->rules;
	start = get_current_time();
	end = start + milliseconds;
	while (get_current_time() < end)
	{
		if (check_death(rules) == 1)
			return (1);
		usleep(300);
	}
	return (0);
}
