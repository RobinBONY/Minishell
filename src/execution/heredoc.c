/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:12:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/08 15:29:50 by rbony            ###   ########lyon.fr   */
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

static char	*replace_var_heredoc(char *str, t_var *head)
{
	int		len;
	char	*tmp;

	tmp = str;
	if (!ft_strchr(str, '$') && *tmp != '$')
		return (str);
	while (*tmp != '$')
		tmp++;
	len = get_type(tmp);
	if (len == -1)
		return (last_exit(str, tmp - str));
	if (len > 1)
		return (replace_string(str, tmp - str, len,
				find_var(tmp + 1, head)));
	return (str);
}

static void	launch_heredoc(t_heredoc *tmp, t_var *env, int fd)
{
	int			expand;
	char		*heredoc;

	heredoc_signals();
	expand = is_expand(tmp);
	while (tmp)
	{
		heredoc = readline("> ");
		if (!heredoc)
			exit(1);
		if (ft_strcmp(heredoc, tmp->str) == 0)
		{
			tmp = tmp->next;
			expand = is_expand(tmp);
		}
		else if (heredoc[0])
		{
			if (expand)
				ft_putstr_fd(replace_var_heredoc(heredoc, env), fd);
			else
				ft_putstr_fd(heredoc, fd);
			ft_putstr_fd("\n", fd);
		}
	}
	exit(0);
}

int	ft_heredoc(t_var *env, t_cmd *exec)
{
	int			fd;
	int			pid;

	while (exec)
	{
		if (exec->heredocs)
		{
			fd = open("/tmp/.heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0664);
			if (fd == -1)
				return (1);
			signal(SIGINT, SIG_IGN);
			pid = fork();
			if (pid < 0)
				return (1);
			else if (pid == 0)
				launch_heredoc(exec->heredocs, env, fd);
			waitpid(pid, &g_exit, 0);
			main_signals();
			close(fd);
			if (WIFEXITED(g_exit))
				return (WEXITSTATUS(g_exit));
		}
		exec = exec->next;
	}
	return (0);
}
