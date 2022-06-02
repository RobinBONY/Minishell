/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:12:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/02 15:16:11 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handler_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static int	is_expand(t_heredoc *tmp)
{
	if (!tmp)
		return (1);
	if (ft_strchr(tmp->str, '\'') || ft_strchr(tmp->str, '"'))
	{
		remove_quotes_heredoc(tmp);
		return (0);
	}
	return (1);
}

static void	launch_heredoc(t_heredoc *tmp, t_var *env, int fd)
{
	int			expand;
	char		*heredoc;

	expand = is_expand(tmp);
	while (tmp)
	{
		heredoc = readline(">> ");
		if (!heredoc)
			break ;
		if (ft_strcmp(heredoc, tmp->str) == 0)
		{
			tmp = tmp->next ;
			if (!tmp)
				return ;
			expand = is_expand(tmp);
		}
		else if (heredoc[0])
		{
			if (expand)
				ft_putstr_fd(replace_var(heredoc, env), fd);
			else
				ft_putstr_fd(heredoc, fd);
			ft_putstr_fd("\n", fd);
		}
	}
}

int	ft_heredoc(t_var *env, t_executor *exec)
{
	int			fd;
	int			expand;

	fd = open("/tmp/.heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd == -1)
		return (1);
	launch_heredoc(exec->heredocs, env, fd);
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	if (fd == -1)
		return (1);
	if (exec->input == 0)
		exec->input = fd;
	if (unlink("/tmp/.heredoc") == -1)
		printf("Could not delete .heredoc\n");
	return (0);
}
