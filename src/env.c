/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:30:39 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/17 13:52:36 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

void	print_env(void)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		printf("%s\n", g_env[i]);
		i++;
	}
}

int	env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i ++;
	return (i);
}

void	set_env(char **envp)
{
	int	i;

	i = -1;
	g_env = malloc(sizeof(char *) * (env_len(envp) + 1));
	while (envp[++i])
	{
		g_env[i] = ft_strdup(envp[i]);
		printf("Test");
		if (!g_env[i])
			exit(0);
	}
}

// char	*get_env(char *var, char **env, int n)
// {
// 	int	i;
// 	int	n2;

// 	i = 0;
// 	if (n < 0)
// 		n = ft_strlen(var);
// 	while (!ft_strchr(var, '=') && env && env[i])
// 	{
// 		n2 = n;
// 		if (n2 < ft_strchr(env[i], '='))
// 			n2 = ft_strchr(env[i], '=');
// 		if (!ft_strncmp(env[i], var, n2))
// 			return (ft_substr(env[i], n2 + 1, ft_strlen(env[i])));
// 		i++;
// 	}
// 	return (NULL);
// }

// void	unset_envvar(int envvar_index)
// {
// 	int	i;
// 	int	count;

// 	i = envvar_index;
// 	count = envvar_index + 1;
// 	free(g_env[envvar_index]);
// 	while (g_env[i + 1])
// 	{
// 		g_env[i] = ft_strdup(g_env[i + 1]);
// 		free(g_env[i + 1]);
// 		i++;
// 		count++;
// 	}
// 	g_env = ft_realloc(count - 1);
// }
