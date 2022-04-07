/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:33:13 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/07 14:14:36 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var	*create_exp_node(t_var *next, char *envp)
{
	t_var	*new_env;

	new_env = (t_var *)malloc(sizeof(t_var));
	if (!new_env)
	{
		printf("Error in adding new export variable\n");
		g_exit = 0;
		exit (0);
	}
	new_env->key = get_key(envp);
	new_env->value = get_value(envp);
	new_env->next = next;
	return (new_env);
}

t_var	*init_export(char **envp)
{
	int		i;
	t_var	*head;

	i = 0;
	head = create_exp_node(NULL, envp[i]);
	while (envp[++i])
		append_to_list(head, envp[i]);
	return (head);
}

int	ft_list_len(t_var *head)
{
	int		i;
	t_var	*current_node;

	i = 0;
	current_node = head;
	while (current_node)
	{
		current_node = current_node->next;
		i++;
	}
	return (i);
}

void	print_export(t_var *head)
{
	t_var	*current_node;

	current_node = head;
	while (current_node != NULL)
	{
		printf("%s", "declare -x ");
		printf("%s", current_node->key);
		printf("%c", '=');
		printf("%s\n", current_node->value);
		current_node = current_node->next;
	}
}

void	sort_list(t_var *head)
{
	t_var	*next_node;
	t_var	*current_node;
	t_var	*tmp;

	current_node = head;
	next_node = current_node->next;
	while (current_node)
	{
		while (next_node)
		{
			if (ft_strcmp(current_node->key, next_node->key) < 0)
			{
				tmp = current_node;
				current_node = next_node;
				next_node = tmp;
			}
			next_node = next_node->next;
		}
		current_node = current_node->next;
	}
}
