/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:12:01 by rbony             #+#    #+#             */
/*   Updated: 2022/05/25 12:29:19 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	count_quotes(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			i++;
		*str++;
	}
	return (i);
}

static char	*resize_str(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc((ft_strlen(str) - count_quotes(str) + 1) * sizeof(char));
	if (!new)
		retrun (NULL);
	while (str[j])
	{
		if (str[j] != '\'' && str[j] != '"')
		{
			new[i] = str[j];
			i++;
		}
		j++;
	}
	return (new);
}

int	remove_quotes(t_source *source)
{
	char		*new;
	t_source	*tmp;

	tmp = source;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '\'') || ft_strchr(tmp->str, '"'))
		{
			new = resize_str(tmp->str);
			if (!new)
				return (1);
			free(tmp->str);
			tmp->str = new;
		}
		tmp = tmp->next;
	}
	return (0);
}