/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:50:25 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/13 16:17:18 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	d;

	d = c;
	while (*s != '\0')
	{
		if (*s == d)
		{
			return ((char *) s);
		}
		s++;
	}
	if (d == '\0')
	{
		return ((char *) s);
	}
	return (NULL);
}
