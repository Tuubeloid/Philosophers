/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:14:34 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/11 17:14:49 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	destroy_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->threads_running)
	{
		if (pthread_mutex_destroy(&rules->fork_id[i]) != 0)
			error(rules, "Error: Fork mutex destroy failed");
		i++;
	}
	if (pthread_mutex_destroy(&rules->monitor) != 0)
		error(rules, "Error: Monitor mutex destroy failed");
	if (pthread_mutex_destroy(&rules->write_lock) != 0)
		error(rules, "Error: Writelock mutex destroy failed");
	free (rules);
}
