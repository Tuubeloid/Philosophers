/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:57:24 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/13 16:17:30 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(s1) + 1;
	copy = (char *) malloc(len * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, s1, len);
	return (copy);
}
