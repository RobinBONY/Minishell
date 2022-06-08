/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:19:37 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/08 10:53:26 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_redirects(t_cmd *exec, t_source **source, t_env *env)
{
	t_source	*tmp;

	tmp = *source;
	while (tmp)
	{
		if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, "<<") == 0)
		{
			if (find_heredocs(exec, &tmp))
				return (1);
			exec->input = open_infile("/tmp/.heredoc");
		}
		if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, "<") == 0)
			set_input(exec, tmp, env);
		else if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, ">") == 0)
			set_output(exec, tmp, 0, env);
		else if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, ">>") == 0)
			set_output(exec, tmp, 1, env);
		tmp = tmp->next;
	}
	return (check_redirects(exec));
}

void	set_redirect_first(t_cmd *cmd)
{
	if (cmd->input)
		dup2(cmd->input, STDIN_FILENO);
	if (cmd->output)
	{
		dup2(cmd->output, STDOUT_FILENO);
		close(cmd->next->pipex[1]);
	}
	else
		dup2(cmd->next->pipex[1], STDOUT_FILENO);
	close(cmd->next->pipex[0]);
	close(cmd->pipex[0]);
	close(cmd->pipex[1]);
	close_pipes_fromfirst(cmd->next);
	if (!cmd->is_builtin && access(cmd->path, X_OK) == -1)
	{
		close(cmd->input);
		close(cmd->next->pipex[1]);
	}
}

void	set_redirect_last(t_cmd *cmd)
{
	if (cmd->output)
		dup2(cmd->output, STDOUT_FILENO);
	if (cmd->input)
	{
		dup2(cmd->input, STDIN_FILENO);
		close(cmd->pipex[0]);
	}
	else
		dup2(cmd->pipex[0], STDIN_FILENO);
	close(cmd->pipex[1]);
	close_pipes_fromlast(cmd);
	if (cmd->index == 2)
		close(cmd->pipex[0]);
	if (!cmd->path)
		close(cmd->pipex[0]);
}

void	set_redirect(t_cmd *cmd)
{
	if (cmd->input)
	{
		dup2(cmd->input, STDIN_FILENO);
		close(cmd->pipex[0]);
	}
	else
		dup2(cmd->pipex[0], STDIN_FILENO);
	if (cmd->output)
	{
		dup2(cmd->output, STDOUT_FILENO);
		close(cmd->next->pipex[1]);
	}
	else
		dup2(cmd->next->pipex[1], STDOUT_FILENO);
	close(cmd->pipex[1]);
	close(cmd->next->pipex[0]);
	close_pipes_fromfirst(cmd->next);
	close_pipes_fromlast(cmd);
	if (cmd->index == 2)
		close(cmd->pipex[0]);
	if (!cmd->is_builtin && access(cmd->path, X_OK) == -1)
		close(cmd->pipex[0]);
}

void	set_redirect_solobolo(t_cmd *cmd)
{
	if (cmd->input)
		dup2(cmd->input, STDIN_FILENO);
	if (cmd->output)
		dup2(cmd->output, STDOUT_FILENO);
}
