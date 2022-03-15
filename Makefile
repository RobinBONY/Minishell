# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/28 08:34:54 by rbony             #+#    #+#              #
#    Updated: 2022/03/15 17:31:34 by rbony            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	prompt.c
		

OBJS = ${SRCS:.c=.o}

HEADERS = libft.h

CC = gcc
RM = rm -f

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

$(NAME): ${OBJS}
	${CC} ${OBJS} -lreadline -I./readline/include -L./readline/lib -lncurses libft.a -o ${NAME}

%.o : %.c ${HEADERS} Makefile
	${CC} ${FLAGS} -I headers -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all
         
.PHONY: all clean fclean re 
