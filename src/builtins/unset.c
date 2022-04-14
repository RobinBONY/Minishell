/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:33:01 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/13 11:52:10 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_var *head, char *key)
{
	t_var	*cursor;
	t_var	*prev;

	cursor = head;
	if (cursor != NULL && ft_strncmp(cursor->key, key, ft_strlen(key)) == 0)
	{
		head = cursor->next;
		free(cursor);
		return ;
	}
	while (cursor != NULL && ft_strncmp(cursor->key, key, ft_strlen(key)) != 0)
	{
		prev = cursor;
		cursor = cursor->next;
	}
	if (cursor == NULL)
		return ;
	prev->next = cursor->next;
	free(cursor);
}

// void	unset_export(t_var *head_exp, char *key)
// {
	
// }