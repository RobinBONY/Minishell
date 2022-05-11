/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:25:05 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/10 14:00:42 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executor.h"

int	print_env(t_var *head)
{
	t_var	*current_node;

	current_node = head;
	while (current_node != NULL)
	{
		if (current_node->printable == 1)
		{
			printf("%s", current_node->key);
			printf("%c", '=');
			printf("%s\n", current_node->value);
		}
		current_node = current_node->next;
	}
	return (0);
}

char	*get_key(char *envp)
{
	char	*key;
	char	*tmp;

	tmp = ft_strchr(envp, '=');
	key = ft_substr(envp, 0, tmp - envp);
	if (!key)
		return (NULL);
	return (key);
}

char	*get_value(char *envp)
{
	char	*value;
	char	*tmp;

	tmp = ft_strchr(envp, '=');
	tmp++;
	value = ft_substr(envp, tmp - envp, ft_strlen(tmp));
	if (!value)
		return (NULL);
	return (value);
}

int	is_occurring(char *envp)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
			flag = 1;
		i++;
	}
	return (flag);
}

void	free_params(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
