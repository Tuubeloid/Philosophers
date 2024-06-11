/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:33:50 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/11 19:16:32 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	status_handler(t_philo_data *philo, int status, int status_two)
{
	if (status == 1)
		pthread_mutex_unlock(&philo->rules->fork_id[philo->left_fork]);
	if (status == 2)
	{
		pthread_mutex_unlock(&philo->rules->fork_id[philo->left_fork]);
		pthread_mutex_unlock(&philo->rules->fork_id[philo->right_fork]);
	}
	if (status_two == 1)
		pthread_mutex_unlock(&philo->rules->write_lock);
	if (status_two == 2)
	{
		pthread_mutex_unlock(&philo->rules->write_lock);
		pthread_mutex_unlock(&philo->rules->monitor);
	}
	if (status_two == 3)
		pthread_mutex_unlock(&philo->rules->monitor);
	return (1);
}

int	death_monitor(t_philo_data *philo, int status)
{
	long	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->rules->monitor);
	if (philo->rules->all_fed == 1)
	{
		pthread_mutex_lock(&philo->rules->write_lock);
		return (status_handler(philo, status, 1));
	}
	if (philo->rules->philo_died == 1)
		return (status_handler(philo, status, 3));
	pthread_mutex_unlock(&philo->rules->monitor);
	if (current_time - philo->time_since_last_meal >= \
	philo->rules->time_to_die)
	{
		pthread_mutex_lock(&philo->rules->monitor);
		philo->rules->philo_died = 1;
		status_handler(philo, status, 2);
		return (1);
	}
	return (0);
}

int	write_with_thread(t_philo_data *philo, char *message, int status, int eat)
{
	long	current_time;

	pthread_mutex_lock(&philo->rules->monitor);
	pthread_mutex_lock(&philo->rules->write_lock);
	if (death_monitor(philo, status) == 1)
		return (1);
	current_time = get_current_time() - philo->time_since_start;
	if (philo->rules->philo_died == 1)
	{
		status_handler(philo, status, 2);
		return (1);
	}
	if (eat == 1 && philo->rules->number_of_meals != -1)
		philo->meals_eaten++;
	printf("%ld %d %s\n", current_time, philo->philo_id + 1, message);
	pthread_mutex_unlock(&philo->rules->monitor);
	pthread_mutex_unlock(&philo->rules->write_lock);
	if (death_monitor(philo, status) == 1)
		return (1);
	return (0);
}

void	thread_loop(t_philo_data *philo)
{
	while (1)
	{
		if (death_monitor(philo, 0) == 1)
			break ;
		pthread_mutex_lock(&philo->rules->fork_id[philo->left_fork]);
		if (write_with_thread(philo, "has taken a fork", 1, 0) == 1)
			break ;
		pthread_mutex_lock(&philo->rules->fork_id[philo->right_fork]);
		pthread_mutex_lock(&philo->rules->monitor);
		philo->time_since_last_meal = get_current_time();
		pthread_mutex_unlock(&philo->rules->monitor);
		if (write_with_thread(philo, "has taken a fork", 2, 0) == 1)
			break ;
		if (write_with_thread(philo, "is eating", 2, 1) == 1)
			break ;
		timer(philo->rules->time_to_eat, philo, 2);
		pthread_mutex_unlock(&philo->rules->fork_id[philo->left_fork]);
		pthread_mutex_unlock(&philo->rules->fork_id[philo->right_fork]);
		if (write_with_thread(philo, "is sleeping", 0, 0) == 1)
			break ;
		timer(philo->rules->time_to_sleep, philo, 0);
		if (write_with_thread(philo, "is thinking", 0, 0) == 1)
			break ;
	}
}

void	*process_simulation(void *param)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)param;
	if (philo->left_fork == philo->right_fork)
	{
		write_with_thread(philo, "has taken a fork", 0, 0);
		timer(philo->rules->time_to_die, philo, 0);
		philo->rules->philo_died = 1;
		return (NULL);
	}
	if (philo->philo_id % 2 == 0 || philo->philo_id == \
	philo->rules->number_of_philosophers)
		usleep(10000);
	thread_loop(philo);
	return (NULL);
}
