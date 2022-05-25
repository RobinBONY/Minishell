/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:14:41 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 13:36:29 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	assign_type(t_source *source)
{
	t_source	*src;

	src = source;
	while (src)
	{
		if (ft_isoperator(src->str[0]))
			src->type = OPERATOR;
		else
			src->type = STRING;
		src = src->next;
	}
}

void	ft_srcclear(t_source **head)
{
	t_source	*cursor;

	while (*head)
	{
		cursor = (*head)->next;
		if ((*head)->str)
			free((*head)->str);
		free((*head));
		*head = cursor;
	}
}
