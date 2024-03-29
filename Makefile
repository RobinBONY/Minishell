# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/28 08:34:54 by rbony             #+#    #+#              #
#    Updated: 2022/05/25 14:39:08 by rbony            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	src/main.c	\
		src/builtins/cd.c	\
		src/builtins/echo.c	\
		src/builtins/env_utils.c	\
		src/builtins/env.c	\
		src/builtins/export_utils.c	\
		src/builtins/export.c	\
		src/builtins/signals.c	\
		src/builtins/sort_export.c	\
		src/builtins/unset.c	\
		src/execution/execution.c	\
		src/execution/heredoc.c	\
		src/execution/pipes.c	\
		src/execution/place_env_var.c	\
		src/execution/quotes.c	\
		src/parsing/cmd.c	\
		src/parsing/cmd_utils.c	\
		src/parsing/executor.c	\
		src/parsing/files_utils.c	\
		src/parsing/files.c	\
		src/parsing/heredoc_utils.c	\
		src/parsing/pre_check.c	\
		src/parsing/redirect.c	\
		src/parsing/source.c	\
		src/parsing/source_utils.c

OBJS = ${SRCS:.c=.o}

HEADERS = 	minishell.h \
			source.h \
			scanner.h \
			parser.h \
			node.h \
			executor.h

CC = gcc -g -fsanitize=address
RM = rm -f

FLAGS = -Wall -Wextra -Werror

all: lib ${NAME}

$(NAME): ${OBJS}
	${CC} ${OBJS} -lreadline -I./readline/include -L./readline/lib -lncurses src/libft/libft.a -o ${NAME}

%.o : %.c ${HEADERS} Makefile
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS}
	make clean -C src/libft

fclean:	clean
	${RM} ${NAME}
	make fclean -C src/libft

re:	fclean all

lib:
	make -C src/libft

.PHONY: all clean fclean re 
