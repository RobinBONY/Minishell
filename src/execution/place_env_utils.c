/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:59:45 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/03 11:26:06 by alakhdar         ###   ########lyon.fr   */
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
		while (tmp[len] && tmp[len] != '\'' && tmp[len] != ' '
			&& tmp[len] != '"' && tmp[len] != '$')
			len++;
		return (len);
	}
	return (0);
}
