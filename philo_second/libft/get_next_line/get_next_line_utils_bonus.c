/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:58:24 by tvalimak          #+#    #+#             */
/*   Updated: 2023/12/15 18:34:37 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_terminate(t_list **dump)
{
	t_list	*current;

	while (*dump)
	{
		current = (*dump)->next;
		free ((*dump)->content);
		free(*dump);
		*dump = current;
	}
	dump = NULL;
}

void	ft_append_node(t_list **dump, t_list *new_node, char *buff)
{
	t_list	*temp;

	new_node->content = buff;
	new_node->next = NULL;
	temp = *dump;
	if (!*dump)
		*dump = new_node;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	dealloc(t_list **dump, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	clean_node->content = buf;
	clean_node->next = NULL;
	while (*dump)
	{
		tmp = (*dump)->next;
		free((*dump)->content);
		free(*dump);
		*dump = tmp;
	}
	if (clean_node->content[0])
		*dump = clean_node;
	else
	{
		free(buf);
		free(clean_node);
		free(*dump);
		dump = NULL;
		buf = NULL;
		clean_node = NULL;
	}
}

t_list	*find_last_node(t_list *dump)
{
	if (NULL == dump)
		return (NULL);
	while (dump->next)
		dump = dump->next;
	return (dump);
}

void	ft_polish_dump(t_list **dump)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	last_node = find_last_node(*dump);
	clean_node = malloc(sizeof(t_list));
	buf = malloc(BUFFER_SIZE + 1);
	if (last_node == NULL || last_node->content == NULL || \
	buf == NULL || NULL == clean_node)
	{
		free (buf);
		free (clean_node);
		ft_terminate(dump);
		return ;
	}
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[i++])
		buf[k++] = last_node->content[i];
	buf[k] = '\0';
	dealloc(dump, clean_node, buf);
}
