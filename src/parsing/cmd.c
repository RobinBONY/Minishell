/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:10:13 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/08 12:56:47 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_cmdadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_cmd	*ft_lstlast(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	ft_lstadd_front(t_source **alst, t_source *new)
{
	t_source	*next;

	next = *alst;
	*alst = new;
	new->next = next;
}

void	ft_push(t_source **src, t_source **dest)
{
	t_source	*tmp;
	t_source	*cursor;

	if (!src)
		return ;
	tmp = (*src)->next;
	(*src)->next = NULL;
	if (!*dest)
		*dest = *src;
	else
	{
		cursor = *dest;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = (*src);
	}
	(*src) = tmp;
}

int	set_cmd(t_source **source, t_cmd *new, t_cmd *prev, int len)
{
	int	i;

	i = 0;
	new->argv = malloc((len + 1) * sizeof(char *));
	if (!new->argv)
		return (1);
	while (*source && i < len)
	{
		if ((*source)->used)
		{
			new->argv[i++] = ft_strdup((*source)->str);
			(*source)->used = 0;
		}
		*source = (*source)->next;
	}
	new->argv[i] = NULL;
	new->is_builtin = is_builtin(new->argv[0]);
	new->is_local = is_local(new->argv[0], new->argv);
	new->path = ft_strdup(new->argv[0]);
	ft_tolower(new->path);
	new->next = NULL;
	new->prev = prev;
	return (0);
}
