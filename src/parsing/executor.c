/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:11:42 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/02 12:01:15 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exit(char *ex_no)
{
	g_exit = ft_atoi(ex_no);
	exit(ft_atoi(ex_no));
}

int	is_builtin(char *cmd)
{
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

void	*free_executor(t_executor **exec)
{
	t_heredoc	*doctmp;
	t_cmd		*cmdtmp;

	doctmp = (*exec)->heredocs;
	cmdtmp = (*exec)->commands;
	while ((*exec)->heredocs)
	{
		doctmp = (*exec)->heredocs->next;
		free((*exec)->heredocs->str);
		free((*exec)->heredocs);
		(*exec)->heredocs = doctmp;
	}
	while ((*exec)->commands)
	{
		cmdtmp = (*exec)->commands->next;
		free((*exec)->commands->path);
		free_params((*exec)->commands->argv);
		free((*exec)->commands);
		(*exec)->commands = cmdtmp;
	}
	free(*exec);
	return (NULL);
}

t_executor	*make_executor(t_source	*source, t_env *env)
{
	t_executor	*executor;

	executor = malloc(sizeof(t_executor));
	if (!executor)
		return (NULL);
	executor->input = 0;
	executor->output = 0;
	executor->heredocs = NULL;
	executor->commands = NULL;
	if (find_redirects(executor, &source, env))
		return (free_executor(&executor));
	if (place_env_var(source, env->head_var))
		return (free_executor(&executor));
	if (make_commands(executor, &source, env))
		return (free_executor(&executor));
	return (executor);
}
