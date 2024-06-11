/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:40:28 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/09 16:38:24 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	error(t_rules *rules, char *message)
{
	int	i;

	i = 1;
	printf("%s\n", message);
	while (i <= rules->threads_running)
	{
		if (pthread_mutex_destroy(&rules->fork_id[i]) != 0)
			error(rules, "Error: Mutex destroy failed");
		i++;
	}
	exit(1);
}

void	thread_fail_handler(t_rules *rules, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (pthread_join(rules->thread_id[j], NULL) != 0)
			error(rules, "Error: Thread join failed");
		j++;
	}
	destroy_mutexes(rules);
	exit(1);
}
