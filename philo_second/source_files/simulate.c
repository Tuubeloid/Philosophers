/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:33:50 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/17 14:37:33 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	mutexunlock(t_philo_data *philo, pthread_mutex_t *mutex)
{
	(void)philo;
	if (pthread_mutex_unlock(mutex) != 0)
	{
		error(NULL, "Mutex unlock failed");
		return (1);
	}
	return (0);
}

int	mutexlock(t_philo_data *philo, pthread_mutex_t *mutex)
{
	(void)philo;
	if (pthread_mutex_lock(mutex) != 0)
	{
		error(NULL, "Mutex lock failed");
		return (1);
	}
	return (0);
}

void	meal_refresh(t_philo_data *philo)
{
	mutexlock(philo, &philo->rules->meal_lock);
	philo->time_since_last_meal = get_current_time();
	philo->meals_eaten++;
	mutexunlock(philo, &philo->rules->meal_lock);
}

void	write_with_thread(t_philo_data *philo, char *message)
{
	long	current_time;

	current_time = get_current_time();
	mutexlock(philo, &philo->rules->write_lock);
	if (philo->rules->write_lock_locked == 1)
	{
		mutexunlock(philo, &philo->rules->write_lock);
		return ;
	}
	printf("%ld %d %s\n", (current_time - philo->time_since_start), \
	philo->philo_id + 1, message);
	if (ft_strncmp(message, "died", ft_strlen(message)) == 0)
	{
		philo->rules->philo_died = 1;
		philo->rules->write_lock_locked = 1;
		mutexunlock(philo, &philo->rules->write_lock);
		return ;
	}
	mutexunlock(philo, &philo->rules->write_lock);
}
int	check_death(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_count)
	{
		pthread_mutex_lock(&rules->monitor);
		if (rules->philo_died == 1)
		{
			pthread_mutex_unlock(&rules->monitor);
			return (1);
		}
		pthread_mutex_unlock(&rules->monitor);
		i++;
	}
	return (0);
}

void	lay_forks(t_philo_data *philo)
{
	mutexlock(philo, &philo->rules->fork_lock);
	if (philo->has_left == 1)
	{
		mutexunlock(philo, &philo->rules->fork_id[philo->left_fork]);
		philo->has_left = 0;
		philo->rules->fork_taken[philo->left_fork] = 0;
	}
	if (philo->has_right == 1)
	{
		mutexunlock(philo, &philo->rules->fork_id[philo->right_fork]);
		philo->has_right = 0;
		philo->rules->fork_taken[philo->right_fork] = 0;
	}
	mutexunlock(philo, &philo->rules->fork_lock);
}

int	even_forks(t_philo_data *philo)
{
	mutexlock(philo, &philo->rules->fork_lock);
	if (philo->rules->fork_taken[philo->left_fork] == 0)
	{
		if (philo->rules->fork_taken[philo->right_fork] == 0)
		{
			philo->rules->fork_taken[philo->left_fork] = 1;
			philo->has_left = 1;
			mutexlock(philo, &philo->rules->fork_id[philo->left_fork]);
			philo->rules->fork_taken[philo->right_fork] = 1;
			philo->has_right = 1;
			mutexlock(philo, &philo->rules->fork_id[philo->right_fork]);
			mutexunlock(philo, &philo->rules->fork_lock);
			write_with_thread(philo, "has taken a fork");
			write_with_thread(philo, "has taken a fork");
			return (1);
		}
	}
	mutexunlock(philo, &philo->rules->fork_lock);
	return (0);
}

int	odd_forks(t_philo_data *philo)
{
	mutexlock(philo, &philo->rules->fork_lock);
	if (philo->rules->fork_taken[philo->left_fork] == 0)
	{
		philo->rules->fork_taken[philo->left_fork] = 1;
		philo->has_left = 1;
		write_with_thread(philo, "has taken a fork");
		mutexlock(philo, &philo->rules->fork_id[philo->left_fork]);
	}
	if (philo->rules->fork_taken[philo->right_fork] == 0)
	{
		philo->rules->fork_taken[philo->right_fork] = 1;
		philo->has_right = 1;
		write_with_thread(philo, "has taken a fork");
		mutexlock(philo, &philo->rules->fork_id[philo->right_fork]);
	}
	if (philo->has_left == 1 && philo->has_right == 1)
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
	if (philo->has_left == 1 && philo->has_right == 1)
	{
		mutexunlock(philo, &philo->rules->fork_lock);
		return (1);
	}
	mutexunlock(philo, &philo->rules->fork_lock);
	return (0);
}

int take_forks(t_philo_data *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	if (rules->odd_sync == 1)
	{
		if (!forks_taken(philo))
		{
			while (!check_death(philo->rules))
			{
				if (odd_forks(philo))
					return (1);
				//usleep(100);
			}
		}
	}
	if (!check_death(philo->rules))
		return (even_forks(philo));
	return (0);
}

int	wait_forks(t_philo_data *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		write_with_thread(philo, "has taken a fork");
		if (timer(philo->rules->time_to_die, philo))
			return (1);
	}
	while (!check_death(philo->rules))
	{
		if (take_forks(philo))
			break ;
		//usleep(100);
	}
	return (check_death(philo->rules));
}

int	eat_loop(t_philo_data *philo)
{
	if (philo->rules->all_fed == 1)
	{
		lay_forks(philo);
		return (1);
	}
	if (wait_forks(philo))
	{
		lay_forks(philo);
		return (1);
	}
	write_with_thread(philo, "is eating");
	meal_refresh(philo);
	if (timer(philo->rules->time_to_eat, philo))
		return (1);
	return (0);
}

void	*process_simulation(void *param)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)param;
	philo->time_since_last_meal = get_current_time();
	if ((philo->philo_id + 1 ) % 2 == 0)
	{
		write_with_thread(philo, "is thinking");
		if (timer(philo->rules->time_to_eat, philo))
			write_with_thread(philo, "died 1");
	}
	while (!check_death(philo->rules))
	{
		if (eat_loop(philo))
			break ;
		write_with_thread(philo, "is sleeping");
		lay_forks(philo);
		if (timer(philo->rules->time_to_sleep, philo))
			break ;
		write_with_thread(philo, "is thinking");
	}
	lay_forks(philo);
	philo->rules->threads_running--;
	return (NULL);
}
