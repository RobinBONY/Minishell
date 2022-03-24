/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:30:39 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/24 15:07:04 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

void	print_envp(void)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		printf("%s\n", g_env[i]);
		i++;
	}
}

int	envp_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i ++;
	return (i);
}

int	set_envp(char **envp)
{
	int	i;

	i = -1;
	g_env = malloc(sizeof(char *) * (envp_len(envp) + 1));
	while (envp[++i])
	{
		g_env[i] = ft_strdup(envp[i]);
		if (!g_env[i])
			exit(0);
	}
	return (0);
}

char	*get_envp(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr(envp[i], '='))
			n2 = ft_strchr(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

void	unset_envp(int envp_index)
{
	int	i;
	int	count;

	i = envp_index;
	count = envp_index + 1;
	free(g_env[envp_index]);
	while (g_env[i + 1])
	{
		g_env[i] = ft_strdup(g_env[i + 1]);
		free(g_env[i + 1]);
		i++;
		count++;
	}
	g_env = ft_realloc(count - 1);
}
