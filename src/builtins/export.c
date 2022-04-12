/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:33:13 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/12 16:37:20 by alakhdar         ###   ########lyon.fr   */
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
	t_var	*current_node_node;

	i = 0;
	current_node_node = head;
	while (current_node_node)
	{
		current_node_node = current_node_node->next;
		i++;
	}
	return (i);
}

void	print_export(t_var *head_exp)
{
	t_var	*cursor;

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
}

int	node_count(t_var *head)
{
	int		i;
	t_var	*cursor;

	if (!head)
		return (-1);
	i = 1;
	cursor = head->next;
	while (cursor)
	{
		cursor = cursor->next;
		i++;
	}
	return (i);
}

char	*join_key_val(t_var *node)
{
	char	*buffer;

	if (node->value)
		buffer = malloc((ft_strlen(node->key) + (ft_strlen(node->value)) * sizeof(char)) + 2);
	else
		buffer = malloc(ft_strlen(node->key) * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	ft_strcpy(buffer, node->key);
	if (node->value)
	{
		ft_strcat(buffer, "=");
		ft_strcat(buffer, node->value);
	}
	return (buffer);
}

// int	tab_is_sorted(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	sort_char_tab(char	**str, int len)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	while (i <= len)
	{
		j = i + 1;
		while (j <= len)
		{
			if (ft_strcmp(str[i], str[j]) > 0)
			{
				ft_strcpy(buffer, str[i]);
				ft_strcpy(str[i], str[j]);
				ft_strcpy(str[j], buffer);
			}
			j++;
		}
		i++;
	}
}

void	free_list(t_var	*head)
{
	t_var	*current_node;
	t_var	*next;

	current_node = head;
	while (current_node != NULL)
	{
		next = current_node->next;
		free(current_node);
		current_node = next;
	}
	head = NULL;
}

/* Passer la liste exp en tableau de char
	Trier le tableau de char
	Passer le tableau en nouvelle liste exp
	 free l'ancienne liste exp
	Return la nouvelle liste triée */
t_var	*sort_export(t_var *head_exp)
{
	t_var	*cursor;
	t_var	*new_head;
	char	**export;
	int		i;
	int		len;

	i = 0;
	len = node_count(head_exp);
	export = malloc(sizeof(char *) * len);
	cursor = head_exp->next;
	while (cursor)
	{
		export[i] = join_key_val(cursor);
		i++;
		cursor = cursor->next;
	}
	sort_char_tab(export, len);
	new_head = init_export(export);
	free_list(head_exp);
	return (new_head);
}
