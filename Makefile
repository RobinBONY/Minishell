NAME = Minishell
SRCS		= 	src/main.c src/builtins/echo.c
HEADER		=	includes/minishell.h
OBJS		= ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -rf

all: lib ${NAME}

$(NAME) : ${SRCS} $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(SRCS) libft/libft.a -o ${NAME}
	@echo "\033[92m\n[- COMPILATION COMPLETE -]\n\033[0m"

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

lib:
	@make -C libft

clean :
	$(RM) Minishell
	$(RM) src/*.o
	$(RM) libft/*.o
	@echo "\033[91m\n[- FILES DELETED -]\n\033[0m"

fclean : clean

re : fclean all

.PHONY : all clean bonus fclean re