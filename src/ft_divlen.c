/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:54:18 by rbony             #+#    #+#             */
/*   Updated: 2022/03/29 13:55:45 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_divlen(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp && *tmp == *s)
	{
		if (*tmp == ' ')
			return (tmp - s);
		if (*tmp == '\'' || *tmp == '"')
		{
			tmp = ft_strchr(tmp, *tmp);
			return ((tmp - s) + 1);
		}
		while (ft_isalpha(*tmp) || ft_isdigit(*tmp))
			tmp++;
		if (*tmp != *s)
			return (tmp - s);
		tmp++;
	}
	return (tmp - s);
}
