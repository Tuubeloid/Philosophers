/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:41:07 by tvalimak          #+#    #+#             */
/*   Updated: 2024/06/15 16:09:46 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	check_int_len(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) > 10)
		{
			printf("One of the arguments is overflowing\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_numeric(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf("One of the arguments is not numeric\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_if_empty(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
		{
			printf("One of the arguments is empty\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_args(int argv_int[5], char **argv, int argc)
{
	argv_int[4] = -1;
	if (check_if_empty(argv, argc) == 1)
		return (1);
	if (check_if_numeric(argv, argc) == 1)
		return (1);
	if (check_int_len(argv, argc) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int		argv_int[5];
	t_rules	*rules;

	printf("Starting simulation\n");
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong amount of arguments\n");
		return (1);
	}
	rules = (t_rules *)malloc(sizeof(t_rules));
	ft_memset(rules, 0, sizeof(t_rules));
	if (!rules)
	{
		printf("Error: Malloc failed\n");
		return (1);
	}
	if (check_args(argv_int, argv, argc) == 1)
	{
		printf("Error: Argument check failed\n");
		return (1);
	}
	parse_args(rules, argv);
	init_vars(rules);
	spawn_threads(rules);
	monitor_threads(rules);
	printf("Simulation end\n");
	return (0);
}
