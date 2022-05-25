/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:13:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 13:44:18 by alakhdar         ###   ########lyon.fr   */
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

static void	ft_docadd_front(t_heredoc **alst, t_heredoc *new)
{
	t_heredoc	*next;

	next = *alst;
	*alst = new;
	new->next = next;
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
			ft_docadd_front(&exec->heredocs, new);
			tmp->used = 0;
			tmp->next->used = 0;
		}
		tmp = tmp->next;
	}
	return (0);
}
