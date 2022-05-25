/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:12:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 10:06:13 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include "../src/libft/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_heredoc(char *input)
{
	char	*limiter;
	char	*heredoc;
	int		fd;
	int		fd_in;

	limiter = input;
	fd = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (!fd)
		exit(0);
	while (1)
	{
		heredoc = readline(">> ");
		if (!heredoc)
			break ;
		if (ft_strcmp(heredoc, limiter) == 0)
			break ;
		if (heredoc[0])
		{
			ft_putstr_fd(heredoc, fd);
			ft_putstr_fd("\n", fd);
		}
	}
	close(fd);
	fd_in = open(".heredoc", O_RDONLY);
	return (fd_in);
}

int	main(int argc, char **argv)
{
	ft_heredoc(argv[1]);
	return (0);
}

//Expand les var d'environnement dans le heredoc
// SI entre double quotes / sans quotes
// Ne pas expand si simple quotes
// Ne pas expand si quotes dans délimiteur