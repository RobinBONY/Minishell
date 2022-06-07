/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:59:45 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/07 17:29:31 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**dup_env(char **envp)
{
	int		i;
	int		size;
	char	**dup_env;

	i = 0;
	size = ft_tabsize(envp);
	dup_env = malloc(sizeof(char *) * (size + 1));
	while (envp[i])
	{
		dup_env[i] = ft_strdup(envp[i]);
		shell_level(&dup_env[i]);
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}

void	shell_level(char **envp)
{
	int		tmp;

	tmp = 0;
	if (ft_strncmp(get_key(*envp), "SHLVL", ft_strlen("SHLVL")) == 0)
	{
		tmp = ft_atoi(get_value(*envp));
		tmp += 1;
		free(*envp);
		*envp = ft_strjoin("SHLVL=", ft_itoa(tmp));
	}
}

int	replace_needed(char *str, t_var *head)
{
	char	*tmp;
	int		len;

	tmp = str;
	len = 0;
	while (*tmp)
	{
		if (*tmp == '\'')
			tmp = ft_strchr(tmp, '\'');
		if (*tmp == '$')
			return (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '?');
		tmp++;
	}
	return (0);
}

int	get_type(char *tmp)
{
	int	len;

	len = 0;
	if (*(tmp + 1) == '?')
		return (-1);
	if (ft_isdigit(*(tmp + 1)))
		return (2);
	else
	{
		len++;
		while (tmp[len] && tmp[len] != '\'' && tmp[len] != ' '
			&& tmp[len] != '"' && tmp[len] != '$')
			len++;
		return (len);
	}
	return (0);
}
