/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:59:45 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/09 13:48:48 by rbony            ###   ########lyon.fr   */
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
	char	*buff_key;
	char	*buff_value;
	char	*buff_itoa;

	tmp = 0;
	buff_key = get_key(*envp);
	if (ft_strncmp(buff_key, "SHLVL", ft_strlen("SHLVL")) == 0)
	{
		buff_value = get_value(*envp);
		tmp = ft_atoi(buff_value);
		free(buff_value);
		tmp += 1;
		free(*envp);
		buff_itoa = ft_itoa(tmp);
		*envp = ft_strjoin("SHLVL=", buff_itoa);
		free(buff_itoa);
	}
	free(buff_key);
}

int	replace_needed(char *str, t_var *head)
{
	char	*tmp;
	int		len;
	int		expand;

	tmp = str;
	len = 0;
	expand = 1;
	while (*tmp)
	{
		if (*tmp == '"')
			expand *= -1;
		if (*tmp == '\'' && expand == 1)
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
		while (tmp[len] && ft_isalnum(tmp[len]))
			len++;
		return (len);
	}
	return (0);
}
