/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:23:30 by rbony             #+#    #+#             */
/*   Updated: 2022/05/25 15:34:25 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_lstsize(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

static char	*find_path(t_var *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*find_cmd_path(char *cmd, char *env_path)
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
		if (access(cmd_path, F_OK) == 0)
		{
			free_params(path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_params(path);
	return (NULL);
}

void	find_all_path(t_var *env, t_cmd *cmd)
{
	char	*path;

	path = find_path(env);
	if (!path)
		return ;
	while (cmd)
	{
		if (cmd->is_builtin == 0)
		{
			cmd->path = find_cmd_path(cmd->argv[0], path);
			if (!cmd->path)
				cmd->path = ft_strdup(cmd->argv[0]);
		}
		cmd = cmd->next;
	}
}
