/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:16:05 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/16 19:54:14 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	cpy_len;
	size_t	copied;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	dstlen = 0;
	srclen = 0;
	while (src[srclen])
		srclen++;
	while (dst[dstlen] && dstsize > dstlen)
		dstlen++;
	if (dstsize <= dstlen)
		return (dstlen + srclen);
	cpy_len = (dstsize - dstlen - 1);
	copied = 0;
	while (copied < cpy_len && src[copied] != '\0')
	{
		dst[dstlen] = src[copied];
		copied++;
		dstlen++;
	}
	dst[dstlen] = '\0';
	return (dstlen + srclen - copied);
}
