/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:18:38 by rbony             #+#    #+#             */
/*   Updated: 2022/06/08 15:15:39 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	execbltin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->path, "echo") == 0)
		return (ft_echo(cmd->argv));
	if (ft_strcmp(cmd->path, "cd") == 0)
		return (ft_cd(cmd->argv[1], env->head_var, env->head_exp));
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
			rep_or_app_exp(env->head_exp, cmd->argv[1]);
			rep_or_app_env(env->head_var, cmd->argv[1]);
			sort_export(env->head_exp);
			return (0);
		}
	}
	if (ft_strcmp(cmd->path, "unset") == 0)
		return (ft_unset(env->head_exp, env->head_var, cmd->argv[1]));
	if (ft_strcmp(cmd->path, "exit") == 0)
		ft_exit(cmd->argv[1]);
	return (0);
}

static void	external_redirections(t_cmd *cmd, t_env *env)
{
	if (!cmd->prev && !cmd->next)
		set_redirect_solobolo(cmd);
	else if (!cmd->prev)
		set_redirect_first(cmd);
	else if (!cmd->next)
		set_redirect_last(cmd);
	if (cmd->is_builtin)
		exit (execbltin(cmd, env));
	else
		execve(cmd->path, cmd->argv, env->envp);
	if (cmd->argv[0])
		cmd_not_found(cmd->argv[0]);
	exit(127);
}

static void	execute_cmd(t_cmd *cmd, t_env *env)
{
	if (!cmd->prev || !cmd->next)
	{
		external_redirections(cmd, env);
	}
	else
	{
		set_redirect(cmd);
		if (cmd->is_builtin)
			exit(execbltin(cmd, env));
		else
			execve(cmd->path, cmd->argv, env->envp);
		if (cmd->argv[0])
			cmd_not_found(cmd->argv[0]);
		exit(127);
	}
}

static void	out_execution(t_env *env, t_cmd *exec)
{
	t_cmd	*tmp;

	if (open_pipes(&exec))
		return ;
	tmp = exec;
	while (tmp)
	{
		child_signals();
		tmp->pid = fork();
		if (tmp->pid < 0)
		{
			printf("%s\n", "echec fork");
			break ;
		}
		if (tmp->pid == 0)
			execute_cmd(tmp, env);
		tmp = tmp->next;
	}
	tmp = exec;
	close_pipes_fromfirst(tmp);
	ft_waitpid(tmp);
	main_signals();
}

void	execution(t_env *env, t_cmd *exec)
{
	t_cmd	*tmp;

	tmp = exec;
	g_exit = ft_heredoc(env->head_var, exec);
	if (ft_lstsize(exec) > 1)
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
			execute_cmd(tmp, env);
		waitpid(tmp->pid, &g_exit, 0);
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
		main_signals();
	}
}
