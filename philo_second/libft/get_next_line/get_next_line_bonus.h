/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:56:42 by tvalimak          #+#    #+#             */
/*   Updated: 2023/12/15 18:35:36 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list			*find_last_node(t_list *dump);
void			dealloc(t_list **dump, t_list *clean_node, char *buf);
void			ft_append_node(t_list **dump, t_list *new_node, char *buff);
void			ft_polish_dump(t_list **dump);
void			ft_terminate(t_list **dump);
char			*get_next_line(int fd);
char			*cpy_str(t_list *dump, char *next_line);

#endif