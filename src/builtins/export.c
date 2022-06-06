/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:33:13 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/06 11:32:12 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_exp	*create_exp_node(char *envp)
{
	t_exp	*new_env;

	new_env = (t_exp *)malloc(sizeof(t_exp));
	if (!new_env)
	{
		printf("Error in adding new export variable\n");
		g_exit = 0;
		exit (0);
	}
	new_env->key = get_key(envp);
	new_env->value = get_value(envp);
	new_env->next = NULL;
	new_env->prev = NULL;
	return (new_env);
}

t_exp	*append_to_exp(t_exp *head, char *envp)
{
	t_exp	*cursor;
	t_exp	*new_env;

	cursor = head;
	while (cursor->next != NULL)
		cursor = cursor->next;
	new_env = create_exp_node(envp);
	cursor->next = new_env;
	new_env->prev = cursor;
	return (head);
}

t_exp	*init_export(char **envp)
{
	int		i;
	t_exp	*head;

	i = 0;
	head = create_exp_node(envp[i]);
	while (envp[++i])
		append_to_exp(head, envp[i]);
	return (head);
}

int	print_export(t_exp *head_exp)
{
	t_exp	*cursor;

	cursor = head_exp->next;
	while (cursor)
	{
		printf("declare -x %s", cursor->key);
		if (cursor->value)
			printf("=\"%s\"\n", cursor->value);
		else
			printf("\n");
		cursor = cursor->next;
	}
	return (0);
}
