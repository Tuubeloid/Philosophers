/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:43:47 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/13 16:14:58 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		d;
	const unsigned char	*big;
	size_t				i;

	d = (unsigned char)c;
	big = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (big[i] == d)
		{
			return ((void *)(big + i));
		}
		i++;
	}
	return (NULL);
}
