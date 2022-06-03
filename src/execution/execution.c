/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:18:38 by rbony             #+#    #+#             */
/*   Updated: 2022/06/03 16:18:50 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	execbltin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->path, "echo") == 0)
		return (ft_echo(cmd->argv));
	if (ft_strcmp(cmd->path, "cd") == 0)
		return (ft_cd(cmd->argv[1], env->head_var));
	if (ft_strcmp(cmd->path, "pwd") == 0)
		return (ft_pwd(env->head_var));
	if (ft_strcmp(cmd->path, "env") == 0)
		return (print_env(env->head_var));
	if (ft_strcmp(cmd->path, "export") == 0)
	{
		if (cmd->argv[1] == 0)
			return (print_export(env->head_exp));
		else
		{
			append_to_exp(env->head_exp, cmd->argv[1]);
			sort_export(env->head_exp);
			append_to_list(env->head_var, cmd->argv[1]);
			return (0);
		}
	}
	if (ft_strcmp(cmd->path, "unset") == 0)
		return (ft_unset(env->head_exp, env->head_var, cmd->argv[1]));
	if (ft_strcmp(cmd->path, "exit") == 0)
		ft_exit(cmd->argv[1]);
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
		exit (execbltin(cmd, env));
	else
		execve(cmd->path, cmd->argv, env->envp);
	cmd_not_found(cmd->argv[0]);
	exit(1);
}

static void	execute_cmd(t_cmd *cmd, t_env *env, t_executor *exec)
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
			exit(execbltin(cmd, env));
		else
			execve(cmd->path, cmd->argv, env->envp);
		cmd_not_found(cmd->argv[0]);
		exit(1);
	}
}

static void	out_execution(t_env *env, t_executor *exec)
{
	t_cmd	*tmp;

	if (open_pipes(&exec->commands))
		return ;
	tmp = exec->commands;
	while (tmp)
	{
		child_signals();
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
		waitpid(tmp->pid, &g_exit, 0);
		tmp = tmp->next;
	}
	main_signals();
}

void	execution(t_env *env, t_executor *exec)
{
	t_cmd	*tmp;

	tmp = exec->commands;
	if (ft_heredoc(env->head_var, exec))
		return ;
	if (ft_lstsize(exec->commands) > 1)
		out_execution (env, exec);
	else if (tmp && tmp->is_local)
		g_exit = execbltin(tmp, env);
	else if (tmp)
	{
		child_signals();
		tmp->pid = fork();
		if (tmp->pid < 0)
			return ;
		if (tmp->pid == 0)
			execute_cmd(tmp, env, exec);
		waitpid(tmp->pid, &g_exit, 0);
		main_signals();
	}
}
