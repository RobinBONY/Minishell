/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:12:01 by rbony             #+#    #+#             */
/*   Updated: 2022/06/06 13:45:59 by rbony            ###   ########lyon.fr   */
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
		{
			str = ft_strchr(str, *str);
			i += 2;
		}
		str++;
	}
	return (i);
}

static void	resize_str_2(char *new, char *str)
{
	char	*tmp;
	int		i;
	int		quotes;

	i = -1;
	quotes = 0;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] && !tmp && (str[i] == '\'' || str[i] == '"'))
		{
			quotes++;
			tmp = &str[i];
		}
		else if (str[i] && tmp && str[i] == *tmp)
		{
			quotes++;
			tmp = NULL;
		}
		else
			new[i - quotes] = str[i];
	}
	new[i - quotes] = '\0';
}

char	*resize_str(char *str)
{
	char	*new;

	new = malloc((ft_strlen(str) - count_quotes(str) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	resize_str_2(new, str);
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
