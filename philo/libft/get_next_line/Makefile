# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 13:55:28 by tvalimak          #+#    #+#              #
#    Updated: 2024/05/27 13:56:01 by tvalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

SRCS = \
	get_next_line_utils.c \
	get_next_line.c \

OBJS := $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	cc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	ar -rcs $(NAME) $^ 

all: $(NAME)

clean: 
	rm -f $(OBJS)

fclean: 
	rm -f $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
