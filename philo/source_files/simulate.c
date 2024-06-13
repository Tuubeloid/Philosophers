/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:33:50 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/14 00:36:51 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	status_handler(t_philo_data *philo, int status, int first_fork, int second_fork)
{
	if (status == 1)
	{
		pthread_mutex_unlock(&philo->rules->fork_id[first_fork]);
	}
	if (status == 2)
	{
		pthread_mutex_unlock(&philo->rules->fork_id[second_fork]);
		pthread_mutex_unlock(&philo->rules->fork_id[first_fork]);
	}
	pthread_mutex_unlock(&philo->rules->monitor);
	return (1);
}

int	death_monitor(t_philo_data *philo, int status, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->rules->monitor);
	if (philo->rules->philo_died == 1 || philo->rules->all_fed == 1)
	{
		return status_handler(philo, status, first_fork, second_fork);
	}
	pthread_mutex_unlock(&philo->rules->monitor);
	return (0);
}

int	write_with_thread(t_philo_data *philo, char *message, int status, int eat, int first_fork, int second_fork)
{
	long	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->rules->write_lock);
	if (eat == 1)
		philo->time_since_last_meal = get_current_time();
	printf("%ld %d %s\n", (current_time - philo->time_since_start), \
	philo->philo_id + 1, message);
	pthread_mutex_unlock(&philo->rules->write_lock);
	return (0);
}

void	determine_fork_order(t_philo_data *philo, int *first_fork, int *second_fork)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

void	acquire_forks(t_philo_data *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->rules->fork_id[first_fork]);
	if (write_with_thread(philo, "has taken a fork", 1, 0, first_fork, second_fork) == 1)
		return;
	pthread_mutex_lock(&philo->rules->fork_id[second_fork]);
	if (write_with_thread(philo, "has taken a fork", 2, 1, first_fork, second_fork) == 1)
		return;
}

void release_forks(t_philo_data *philo, int first_fork, int second_fork)
{
	pthread_mutex_unlock(&philo->rules->fork_id[second_fork]);
	pthread_mutex_unlock(&philo->rules->fork_id[first_fork]);
}

void thread_loop(t_philo_data *philo)
{
	int first_fork;
	int second_fork;
	
	determine_fork_order(philo, &first_fork, &second_fork);
	while (1)
	{
		acquire_forks(philo, first_fork, second_fork);
		if (write_with_thread(philo, "is eating", 2, 0, first_fork, second_fork) == 1)
			break;
		if (timer(philo->rules->time_to_eat, philo, 2, first_fork, second_fork) == 1)
			break;
		philo->meals_eaten++;
		release_forks(philo, first_fork, second_fork);
		if (write_with_thread(philo, "is sleeping", 0, 1, first_fork, second_fork) == 1)
			break;
		if (timer(philo->rules->time_to_sleep, philo, 0, first_fork, second_fork) == 1)
			break;
		if (write_with_thread(philo, "is thinking", 0, 0, first_fork, second_fork) == 1)
			break;
	}
}

void	*process_simulation(void *param)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)param;
	printf("Thread created for philosopher %d\n", philo->philo_id + 1);
	if (philo->left_fork == philo->right_fork)
	{
		printf("Philosopher %d has taken a fork\n", philo->philo_id + 1);
		usleep(philo->rules->time_to_die * 1000);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		usleep(philo->rules->time_to_eat * 1000);
	thread_loop(philo);
	return (NULL);
}
