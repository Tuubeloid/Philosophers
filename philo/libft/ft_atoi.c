/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:16:39 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/15 13:55:00 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	result;
	size_t	max;
	int		sign;

	result = 0;
	max = 0 - 1;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if ((size_t)result > max / 10 - (*str - '0') && sign == 1)
			return (-1);
		if ((size_t)result > max / 10 - (*str - '0') && sign == -1)
			return (0);
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}
