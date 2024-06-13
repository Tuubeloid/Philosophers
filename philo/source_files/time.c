/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:37:33 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/13 21:08:06 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int timer(int milliseconds, t_philo_data *philo, int status, int first_fork, int second_fork)
{
	long start;
	long end;

	start = get_current_time();
	end = start + milliseconds;
	while (get_current_time() < end)
	{
		usleep(500);
	}
	usleep(500);
	if (death_monitor(philo, status, first_fork, second_fork) == 1)
		return (1);
	return (0);
}
