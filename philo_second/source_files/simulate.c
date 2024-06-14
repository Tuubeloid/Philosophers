/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:33:50 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/15 02:51:00 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
/*
int	status_handler(t_philo_data *philo, int status)
{
	if (status == 1)
	{
		pthread_mutex_unlock(&philo->rules->fork_id[philo->left_fork]);
	}
	if (status == 2)
	{
		pthread_mutex_unlock(&philo->rules->fork_id[philo->left_fork]);
		pthread_mutex_unlock(&philo->rules->fork_id[philo->right_fork]);
	}
	return (1);
}

int	death_monitor(t_philo_data *philo, int status)
{
	pthread_mutex_lock(&philo->rules->monitor);
	if (philo->rules->philo_died == 1 || philo->rules->all_fed == 1)
	{
		if (status == 0)
			return (status_handler(philo, 0));
		if (status == 1)
			return (status_handler(philo, 1));
		if (status == 2)
			return (status_handler(philo, 2));
	}
	pthread_mutex_unlock(&philo->rules->monitor);
	return (0);
}

int	write_with_thread(t_philo_data *philo, char *message, int status, int eat)
{
	long	current_time;

	current_time = get_current_time();
	if (death_monitor(philo, status) == 1)
		return (1);
	pthread_mutex_lock(&philo->rules->write_lock);
	if (eat == 1)
		philo->time_since_last_meal = get_current_time();
	printf("%ld %d %s\n", (current_time - philo->time_since_start), \
	philo->philo_id + 1, message);
	pthread_mutex_unlock(&philo->rules->write_lock);
	return (0);
}
void	meal_refresh(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->rules->meal_lock);
	philo->time_since_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->rules->meal_lock);
}

void	thread_loop(t_philo_data *philo)
{
	while (1)
	{
		while (philo->rules->fork_taken[philo->left_fork] == 1)
			usleep(300);
		philo->rules->fork_taken[philo->left_fork] = 1;
		pthread_mutex_lock(&philo->rules->fork_id[philo->left_fork]);
		if (write_with_thread(philo, "has taken a fork", 1, 0) == 1)
			break ;
		while (philo->rules->fork_taken[philo->right_fork] == 1)
			usleep(300);
		philo->rules->fork_taken[philo->right_fork] = 1;
		pthread_mutex_lock(&philo->rules->fork_id[philo->right_fork]);
		pthread_mutex_lock(&philo->rules->meal_lock);
		if (write_with_thread(philo, "has taken a fork", 2, 0) == 1)
			break ;
		if (write_with_thread(philo, "is eating", 2, 1) == 1)
			break ;
		pthread_mutex_unlock(&philo->rules->meal_lock);
		philo->meals_eaten++;
		if (timer(philo->rules->time_to_eat, philo, 2) == 1)
			break ;
		pthread_mutex_unlock(&philo->rules->fork_id[philo->left_fork]);
		philo->rules->fork_taken[philo->left_fork] = 0;
		pthread_mutex_unlock(&philo->rules->fork_id[philo->right_fork]);
		philo->rules->fork_taken[philo->right_fork] = 0;
		if (write_with_thread(philo, "is sleeping", 0, 0) == 1)
			break ;
		if (timer(philo->rules->time_to_sleep, philo, 0) == 1)
			break ;
		if (write_with_thread(philo, "is thinking", 0, 0) == 1)
			break ;
	}
}

void	*process_simulation(void *param)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)param;
	meal_refresh(philo);
	if (philo->left_fork == philo->right_fork)
	{
		write_with_thread(philo, "has taken a fork", 0, 0);
		timer(philo->rules->time_to_die, philo, 0);
		while (philo->rules->philo_died == 0)
			usleep(300);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		timer(philo->rules->time_to_eat, philo, 2);
	thread_loop(philo);
	return (NULL);
}*/

/*int	write_with_thread(t_philo_data *philo, char *message, int status, int eat)
{
	long	current_time;

	current_time = get_current_time();
	if (death_monitor(philo, status) == 1)
		return (1);
	pthread_mutex_lock(&philo->rules->write_lock);
	if (eat == 1)
		philo->time_since_last_meal = get_current_time();
	printf("%ld %d %s\n", (current_time - philo->time_since_start), \
	philo->philo_id + 1, message);
	pthread_mutex_unlock(&philo->rules->write_lock);
	return (0);
}*/

int	mutexunlock(t_philo_data *philo, pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		error(NULL, "Mutex unlock failed");
		return (1);
	}
	return (0);
}

