/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:37:33 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/09 20:10:18 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	timer(int milliseconds, t_philo_data *philo, int status)
{
	long	start;
	long	end;

	start = get_current_time();
	end = start + milliseconds;
	while (get_current_time() < end)
	{
		if (death_monitor(philo, status) == 1)
			break ;
		usleep(500);
	}
	usleep(500);
	return (0);
}
