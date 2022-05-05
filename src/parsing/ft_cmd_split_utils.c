/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:31:41 by rbony             #+#    #+#             */
/*   Updated: 2022/05/04 14:32:34 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_divlen(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp && tmp == s)
	{
		if (*tmp == ' ')
			return (tmp - s);
		if (*tmp == '\'' || *tmp == '"')
		{
			tmp = ft_strchr(tmp, *tmp);
			return ((tmp - s) + 1);
		}
		if (*tmp == '$')
		{
			tmp++;
			if (*tmp == '?')
				tmp++;
		}
		while (ft_isalnum(*tmp) || *tmp == '=')
			tmp++;
		if (tmp != s)
			return (tmp - s);
		tmp++;
	}
	return (tmp - s);
}
