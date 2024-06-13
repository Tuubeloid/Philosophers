/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:49:36 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/13 16:14:46 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	count = 0;
	temp = lst;
	if (lst == NULL)
		return (0);
	while (temp -> next != 0)
	{
		temp = temp->next;
		count++;
	}
	if (temp -> next == 0)
		count++;
	return (count);
}
