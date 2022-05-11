/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:40:08 by rbony             #+#    #+#             */
/*   Updated: 2022/05/11 15:09:14 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executor.h"

int	ft_export(char **argv, t_exp *head_exp)
{
	if (argv[1])
	{
		append_to_exp(head_exp, argv[1]);
		sort_export(head_exp);
	}
	else
		print_export(head_exp);
	return (0);
}

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	launch_builtin(char *path, char **argv,
	t_var *head_env, t_exp *head_exp)
{
	if (ft_strcmp(path, "echo") == 0)
		g_exit = ft_echo(argv);
	else if (ft_strcmp(path, "cd") == 0)
		g_exit = ft_cd(argv[1], head_env);
	else if (ft_strcmp(path, "pwd") == 0)
		g_exit = ft_pwd(head_env);
	else if (ft_strcmp(path, "export") == 0)
		g_exit = ft_export(argv, head_exp);
	else if (ft_strcmp(path, "unset") == 0)
		g_exit = ft_unset(head_exp, head_env, argv[1]);
	else if (ft_strcmp(path, "env") == 0)
		g_exit = print_env(head_env);
	else if (ft_strcmp(path, "exit") == 0)
		exit(0);
}
