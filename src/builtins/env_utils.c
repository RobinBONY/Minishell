/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:25:05 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/06 16:28:33 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_var(t_var *head)
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
}

char	*get_key(char *envp)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	while (envp[i] && envp[i] != '=')
	{
		i++;
	}
	key = ft_substr(envp, j, ft_strlen(envp) - i);
	return (key);
}

char	*get_value(char *envp)
{
	char	*buf;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	i++;
	j = i;
	while (envp[i])
		i++;
	len = i;
	buf = malloc(sizeof(char) * len + 1);
	if (!buf)
		exit (0);
	i = 0;
	while (envp[j])
	{
		buf[i] = envp[j];
		i++;
		j++;
	}
	buf[i] = '\0';
	return (buf);
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
