/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:15:26 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/31 14:34:24 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	unmanaged_character_error(char c)
{
	printf("%s%c\n", "Unmanaged character : ", c);
	g_exit = 258;
	return (1);
}

static int	check_quotes(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == '\'')
		{
			tmp = ft_strchr(tmp, '\'');
			if (!tmp)
				return (unmanaged_character_error('\''));
		}
		else if (*tmp == '"')
		{
			tmp = ft_strchr(tmp, '"');
			if (!tmp)
				return (unmanaged_character_error('"'));
		}
		tmp++;
	}
	return (0);
}

int	not_interpreted(char *line)
{
	if (check_quotes(line))
		return (1);
	if (ft_strchr(line, ';'))
		return (unmanaged_character_error(';'));
	if (ft_strchr(line, '\\'))
		return (unmanaged_character_error('\\'));
	return (0);
}

int	syntax_error(void)
{
	printf("%s\n", "minishell : syntax error");
	g_exit = 258;
	return (1);
}

int	parse_error(t_source *head)
{
	t_source	*node;

	node = head;
	if (ft_strcmp(node->str, "|") == 0)
		return (syntax_error());
	while (node->next)
	{
		if (node->next && node->type == OPERATOR
			&& node->next->type == OPERATOR)
		{
			if (ft_strcmp(node->str, "|"))
				return (syntax_error());
			else if (ft_strcmp(node->str, "|") == 0
				&& ft_strcmp(node->next->str, "|") == 0)
				return (syntax_error());
		}
		node = node->next;
	}
	if (node->type == OPERATOR)
		return (syntax_error());
	return (0);
}
