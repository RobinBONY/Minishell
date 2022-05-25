/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:13:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 16:39:56 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_heredoc	*new_heredoc(char *delim)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->str = ft_strdup(delim);
	new->next = NULL;
	return (new);
}

static void	ft_docadd_back(t_heredoc **alst, t_heredoc *new)
{
	t_heredoc	*last;

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

int	find_heredocs(t_executor *exec, t_source **source)
{
	t_source	*tmp;
	t_heredoc	*new;

	tmp = *source;
	exec->heredocs = NULL;
	while (tmp)
	{
		if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, "<<") == 0)
		{
			new = new_heredoc(tmp->next->str);
			if (!new)
				return (1);
			ft_docadd_back(&exec->heredocs, new);
			tmp->used = 0;
			tmp->next->used = 0;
			if (exec->input)
			{
				close(exec->input);
				exec->input = 0;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
