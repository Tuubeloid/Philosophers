/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:20:27 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/13 16:18:49 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' && s2[i] != '\0') && i < n - 1)
	{
		if (s1[i] != s2[i])
		{
			return (((unsigned char)s1[i]) - (unsigned char)s2[i]);
		}
		i++;
	}
	if (i < n)
	{
		return (((unsigned char)s1[i]) - (unsigned char)s2[i]);
	}
	return (0);
}
