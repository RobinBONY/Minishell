/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:10:13 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 13:42:15 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_cmdadd_back(t_cmd **alst, t_cmd *new)
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

static t_cmd	*new_cmd(t_source **source, t_cmd *prev, int len)
{
	t_cmd		*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = malloc((len + 1) * sizeof(char *));
	if (!new->argv)
		return (NULL);
	while (*source && i < len)
	{
		if ((*source)->used)
		{
			new->argv[i] = ft_strdup((*source)->str);
			(*source)->used = 0;
			i++;
		}
		*source = (*source)->next;
	}
	new->argv[i] = NULL;
	new->is_builtin = is_builtin(new->argv[0]);
	new->next = NULL;
	new->prev = prev;
	return (new);
}

static int	get_len(t_source *src)
{
	int			i;
	t_source	*tmp;

	i = 0;
	tmp = src;
	while (tmp && ft_strcmp(tmp->str, "|"))
	{
		if (tmp->used)
			i++;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->used = 0;
	return (i);
}

static void	index_commands(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmds;
	i = 1;
	while (tmp)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

int	make_commands(t_executor *exec, t_source **source)
{
	int			cmd_len;
	t_cmd		*new;
	t_source	*tmp;

	exec->commands = NULL;
	tmp = *source;
	while (tmp)
	{
		cmd_len = get_len(tmp);
		if (cmd_len > 0)
		{
			new = new_cmd(&tmp, new, cmd_len);
			if (!new)
				return (1);
			ft_cmdadd_back(&exec->commands, new);
		}
		else
			tmp = tmp->next;
	}
	index_commands(exec->commands);
	return (0);
}
