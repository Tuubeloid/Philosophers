/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:08:41 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/13 16:31:21 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	d;
	unsigned char	*e;

	d = c;
	e = b;
	i = 0;
	while (i < len)
	{
		e[i] = d;
		i++;
	}
	return (b);
}
