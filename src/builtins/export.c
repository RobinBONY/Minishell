/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:33:13 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/06 16:44:20 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_var	*init_export(char **envp)
{
	int		i;
	t_var	*head;

	i = 0;
	head = create_node(NULL, envp[i]);
	while (envp[++i])
		append_to_list(head, envp[i]);
	return (head);
}
