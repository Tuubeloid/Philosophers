/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:37:33 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/15 01:13:50 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	timer(int milliseconds)
{
	long	start;
	long	end;
	t_rules	*rules;

	start = get_current_time();
	end = start + milliseconds;
	while (get_current_time() < end)
	{
		if (rules->philo_died == 1 || rules->all_fed == 1)
			return (1);
		usleep(300);
	}
	return (0);
}
