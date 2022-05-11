/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:36:14 by rbony             #+#    #+#             */
/*   Updated: 2022/05/10 11:18:50 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/node.h"
#include "../headers/parser.h"

t_node	*new_node(enum e_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		return (NULL);
	}
	ft_memset(node, 0, sizeof(t_node));
	node->type = type;
	return (node);
}

void	add_child_node(t_node *parent, t_node *child)
{
	t_node	*sibling;

	if (!parent || !child)
	{
		return ;
	}
	if (!parent->first_child)
	{
		parent->first_child = child;
	}
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling)
		{
			sibling = sibling->next_sibling;
		}
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}

void	set_node_val_str(t_node *node, char *val)
{
	char	*val2;

	node->val_type = VAL_STR;
	if (!val)
	{
		node->val.str = NULL;
	}
	else
	{
		val2 = malloc(strlen(val) + 1);
		if (!val2)
		{
			node->val.str = NULL;
		}
		else
		{
			ft_strcpy(val2, val);
			node->val.str = val2;
		}
	}
}

void	free_node_tree(t_node *node)
{
	t_node	*child;
	t_node	*next;

	if (!node)
	{
		return ;
	}
	child = node->first_child;
	while (child)
	{
		next = child->next_sibling;
		free_node_tree(child);
		child = next;
	}
	if (node->val_type == VAL_STR)
	{
		if (node->val.str)
		{
			free(node->val.str);
		}
	}
	free(node);
}
