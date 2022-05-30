/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:13:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/30 13:22:56 by rbony            ###   ########lyon.fr   */
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
	t_heredoc	*new;

	new = new_heredoc((*source)->next->str);
	if (!new)
		return (1);
	ft_docadd_back(&exec->heredocs, new);
	(*source)->used = 0;
	(*source)->next->used = 0;
	if (exec->input)
	{
		close(exec->input);
		exec->input = 0;
	}
	return (0);
}
