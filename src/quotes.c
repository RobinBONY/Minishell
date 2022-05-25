/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:12:01 by rbony             #+#    #+#             */
/*   Updated: 2022/05/25 11:21:00 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	remove_quotes(t_source *source)
{
	char		*new;
	t_source	*tmp;

	tmp = source;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '\'') || ft_strchr(tmp->str, '"'))
		{
			new = resize_str(tmp);
			if (!new)
				return (1);
			free(tmp->str);
			tmp->str = new;
		}
		tmp = tmp->next;
	}
	return (0);
}
