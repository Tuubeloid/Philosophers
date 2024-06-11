/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:16:14 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/13 16:17:41 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join_helper(char const *s1, char const *s2, char *joined_str)
{
	size_t	i;

	i = 0;
	while (*s1)
	{
		joined_str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		joined_str[i] = *s2;
		i++;
		s2++;
	}
	joined_str[i] = '\0';
	return (joined_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	allocation_size;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *) s2);
	if (s2 == NULL)
		return ((char *) s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	allocation_size = s1_len + s2_len;
	i = 0;
	joined_str = (char *)malloc ((allocation_size + 1) * sizeof(char));
	if (joined_str == NULL)
		return (NULL);
	ft_join_helper(s1, s2, joined_str);
	return (joined_str);
}
