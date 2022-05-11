/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:57:17 by rbony             #+#    #+#             */
/*   Updated: 2022/05/11 15:32:51 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/node.h"
#include "../headers/executor.h"

char	*search_path(char *cmd, char *env_path)
{
	int		i;
	char	*cmd_path;
	char	**path;

	i = 0;
	path = ft_split(env_path, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		cmd_path = ft_strjoin_cmd(path[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}

int	do_exec_cmd(int argc, char **argv, t_var *head_env, t_exp *head_exp)
{
	char	*path;

	ft_tolower(argv[0]);
	if (is_builtin(argv[0]))
		launch_builtin(argv[0], argv, head_env, head_exp);
	else
	{
		path = search_path(argv[0], get_var(head_env, "PATH"));
		if (!path)
		{
			exit(0);
		}
		execve(path, argv, NULL);
	}
	exit(0);
}

void	free_argv(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
}

int	build_argv(t_node	*child, char **argv)
{
	char	*str;
	int		argc;

	argc = 0;
	while (child)
	{
		str = child->val.str;
		argv[argc] = malloc(ft_strlen(str) + 1);
		if (!argv[argc])
		{
			free_argv(argv);
			return (0);
		}
		ft_strcpy(argv[argc], str);
		if (++argc >= 255)
		{
			break ;
		}
		child = child->next_sibling;
	}
	argv[argc] = NULL;
	return (argc);
}

int	do_simple_command(t_node *node, t_var *head_env, t_exp *head_exp)
{
	t_node	*child;
	int		argc;
	char	*argv[255 + 1];
	pid_t	child_pid;
	int		status;

	status = 0;
	if (!node)
		return (0);
	child = node->first_child;
	if (!child)
		return (0);
	argc = build_argv(child, argv);
	if (argc == 0)
		return (0);
	child_pid = 0;
	child_pid = fork();
	if (child_pid == 0)
		do_exec_cmd(argc, argv, head_env, head_exp);
	else if (child_pid < 0)
		return (0);
	waitpid(child_pid, &status, 0);
	free_argv(argv);
	return (1);
}
