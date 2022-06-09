# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 09:27:22 by rbony             #+#    #+#              #
#    Updated: 2022/06/09 14:59:22 by rbony            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = 	ft_strchr.c 	\
		ft_substr.c 	\
		ft_strjoin_cmd.c 	\
		ft_strlen.c 	\
		ft_strcmp.c 	\
		ft_strcat.c		\
		ft_split.c		\
		ft_strcpy.c		\
		ft_memset.c		\
		ft_realloc.c	\
		ft_memcpy.c		\
		ft_tolower.c	\
		ft_isalnum.c	\
		ft_isdigit.c	\
		ft_strdup.c		\
		ft_strncmp.c	\
		ft_cmd_split.c	\
		ft_src_split.c	\
		ft_isoperator.c	\
		ft_itoa.c		\
		ft_putstr_fd.c	\
		ft_strncat.c	\
		ft_strjoin.c	\
		ft_atoi.c		\
		ft_atol.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

INCLUDES = libft.h

CC = gcc
RM = rm -f

FLAGS = -Wall -Wextra -Werror

%.o : %.c ${INCLUDES} Makefile
	${CC} ${FLAGS} -I includes -c $< -o ${<:.c=.o}

$(NAME): ${OBJS} 
	ar rcs ${NAME} ${OBJS} 

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all
         
.PHONY: all clean fclean re bonus