/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:05:03 by rbony             #+#    #+#             */
/*   Updated: 2022/04/25 16:34:55 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirect	*ft_rednew(int input, int output, char *filename)
{
	t_redirect	*newred;

	newred = malloc(sizeof(t_redirect));
	if (!newred)
		return (NULL);
	newred->is_input = input;
	newred->is_output = output;
	newred->filename = filename;
	newred->next = NULL;
	return (newred);
}

void	ft_redadd_back(t_redirect **alst, t_redirect *new)
{
	t_redirect	*last;

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

void	ft_redclear(t_redirect **lst)
{
	t_redirect	*last;

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
