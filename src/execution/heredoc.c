/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:12:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 13:35:41 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

//Expand les var d'environnement dans le heredoc
// SI entre double quotes / sans quotes
// Ne pas expand si simple quotes
// Ne pas expand si quotes dans délimiteur