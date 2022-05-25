/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:18:38 by rbony             #+#    #+#             */
/*   Updated: 2022/05/25 16:29:05 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	execbltin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->path, "echo") == 0)
		ft_echo(cmd->argv);
	if (ft_strcmp(cmd->path, "cd") == 0)
		ft_cd(cmd->path, env->head_var);
	if (ft_strcmp(cmd->path, "pwd") == 0)
		ft_pwd(env->head_var);
	if (ft_strcmp(cmd->path, "env") == 0)
		print_env(env->head_var);
	if (ft_strcmp(cmd->path, "export") == 0)
		print_export(env->head_exp);
	if (ft_strcmp(cmd->path, "unset") == 0)
		ft_unset(env->head_exp, env->head_var, cmd->argv[1]);
	return (0);
}

static void	external_redirections(t_cmd *cmd, t_env *env, t_executor *exec)
{
	if (!cmd->prev && !cmd->next)
		set_both(exec->input, exec->output);
	else if (!cmd->prev)
		set_infile(cmd, exec->input);
	else if (!cmd->next)
		set_outfile(cmd, exec->output);
	if (cmd->is_builtin)
		execbltin(cmd, env);
	else
		execve(cmd->path, cmd->argv, NULL);
	exit(0);
}

static void	execute_cmd(t_cmd *cmd, t_env *env, t_executor *exec)
{
	ft_heredoc(env->head_var, exec);
	if (!cmd->prev || !cmd->next)
	{
		external_redirections(cmd, env, exec);
	}
	else
	{
		dup2(cmd->pipex[0], STDIN_FILENO);
		dup2(cmd->next->pipex[1], STDOUT_FILENO);
		close(cmd->pipex[1]);
		close(cmd->next->pipex[0]);
		close_pipes_fromfirst(cmd->next);
		close_pipes_fromlast(cmd);
		if (cmd->index == 2)
			close(cmd->pipex[0]);
		if (!cmd->path)
			close(cmd->pipex[0]);
		if (cmd->is_builtin)
			execbltin(cmd, env);
		else
			execve(cmd->path, cmd->argv, NULL);
		exit(0);
	}
}

void	execution(t_env *env, t_executor *exec)
{
	t_cmd	*tmp;

	if (ft_lstsize(exec->commands) > 1)
	{
		if (open_pipes(&exec->commands))
			return ;
	}
	tmp = exec->commands;
	while (tmp)
	{
		tmp->pid = fork();
		if (tmp->pid < 0)
			return ;
		if (tmp->pid == 0)
			execute_cmd(tmp, env, exec);
		tmp = tmp->next;
	}
	tmp = exec->commands;
	if (ft_lstsize(exec->commands) > 1)
		close_pipes_fromfirst(tmp);
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
}
