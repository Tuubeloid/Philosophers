# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 18:17:29 by tvalimak          #+#    #+#              #
#    Updated: 2024/06/02 23:18:58 by tvalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlen.c \
	   ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	   ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c \
	   ft_atoi.c ft_calloc.c ft_strdup.c ft_memchr.c ft_memcmp.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_split.c ft_striteri.c ft_strmapi.c ft_putchar_fd.c ft_putnbr_fd.c \
	   ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_itoa.c \

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${BONUS:.c=.o}
NAME = libft.a
LIBC = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

all: ${NAME}

bonus : .bonus

.bonus: ${NAME} ${OBJS_BONUS}
	${LIBC} ${NAME} $?
	touch .bonus

clean:
	${RM} ${OBJS} ${OBJS_BONUS} .bonus

fclean: clean
	${RM} ${NAME} ${bonus}

re: fclean all

.PHONY: all bonus clean fclean re
