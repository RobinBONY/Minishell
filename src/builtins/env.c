/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:30:39 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/16 15:34:02 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_var	*create_node(char *envp)
{
	t_var	*new_env;

	new_env = (t_var *)malloc(sizeof(t_var));
	if (!new_env)
		return (NULL);
	new_env->key = get_key(envp);
	new_env->value = get_value(envp);
	new_env->printable = is_occurring(envp);
	new_env->next = NULL;
	return (new_env);
}

t_var	*append_to_list(t_var *head, char *envp)
{
	t_var	*cursor;
	t_var	*new_env;

	cursor = head;
	while (cursor->next != NULL)
		cursor = cursor->next;
	new_env = create_node(envp);
	cursor->next = new_env;
	return (head);
}

t_var	*init_env(char **envp)
{
	int		i;
	t_var	*head;

	i = 0;
	head = create_node(envp[i]);
	while (envp[++i])
		append_to_list(head, envp[i]);
	return (head);
}

char	*get_var(t_var *head, char *key)
{
	t_var	*cursor;

	cursor = head;
	while (cursor)
	{
		if (ft_strcmp(key, cursor->key) == 0)
			return (cursor->value);
		cursor = cursor->next;
	}
	return (NULL);
}
