/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:12:11 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/17 21:18:35 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_arr(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		free((void *)s[i++]);
	free(s);
	return (0);
}

static size_t	ft_count_items(const char *s, char c)
{
	size_t	i;
	size_t	items;

	items = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') == 1
			&& (s[i] == c || s[i] == '\0') == 0)
			items++;
		i++;
	}
	return (items);
}

static void	ft_copy_string(char *new_arr, char const *s, char c)
{
	size_t	i;

	i = 0;
	while ((s[i] == c || s[i] == '\0') == 0)
	{
		new_arr[i] = s[i];
		i++;
	}
	new_arr[i] = '\0';
}

static size_t	all_by_split(char **new_arr, const char *s, char c,
size_t items)
{
	size_t	i;
	size_t	j;
	size_t	word;

	word = 0;
	i = 0;
	while (s[i] != '\0' && word < items)
	{
		while ((s[i] == c || s[i] == '\0') == 1)
			i++;
		j = 0;
		while ((s[i + j] == c || s[i + j] == '\0') == 0)
			j++;
		new_arr[word] = (char *) malloc(sizeof(char) * (j + 1));
		if (new_arr[word] == NULL)
		{
			ft_free_arr(new_arr);
			return (0);
		}
		ft_copy_string(new_arr[word], s + i, c);
		i += j;
		word++;
	}
	new_arr[word] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**new_arr;
	size_t	items;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	items = ft_count_items(s, c);
	new_arr = (char **)malloc((items + 1) * sizeof(char *));
	if (new_arr == NULL)
		return (0);
	if (all_by_split(new_arr, s, c, items) == 0)
		return (0);
	return (new_arr);
}
