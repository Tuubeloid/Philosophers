/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:56:53 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/13 22:46:16 by tvalimak         ###   ########.fr       */
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
	if (pthread_join(rules->monitor_thread, NULL) != 0)
		error(rules, "Error: Thread join failed");
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
	if (pthread_create(&rules->monitor_thread, NULL,
			monitor_threads, rules) != 0)
	{
		printf("Error: Thread creation failed\n");
		thread_fail_handler(rules, i);
	}
}
