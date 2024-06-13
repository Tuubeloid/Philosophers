/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:12:13 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/13 21:12:55 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlelen;

	if (haystack == 0 && len == 0)
		return ((char *)haystack);
	if (*needle == '\0')
		return ((char *)haystack);
	needlelen = ft_strlen(needle);
	while (*haystack != '\0' && needlelen <= len)
	{
		if (ft_strncmp(haystack, needle, needlelen) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
