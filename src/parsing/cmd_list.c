/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:11:42 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/08 14:28:37 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	is_local(char *cmd, char **argv)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0 && argv[1])
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	get_len(t_source *source)
{
	int	i;

	i = 0;
	while (source)
	{
		if (source->used)
			i++;
		source = source->next;
	}
	return (i);
}

void	*free_executor(t_cmd *exec)
{
	t_heredoc	*doctmp;
	t_cmd		*cmdtmp;

	while (exec)
	{
		if (exec->input)
			close(exec->input);
		if (exec->output)
			close(exec->output);
		doctmp = exec->heredocs;
		while (exec->heredocs)
		{
			doctmp = exec->heredocs->next;
			free(exec->heredocs->str);
			free(exec->heredocs);
			exec->heredocs = doctmp;
		}
		cmdtmp = exec->next;
		free(exec->path);
		free_params(exec->argv);
		free(exec);
		exec = cmdtmp;
	}
	return (NULL);
}

t_cmd	*make_executor(t_source	*source, t_env *env)
{
	t_cmd		*executor;
	t_source	*tmp;

	executor = NULL;
	tmp = NULL;
	while (source)
	{
		while (source && ft_strcmp(source->str, "|"))
			ft_push(&source, &tmp);
		if (source)
		{
			source->used = 0;
			ft_push(&source, &tmp);
		}
		ft_cmdadd_back(&executor, make_command(&tmp, env,
				ft_lstlast(executor)));
		ft_srcclear(&tmp);
	}
	find_all_path(env->head_var, executor);
	index_commands(executor);
	if (!executor)
		return (NULL);
	return (executor);
}
