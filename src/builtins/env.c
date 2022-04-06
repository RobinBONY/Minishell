/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:30:39 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/06 16:41:04 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

t_var	*create_node(t_var *next, char *envp)
{
	t_var	*new_env;

	new_env = (t_var *)malloc(sizeof(t_var));
	if (!new_env)
	{
		printf("Error in adding new environment variable\n");
		exit (0);
	}
	new_env->key = get_key(envp);
	new_env->value = get_value(envp);
	new_env->printable = is_occurring(envp);
	new_env->next = next;
	return (new_env);
}

t_var	*append_to_list(t_var *head, char *envp)
{
	t_var	*cursor;
	t_var	*new_env;

	cursor = head;
	while (cursor->next != NULL)
		cursor = cursor->next;
	new_env = create_node(NULL, envp);
	cursor->next = new_env;
	return (head);
}

t_var	*init_env(char **envp)
{
	int		i;
	t_var	*head;

	i = 0;
	head = create_node(NULL, envp[i]);
	while (envp[++i])
		append_to_list(head, envp[i]);
	return (head);
}

void	ft_unset(t_var *head, char *key)
{
	t_var	*cursor;
	t_var	*prev;

	cursor = head;
	if (cursor != NULL && ft_strncmp(cursor->key, key, ft_strlen(key)) == 0)
	{
		head = cursor->next;
		free(cursor);
		return ;
	}
	while (cursor != NULL && ft_strncmp(cursor->key, key, ft_strlen(key)) != 0)
	{
		prev = cursor;
		cursor = cursor->next;
	}
	if (cursor == NULL)
		return ;
	prev->next = cursor->next;
	free(cursor);
}
