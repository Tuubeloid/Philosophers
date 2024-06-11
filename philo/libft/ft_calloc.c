/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:20:44 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/14 19:22:03 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	magic_number;

	magic_number = 0 - 1;
	if (count != 0 && size != 0)
	{
		if (magic_number / count < size)
			return (NULL);
	}
	if (count * size > 2147483424)
		return (0);
	ptr = malloc(count * size);
	if (ptr != NULL)
		ft_memset(ptr, 0, count * size);
	return (ptr);
}
