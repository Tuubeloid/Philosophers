/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:07:28 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/27 10:48:39 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_count(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_void_or_min(int n)
{
	if (!n)
		return (ft_strdup("0"));
	return (ft_strdup("-2147483648"));
}

char	*ft_itoa(int n)
{
	int		count;
	char	sign;
	char	*int_str;

	if (!n || n == -2147483648)
		return (ft_void_or_min(n));
	sign = 0;
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	count = ft_int_count(n);
	int_str = ft_calloc(sign + count + 1, 1);
	if (!int_str)
		return (0);
	if (sign)
		int_str[0] = '-';
	while (n)
	{
		int_str[sign + count-- - 1] = n % 10 + '0';
		n /= 10;
	}
	return (int_str);
}
