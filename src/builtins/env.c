/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:30:39 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/05 14:47:41 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

t_env	*create_env_node(t_env *next, char *envp)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		printf("Error in adding new environment variable\n");
		exit (0);
	}
	new_env->key = get_key(envp);
	new_env->value = get_value(envp);
	new_env->next = next;
	return (new_env);
}

t_env	*append_to_envp(t_env *head, char *envp)
{
	t_env	*cursor;
	t_env	*new_env;

	cursor = head;
	while (cursor->next != NULL)
		cursor = cursor->next;
	new_env = create_env_node(NULL, envp);
	cursor->next = new_env;
	return (head);
}

t_env	*init_envp_list(char **envp)
{
	int		i;
	t_env	*head;

	i = 0;
	head = create_env_node(NULL, envp[i]);
	while (envp[++i])
		append_to_envp(head, envp[i]);
	return (head);
}

void	ft_unset(t_env *head, char *key)
{
	t_env	*cursor;
	t_env	*prev;

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
