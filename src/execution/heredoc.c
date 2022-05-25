/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:12:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 17:07:25 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

void	ft_heredoc(t_var *env, t_executor *exec)
{
	int			fd;
	int			expand;

	fd = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (!fd)
		exit(0);
	launch_heredoc(exec->heredocs, env, fd);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (exec->input == 0)
		exec->input = fd;
}

//Expand les var d'environnement dans le heredoc
// SI entre double quotes / sans quotes
// Ne pas expand si simple quotes
// Ne pas expand si quotes dans délimiteur