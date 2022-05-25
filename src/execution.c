/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:18:38 by rbony             #+#    #+#             */
/*   Updated: 2022/05/25 10:39:44 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	close_pipes_fromlast(t_cmd *cmd)
{
	while (cmd->prev)
	{
		cmd = cmd->prev;
		close(cmd->pipex[0]);
		close(cmd->pipex[1]);
	}
}

void	close_pipes_fromfirst(t_cmd *cmd)
{
	while (cmd->next)
	{
		cmd = cmd->next;
		close(cmd->pipex[0]);
		close(cmd->pipex[1]);
	}
}

int	open_pipes(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (pipe(tmp->pipex) == -1)
		{
			close_pipes_fromlast(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	error_cmd_not_found(char *cmd)
{
	char	*error;
	char	prout[1];

	prout[0] = ' ';
	if (!cmd)
		error = ft_strjoin("pipex: command not found: ", prout);
	else
		error = ft_strjoin("pipex: command not found: ", cmd);
	ft_putendl_fd(error, 1);
	free (error);
}

int	execbltin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->path, "echo") == 0)
		ft_echo(cmd->path);
	if (ft_strcmp(cmd->path, "cd") == 0)
		ft_cd(cmd->argv, env->head_var);
	if (ft_strcmp(cmd->path, "pwd") == 0)
		ft_pwd(cmd->argv, env->head_var);
	if (ft_strcmp(cmd->path, "env") == 0)
		ft_print_env(env->head_var);
	if (ft_strcmp(cmd->path, "export") == 0)
		ft_print_export(env->head_exp);
	if (ft_strcmp(cmd->path, "unset") == 0)
		ft_unset();
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

void	external_redirections(t_cmd *cmd, t_env *env, t_executor *exec)
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

void	execute_cmd(t_cmd *cmd, t_env *env, t_executor *exec)
{
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
		if (open_pipes(exec->commands))
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
	close_pipes_fromfirst(tmp);
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
}
