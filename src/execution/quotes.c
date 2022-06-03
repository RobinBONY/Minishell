/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:12:01 by rbony             #+#    #+#             */
/*   Updated: 2022/06/03 11:03:21 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	count_quotes(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			i++;
		str++;
	}
	return (i);
}

char	*resize_str(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc((ft_strlen(str) - count_quotes(str) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (str[j])
	{
		if (str[j] != '\'' && str[j] != '"')
		{
			new[i] = str[j];
			i++;
		}
		j++;
	}
	new[i] = '\0';
	return (new);
}

int	remove_quotes(t_source *source)
{
	char		*new;

	if (ft_strchr(source->str, '\'') || ft_strchr(source->str, '"'))
	{
		new = resize_str(source->str);
		if (!new)
			return (1);
		free(source->str);
		source->str = new;
	}
	return (0);
}

int	remove_quotes_heredoc(t_heredoc *tmp)
{
	char		*new;

	if (ft_strchr(tmp->str, '\'') || ft_strchr(tmp->str, '"'))
	{
		new = resize_str(tmp->str);
		if (!new)
			return (1);
		free(tmp->str);
		tmp->str = new;
	}
	return (0);
}
