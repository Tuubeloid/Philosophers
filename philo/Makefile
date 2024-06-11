# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 11:09:42 by tvalimak          #+#    #+#              #
#    Updated: 2024/06/11 17:15:14 by tvalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=thread -static-libsan
SRCDIR = source_files
OBJDIR = object_files
LIBFTDIR = libft
GNLDIR	 = ./libft/get_next_line/

GNL = $(LIBFTDIR)/get_next_line/gnl.a
LIBFT = $(LIBFTDIR)/libft.a

SRCS =	$(SRCDIR)/error.c \
		$(SRCDIR)/init.c \
		$(SRCDIR)/parse.c \
		$(SRCDIR)/philo.c \
		$(SRCDIR)/simulate.c \
		$(SRCDIR)/threads.c \
		$(SRCDIR)/time.c \
		$(SRCDIR)/threads_helper.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RLFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(GNL):
	@$(MAKE) -C $(GNLDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

sanitize : $(OBJS) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(LIBFT) $(GNL) -o $(NAME) $(RLFLAGS)

clean:
	make fclean -C $(LIBFTDIR)
	make fclean -C $(GNLDIR)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re sanitize