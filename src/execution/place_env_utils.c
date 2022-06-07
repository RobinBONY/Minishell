/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:59:45 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/07 13:17:12 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	replace_needed(char *str, t_var *head)
{
	char	*tmp;
	int		len;

	tmp = str;
	len = 0;
	while (*tmp)
	{
		if (*tmp == '\'')
			tmp = ft_strchr(tmp, '\'');
		if (*tmp == '$')
			return (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '?');
		tmp++;
	}
	return (0);
}

int	get_type(char *tmp)
{
	int	len;

	len = 0;
	if (*(tmp + 1) == '?')
		return (-1);
	if (ft_isdigit(*(tmp + 1)))
		return (2);
	else
	{
		len++;
		while (tmp[len] && ft_isalnum(tmp[len]))
			len++;
		return (len);
	}
	return (0);
}
