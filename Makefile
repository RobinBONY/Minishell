# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/28 08:34:54 by rbony             #+#    #+#              #
#    Updated: 2022/04/06 15:02:44 by alakhdar         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	src/main.c \
		src/prompt.c 		\
		src/ft_cmd_split.c 	\
		src/errors.c		\
		src/place_env_var.c \
		src/pre_checking.c  \
		src/builtins/env_utils.c \
		src/builtins/env.c 
		

OBJS = ${SRCS:.c=.o}

HEADERS = minishell.h

CC = gcc -g #-fsanitize=address
RM = rm -f

FLAGS = -Wall -Wextra -Werror

all: lib ${NAME}

$(NAME): ${OBJS}
	${CC} ${OBJS} -lreadline -I./readline/include -L./readline/lib -lncurses libft/libft.a -o ${NAME}

%.o : %.c ${HEADERS} Makefile
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS}
	make clean -C libft

fclean:	clean
	${RM} ${NAME}
	make fclean -C libft

re:	fclean all

lib:
	make bonus -C libft

.PHONY: all clean fclean re 
