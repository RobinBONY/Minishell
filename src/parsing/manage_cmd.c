/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:05:38 by rbony             #+#    #+#             */
/*   Updated: 2022/04/29 01:39:16 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_cmdnew(char *path, char **argv)
{
	t_cmd	*newcmd;

	newcmd = malloc(sizeof(t_cmd));
	if (!newcmd)
		return (NULL);
	newcmd->path = path;
	newcmd->argv = argv;
	newcmd->next = NULL;
	return (newcmd);
}

void	ft_cmdadd_back(t_cmd **alst, t_cmd *new)
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

void	ft_cmdclear(t_cmd **lst)
{
	t_cmd	*last;

	if (!*lst)
		return ;
	while (*lst)
	{
		last = (*lst)->next;
		free_tab((*lst)->argv);
		free((*lst)->path);
		free(*lst);
		*lst = last;
	}
	lst = NULL;
}
