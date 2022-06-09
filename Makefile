# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/28 08:34:54 by rbony             #+#    #+#              #
#    Updated: 2022/06/09 14:59:59 by rbony            ###   ########lyon.fr    #
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
		src/builtins/signals_handlers.c	\
		src/builtins/sort_export.c	\
		src/builtins/unset.c	\
		src/execution/error.c	\
		src/execution/execution.c	\
		src/execution/heredoc.c	\
		src/execution/pipes.c	\
		src/execution/place_env_var.c	\
		src/execution/place_env_utils.c	\
		src/execution/quotes.c	\
		src/execution/ft_waitpid.c	\
		src/parsing/cmd.c	\
		src/parsing/cmd_utils.c	\
		src/parsing/cmd_list.c	\
		src/parsing/files_utils.c	\
		src/parsing/files.c	\
		src/parsing/heredoc_utils.c	\
		src/parsing/pre_check.c	\
		src/parsing/redirect.c	\
		src/parsing/source.c	\
		src/parsing/source_utils.c \
		src/parsing/make_cmd.c	\
		src/builtins/exit.c

OBJS = ${SRCS:.c=.o}

HEADERS = 	headers/minishell.h \
			readline/include/readline.h

CC = gcc -Wall -Wextra -Werror #-g -fsanitize=address
RM = rm -f

all: lib ${NAME}

$(NAME): ${OBJS}
	${CC} ${OBJS} -lreadline -I./readline/include -L./readline/lib -lncurses src/libft/libft.a -o ${NAME}

%.o : %.c ${HEADERS} Makefile
	${CC} -c $< -o ${<:.c=.o}

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
