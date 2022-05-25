/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:53:31 by rbony             #+#    #+#             */
/*   Updated: 2022/05/25 14:15:29 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_source	*create_src_node(t_source *next, char *data)
{
	t_source	*new_node;

	new_node = (t_source *)malloc(sizeof(t_source));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(data);
	new_node->used = 1;
	new_node->next = next;
	return (new_node);
}

static void	insert_node_cmd(char **data, t_source *node)
{
	int			i;
	t_source	*new;

	i = 0;
	if (node->str)
		free(node->str);
	node->str = ft_strdup(data[i]);
	while (data[++i])
	{
		new = create_src_node(node->next, data[i]);
		node->next = new;
		node = node->next;
	}
	free_params(data);
}

static void	ft_lstadd_back(t_source **alst, t_source *new)
{
	t_source	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last->next)
	{
		last = last->next;
	}
	last->next = new;
}

static t_source	*make_list(char	**split)
{
	t_source	*head;
	t_source	*new;
	int			i;

	i = 0;
	head = create_src_node(NULL, split[i]);
	if (!head)
		return (NULL);
	while (split[++i])
	{
		new = create_src_node(NULL, split[i]);
		if (!new)
			return (NULL);
		ft_lstadd_back(&head, new);
	}
	return (head);
}

t_source	*make_source(char *str)
{
	t_source	*source;
	t_source	*tmp;
	char		**split;
	int			i;

	i = 0;
	split = ft_cmd_split(str);
	if (!split)
		return (NULL);
	source = make_list(split);
	if (!source)
		return (NULL);
	free_params(split);
	tmp = source;
	while (tmp)
	{
		insert_node_cmd(ft_src_split(tmp->str), tmp);
		tmp = tmp->next;
	}
	return (source);
}
