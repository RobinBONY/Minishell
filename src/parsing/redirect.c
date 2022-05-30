/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:19:37 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/30 14:53:02 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_redirects(t_executor *exec, t_source **source, t_env *env)
{
	t_source	*tmp;

	tmp = *source;
	while (tmp)
	{
		if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, "<<") == 0)
		{
			if (find_heredocs(exec, source))
				return (1);
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
	if (exec->input == -1 || exec->output == -1)
		return (1);
	return (0);
}

void	set_infile(t_cmd *cmd, int infile)
{
	if (infile)
		dup2(infile, STDIN_FILENO);
	dup2(cmd->next->pipex[1], STDOUT_FILENO);
	close(cmd->next->pipex[0]);
	close(cmd->pipex[0]);
	close(cmd->pipex[1]);
	close_pipes_fromfirst(cmd->next);
	if (!cmd->path)
	{
		close(infile);
		close(cmd->next->pipex[1]);
	}
}

void	set_outfile(t_cmd *cmd, int outfile)
{
	if (outfile)
		dup2(outfile, STDOUT_FILENO);
	dup2(cmd->pipex[0], STDIN_FILENO);
	close(cmd->pipex[1]);
	close_pipes_fromlast(cmd);
	if (cmd->index == 2)
		close(cmd->pipex[0]);
	if (!cmd->path)
		close(cmd->pipex[0]);
}

void	set_both(int infile, int outfile)
{
	if (infile)
		dup2(infile, STDIN_FILENO);
	if (outfile)
		dup2(outfile, STDOUT_FILENO);
}
