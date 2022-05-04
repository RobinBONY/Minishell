/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:05:31 by rbony             #+#    #+#             */
/*   Updated: 2022/05/04 10:39:11 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_heredoc	*ft_docnew(char *content)
{
	t_heredoc	*newdoc;

	if (!content)
		return (NULL);
	newdoc = malloc(sizeof(t_heredoc));
	if (!newdoc)
		return (NULL);
	newdoc->delim = content;
	newdoc->next = NULL;
	return (newdoc);
}

void	ft_docadd_back(t_heredoc **alst, t_heredoc *new)
{
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
	{
		*alst = (*alst)->next;
	}
	(*alst)->next = new;
}

void	ft_docclear(t_heredoc **lst)
{
	t_heredoc	*last;

	if (!*lst)
		return ;
	while (*lst)
	{
		last = (*lst)->next;
		free((*lst)->delim);
		free(*lst);
		*lst = last;
	}
	lst = NULL;
}
