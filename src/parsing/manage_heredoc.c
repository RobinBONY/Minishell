/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:05:31 by rbony             #+#    #+#             */
/*   Updated: 2022/04/25 16:35:00 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_heredoc	*ft_docnew(char content)
{
	t_heredoc	*newdoc;

	newdoc = malloc(sizeof(t_heredoc));
	if (!newdoc)
		return (NULL);
	newdoc->delim = content;
	newdoc->next = NULL;
	return (newdoc);
}

void	ft_docadd_back(t_heredoc **alst, t_heredoc *new)
{
	t_heredoc	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
	{
		*alst = (*alst)->next;
	}
	last->next = new;
}

void	ft_docclear(t_heredoc **lst)
{
	t_heredoc	*last;

	if (!*lst)
		return ;
	while (*lst)
	{
		last = (*lst)->next;
		free(*lst);
		*lst = last;
	}
	lst = NULL;
}