int	mutexlock(t_philo_data *philo, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		error(NULL, "Mutex lock failed");
		return (1);
	}
	return (0);
}

void	meal_refresh(t_philo_data *philo)
{
	mutexlock(philo, &philo->meal_lock);
	philo->time_since_last_meal = get_current_time();
	philo->meals_eaten++;
	mutexunlock(philo, &philo->meal_lock);
}

void	write_with_thread(t_philo_data *philo, char *message)
{
	long	current_time;

	current_time = get_current_time();
	mutexlock(philo, &philo->rules->write_lock);
	printf("%ld %d %s\n", (current_time - philo->time_since_start), \
	philo->philo_id + 1, message);
	mutexunlock(philo, &philo->rules->write_lock);
}
int	check_death(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_count)
	{
		mutexlock(&rules->philo_data[i], &rules->meal_lock);
		if (get_current_time() - rules->philo_data[i].time_since_last_meal \
		> rules->time_to_die)
		{
			mutexunlock(&rules->philo_data[i], &rules->meal_lock);
			mutexlock(&rules->philo_data[i], &rules->monitor);
			if (rules->philo_died == 0)
			{
				rules->philo_died = 1;
				mutexunlock(&rules->philo_data[i], &rules->monitor);
				write_with_thread(&rules->philo_data[i], "died");
			}
			return (1);
		}
		mutexunlock(&rules->philo_data[i], &rules->meal_lock);
		i++;
	}
	return (0);
}

int	odd_forks(t_philo_data *philo)
{
	mutexlock(philo, &philo->rules->fork_lock);
	if (philo->rules->fork_taken[philo->left_fork] == 0)
	{
		philo->rules->fork_taken[philo->left_fork] = 1;
		mutexlock(philo, &philo->rules->fork_id[philo->left_fork]);
	}
	if (philo->rules->fork_taken[philo->right_fork] == 0)
	{
		philo->rules->fork_taken[philo->right_fork] = 1;
		mutexlock(philo, &philo->rules->fork_id[philo->right_fork]);
	}
	if (philo->rules->fork_taken[philo->left_fork] == 1 && \
	philo->rules->fork_taken[philo->right_fork] == 1)
	{
		mutexunlock(philo, &philo->rules->fork_lock);
		return (1);
	}
	mutexunlock(philo, &philo->rules->fork_lock);
	return (0);
}

int	forks_taken(t_philo_data *philo)
{
	mutexlock(philo, &philo->rules->fork_lock);
	if (philo->rules->fork_taken[philo->left_fork] == 1)
	{
		if (philo->rules->fork_taken[philo->right_fork] == 1)
			return (1);
	}
	mutexunlock(philo, &philo->rules->fork_lock);
	return (0);
}

int take_forks(t_philo_data *philo)
{
	t_rules	*rules;

	if (rules->odd_sync == 1)
	{
		if (!forks_taken(philo)) // we might want to change this to smell for a gap when all forks are available
		{
			while (!check_death(philo->rules))
			{
				if (odd_forks(philo))
					return (1);
				usleep(100);
			}
		}
	}
	return (even_forks(philo));
}

int	wait_forks(t_philo_data *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		write_with_thread(philo, "has taken a fork");
		if (timer(philo->rules->time_to_die + 100))
			return (1);
	}
	while (!check_death(philo->rules))
	{
		if (take_forks(philo))
			break ;
		usleep(300);
	}
	if (check_death(philo->rules))
		return (1);
	return (0);
}

int	eat_loop(t_philo_data *philo)
{
	if (!wait_forks(philo))
	{
		lay_forks(philo);
		return (1);
	}
	meal_refresh(philo);
	write_with_thread(philo, "is eating");
	if (timer(philo->rules->time_to_eat))
	{
		write_with_thread(philo, "died");
		return (1);
	}
	return (0);
}

void	*process_simulation(void *param)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)param;
	meal_refresh(philo);
	if (philo->philo_id % 2 == 0)
	{
		write_with_thread(philo, "is thinking");
		if (timer(philo->rules->time_to_eat - 5))
			write_with_thread(philo, "died");
	}
	while (!check_death(philo->rules))
	{
		if (eat_loop(philo))
			break ;
		write_with_thread(philo, "is sleeping");
		lay_forks(philo);
		if (timer(philo->rules->time_to_sleep))
			write_with_thread(philo, "died");
		write_with_thread(philo, "is thinking");
	}
	free(philo);
	return (NULL);
}
